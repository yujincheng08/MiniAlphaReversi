#include "mct.h"
#include <QDebug>
#include <QRandomGenerator>

MCT::MCT(QObject *parent) : QObject(parent) { reset(Config::WHITE); }

unsigned MCT::defaultPolicy(MCN *node) const {
  unsigned reward = 0;
  return reward;
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

Move MCT::search() {
  while (intime()) {
    auto node = treePolicy();
    auto delta = defaultPolicy(node);
    backUp(node, delta);
    break;
  }
  auto choice = root->bestChild(0.0);
  auto movement = choice->movement();
  Q_ASSERT(movement.size() == 1u);
  return movement[0];
}

void MCT::backUp(MCN *node, const unsigned &delta) const {
  while (node) {
    node->backUp(delta);
    node = node->parent();
  }
}

bool MCT::intime() {
  return true;  // TODO
}

void MCT::laozi(const Config::Movement &movement,
                Config::Movement const &available) {
  Q_ASSERT(movement.size() > 0);
  auto x = movement[0].x();
  auto y = movement[0].y();
  updateTree(x, y);

  //  Move m = search();
  //  qDebug() << m.x() << " " << m.y();
  //  emit decision(m.x(), m.y());
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
  new MCN(initstate + Config::initPieces, Config::first, 0u, rule_);
}

void MCT::updateTree(const size_t &x, const size_t &y) {
  //  root->deleteLater();
  MCN *choice = nullptr;
  for (auto &child : root->children()) {
    if (child->movement()[0].x() == x && child->movement()[0].y() == y) {
      choice = child;
      break;
    }
  }
  if (choice == nullptr) {
    choice = new MCN(root->state(), ~root->type(), root->depth() + 1, rule_,
                     Config::Movement{{x, y, root->type()}});
  }
  choice->setParent(nullptr);
  root->deleteLater();
  root = choice;

  // TODO:
}
