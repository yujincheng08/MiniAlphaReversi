#include "mct.h"
#include <QRandomGenerator>

MCT::MCT(Config::State const &state, Config::Type const &type, QObject *parent)
    : QObject(parent) {
  root = new MCN(state, type, 0u, rule_);
}

unsigned MCT::defaultPolicy(MCN *node) const {
  unsigned reward = 0;
  while (!node->terminal()) {
  }
  return reward;
}

MCN *MCT::treePolicy() const {
  auto node = root;
  while (!node->terminal()) {
    if (node->expandable())
      node = node->expand();
    else
      node = node->bestChild(Config::Cp);
  }
  return node;
}

Move MCT::search() {
  while (intime()) {
    auto node = treePolicy();
    auto delta = defaultPolicy(node);
    backUp(node, delta);
  }
  auto choice = root->bestChild(0.0);
  choice->setParent(nullptr);
  root->deleteLater();
  root = choice;
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
