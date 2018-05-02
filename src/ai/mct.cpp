#include "mct.h"
#include <QDebug>
#include <QRandomGenerator>

MCT::MCT(QObject *parent) : QObject(parent) {
  moveToThread(thread_);
  thread_->start();
}

int MCT::defaultPolicy(MCN *node) const {
  auto state = node->state();
  auto player = node->type();
  unsigned over = 0u;
  auto remainTime = Config::simulationTime;
  int reward = 0;
  while (remainTime--) {
    while (over < 2u) {
      auto priorityMoves =
          rule_.priorityMoves(Config::priorityTable, player, state);
      if (priorityMoves.size() == 0) {
        player = ~player;
        ++over;
        continue;
      }
      over = 0u;
      auto move = priorityMoves[QRandomGenerator::global()->bounded(
          priorityMoves.size())];
      state += rule_.apply(state, {move.x(), move.y(), player});
      player = ~player;
    }
    reward += rule_.judge(state, type_);
  }
  return reward / Config::simulationTime;
}

MCN *MCT::treePolicy() const {
  auto node = root;
  while (!node->terminal()) {
    if (node->expandable()) {
      return node->expand();
    } else
      node = node->bestChild(Config::Cp);
  }
  return node;
}

MCT::~MCT() {
  thread_->terminate();
  thread_->wait();
}

void MCT::search() {
  if (root->type() != type_) {
    qDebug() << "Not AI's turn";
    return;
  }
  emit disableBoard(true);
  QTime time = QTime::currentTime();
  while (time.msecsTo(QTime::currentTime()) < Config::timeLimit) {
    auto node = treePolicy();
    auto delta = defaultPolicy(node);
    backUp(node, delta);
  }
  //  auto choice = root->bestChild(0.0);
  auto choice = root->finalDecision(1.0);
  if (!choice) {
    qDebug() << "I have no choice";
    return;
  }
  auto move = choice->move();
  qDebug() << "AI: " << move.x() << move.y() << (char)move.type();
  updateTree(move.x(), move.y());
  emit decision(move.x(), move.y());
  emit disableBoard(false);
}

void MCT::backUp(MCN *node, const unsigned &delta) const {
  while (node) {
    node->backUp(delta);
    node = node->parent();
  }
}

void MCT::laozi(size_t const &x, size_t const &y) {
  if (!rule_.valid(x, y, root->type(), root->state())) return;
  updateTree(x, y);
  qDebug() << "Player:" << x << y;
  search();
}

void MCT::reset(Config::Type type) {
  type_ = type;
  if (root) root->deleteLater();
  Config::State initstate(Config::SIZE);
  for (auto &row : initstate) {
    row.resize(Config::SIZE);
    for (auto &pos : row) {
      pos = Config::EMPTY;
    }
  }
  root = new MCN(initstate + Config::initPieces, Config::first, 0u, rule_);
  root->moveToThread(thread_);
}

void MCT::updateTree(const size_t &x, const size_t &y) {
  //  root->deleteLater();
  MCN *choice = nullptr;
  for (auto &child : root->children()) {
    if (child->move().x() == x && child->move().y() == y) {
      choice = child;
      break;
    }
  }
  if (choice == nullptr) {
    choice = new MCN(root->state(), ~root->type(), root->depth() + 1, rule_,
                     {x, y, root->type()});
  }
  choice->setParent(nullptr);
  root->deleteLater();
  root = choice;

  // TODO:
}
