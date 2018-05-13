#include "mct.h"
#include <QDebug>
#include <QRandomGenerator>

MCT::MCT(QObject *parent) : QObject(parent) {
  // move to another thread.
  moveToThread(thread_);
  // and start the thread.
  thread_->start();
}

int MCT::defaultPolicy(MCN *node) const {
  auto state = node->state();
  auto player = node->type();
  // flag for whether the game is over.
  unsigned over = 0u;
  // get simulation time.
  auto remainTime = Config::simulationTime;
  // reward to show.
  int reward = 0;
  // each time of simulation, it will decrease remain time.
  while (remainTime--) {
    // initial turn of the node.
    auto simulateCount = node->depth() + 4;
    // if not over
    while (over < 2u) {
      // get the movement
      auto movement =
          simulateCount > Config::laterStage
              // if it's in last state, simply return all movement
              ? rule_.availableMovement(player, state)
              // if not, return priority moves.
              : rule_.priorityMoves(Config::priorityTable, player, state);
      // if no movement, skip, over increase.
      if (movement.size() == 0) {
        player = ~player;
        ++over;
        continue;
      }
      // increase simulation count.
      ++simulateCount;
      over = 0u;
      // apply the decision
      auto move =
          movement[QRandomGenerator::global()->bounded(movement.size())];
      state += rule_.apply(state, {move.x(), move.y(), player});
      player = ~player;
    }
    // if won, reward is 1, and 0 otherwise.
    reward += rule_.judge(state, type_) ? 1 : 0;
  }
  // average reward
  return reward / Config::simulationTime;
}

MCN *MCT::treePolicy() const {
  auto node = root;
  // get unexpanded node from the top to down.
  while (!node->terminal()) {
    if (node->expandable()) {
      return node->expand();
    } else
      // if not expandable, return its best children
      node = node->bestChild(Config::Cp);
  }
  return node;
}

MCT::~MCT() {
  // before deconstruction, stop the thread and delete the root.
  thread_->terminate();
  thread_->wait();
  root->deleteLater();
}

void MCT::search() {
  // skip if not AI's trun
  if (root->type() != type_) {
    qDebug() << "Not AI's turn";
    return;
  }
  emit disableBoard(true);
  QTime time = QTime::currentTime();
  // while in time limit, get a new node, apply default policy to it and backup
  // the delta reward.
  while (time.msecsTo(QTime::currentTime()) < Config::timeLimit) {
    auto node = treePolicy();
    auto delta = defaultPolicy(node);
    backUp(node, delta);
  }
  auto piecesCount = root->depth() + 4;
  qDebug() << "Total pieces:" << piecesCount;
  // get the best reward
  auto choice = root->finalDecision(1.0, piecesCount);
  if (!choice) {
    qDebug() << "I have no choice";
    return;
  }
  // update the three and emit the decision.
  auto move = choice->move();
  qDebug() << "AI: " << move.x() << move.y() << (char)move.type();
  updateTree(move.x(), move.y());
  emit decision(move.x(), move.y());
  emit disableBoard(false);
}

void MCT::backUp(MCN *node, const int &delta) const {
  // backup from the node to its parents.
  while (node) {
    node->backUp(delta);
    node = node->parent();
  }
}

void MCT::laozi(size_t const &x, size_t const &y) {
  if (!rule_.valid(x, y, root->type(), root->state())) return;
  // if valid, update the tree and search, 'caze it might be my turn.
  updateTree(x, y);
  qDebug() << "Player:" << x << y;
  search();
}

void MCT::reset(Config::Type type) {
  type_ = type;
  // delete the root.
  if (root) root->deleteLater();
  // construct the initial state.
  Config::State initstate(Config::SIZE);
  for (auto &row : initstate) {
    row.resize(Config::SIZE);
    for (auto &pos : row) {
      pos = Config::EMPTY;
    }
  }
  // create a new root and move it to the thread.
  root = new MCN(initstate + Config::initPieces, Config::first, 0u, rule_);
  root->moveToThread(thread_);
}

void MCT::updateTree(const size_t &x, const size_t &y) {
  MCN *choice = nullptr;
  // search if the corresponded node is expaned.
  for (auto &child : root->children()) {
    if (child->move().x() == x && child->move().y() == y) {
      choice = child;
      break;
    }
  }
  // if not expanded, create the node.
  if (choice == nullptr) {
    choice = new MCN(root->state(), ~root->type(), root->depth() + 1, rule_,
                     {x, y, root->type()});
  }
  // set the children as the new node and delete other nodes.
  choice->setParent(nullptr);
  root->deleteLater();
  root = choice;
}
