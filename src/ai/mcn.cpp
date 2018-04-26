#include "mcn.h"
#include <QRandomGenerator>
#include <QtMath>

MCN::MCN(State const &lastState, Type const &type, unsigned const &depth,
         Rule const &rule, Movement const &movement, MCN *parent)
    : QObject(parent),
      state_(lastState),
      type_(type),
      depth_(depth),
      movement_(movement),
      rule_(rule),
      remainMovement_(rule.availableMovement(type, state_)) {}

MCN *MCN::bestChild(double const &c) const {
  double bestValue = -qInf();
  MCN *best = nullptr;
  for (auto const &child : children()) {
    double value = child->value(c);
    if (bestValue < value) {
      bestValue = value;
      best = child;
    }
  }
  return best;  // nullptr means its leaf;
}

MCN *MCN::expand() {
  if (expandable()) {
    auto choice = QRandomGenerator::global()->bounded(remainMovement_.size());
    auto move = remainMovement_.takeAt(choice);
    return new MCN(state_, ~type_, depth_ + 1, rule_, Movement{move}, this);
  }
  return this;
}

void MCN::backUp(unsigned delta) {
  ++N_;
  Q_ += delta;
}

QList<MCN *> MCN::children() const {
  QList<MCN *> result;
  for (auto child : QObject::children())
    result.append(dynamic_cast<MCN *>(child));
  return result;
}

MCN *MCN::parent() const { return dynamic_cast<MCN *>(QObject::parent()); }

double MCN::value(double const &c) const {
  Q_ASSERT(N_ != 0.0);
  return c * qSqrt(2.0 * qLn(parent()->N_) / N_) + Q_ / N_;
}
