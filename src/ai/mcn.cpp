#include "mcn.h"
#include <QDebug>
#include <QMap>
#include <QRandomGenerator>
#include <QtMath>

MCN::MCN(State const &lastState, Type const &type, unsigned const &depth,
         Rule const &rule, Move const &move, MCN *parent)
    : QObject(parent),
      state_(lastState + rule.apply(lastState, move)),
      type_(type),
      depth_(depth),
      move_(move),
      rule_(rule),
      remainMovement_(rule.availableMovement(type_, state_)) {
  if (remainMovement_.size() == 0) {
    type_ = ~type_;
    remainMovement_ = rule.availableMovement(type_, state_);
  }
  if (parent) moveToThread(parent->thread());
}

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

MCN *MCN::finalDecision(const double &c) const {
  double bestValue = -qInf();
  MCN *best = nullptr;
  MCN *tmpBest = nullptr;

  QMap<double, MCN *> map;
  QMap<double, MCN *> dist;
  double sum = 0;
  int count = 0;
  double alpha = 1;
  double beta = 1.0;

  // TODO
  for (auto const &child : children()) {
    double value = child->value(c);

    // priority
    int level = this->priorityOf(child->move_.x(), child->move_.y());
    qDebug() << value << alpha * (2 - level);
    value = value + alpha * (2 - level);

    // action
    double actionRate =
        1.0 /
        (rule_.getRivalMovement(child->state_, child->move_).length() + 1);
    value = value * beta * actionRate;
    value = value > 0 ? value : 0;

    map[value] = child;

    sum += value;
    count++;

    if (bestValue < value) {
      bestValue = value;
      tmpBest = child;
    }
  }

  if (sum == 0 || count <= 0) {
    return tmpBest;
  }

  foreach (double key, map.keys()) {
    dist[key / sum] = map[key];
    Move m = map[key]->move_;
    qDebug() << "x" << m.x() << "y" << m.y() << key / sum;
  }

  double choice = QRandomGenerator::global()->bounded(1.0);
  double accumulate = 0;
  foreach (double key, dist.keys()) {
    if (accumulate < choice && accumulate + key >= choice) {
      if (key > 1.0 / count)
        best = dist[key];
      else
        best = tmpBest;
      qDebug() << "x" << best->move_.x() << "y" << best->move_.y() << choice;
      break;
    }
    accumulate += key;
  }
  qDebug() << "---------------------------------";
  return best;
}

MCN *MCN::expand() {
  if (expandable()) {
    auto choice = QRandomGenerator::global()->bounded(remainMovement_.size());
    auto move = remainMovement_.takeAt(choice);
    return new MCN(state_, ~type_, depth_ + 1, rule_, move, this);
  }
  return this;
}

void MCN::backUp(int delta) {
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
  double value = c * qSqrt(2.0 * qLn(parent()->N_) / N_) + Q_ * 1.0 / N_;
  return value;
}

int MCN::priorityOf(const size_t &x, const size_t &y) const {
  for (int i = 0; i < Config::priorityTable.length(); i++) {
    for (int j = 0; j < Config::priorityTable[i].length(); j++) {
      if (Config::priorityTable[i][j].x() == x &&
          Config::priorityTable[i][j].y() == y) {
        return i;
      }
    }
  }
  return 0;
}
