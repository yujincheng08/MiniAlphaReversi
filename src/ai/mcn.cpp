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
  // if no avaliable movement, skip to the opposite player.
  if (remainMovement_.size() == 0) {
    type_ = ~type_;
    remainMovement_ = rule.availableMovement(type_, state_);
  }
  // move the parent's thread.
  if (parent) moveToThread(parent->thread());
}

MCN *MCN::bestChild(double const &c) const {
  // initial best value is minus infinity.
  double bestValue = -qInf();
  MCN *best = nullptr;

  // iterate all the children to get the best one.
  for (auto const &child : children()) {
    double value = child->value(c);
    if (bestValue < value) {
      bestValue = value;
      best = child;
    }
  }
  // nullptr means its leaf;
  return best;
}

MCN *MCN::finalDecision(const double &c, int turn) const {
  double bestValue = -qInf();
  MCN *best = nullptr;
  MCN *tmpBest = nullptr;

  QMap<double, MCN *> map;
  QMap<double, MCN *> dist;
  double sum = 0;
  int count = 0;
  double alpha = 1;
  double beta = 1;
  bool skip = false;

  if ((unsigned)turn >= Config::laterStage) {
    skip = true;
  }

  for (auto const &child : children()) {
    double value = child->value(c);

    // priority
    int level = this->priorityOf(child->move_.x(), child->move_.y());
    if (level >= 5) {
      level -= 10;
    }
    if (!skip) {
      value = value + alpha * 1.0 / (level + 0.01);
    }

    // action
    double actionRate =
        1.0 /
        (child->rule_.getRivalMovement(child->state_, child->move_).length() +
         0.01);

    if (!skip) {
      value = value * beta * actionRate;
    }

    // ensure value >=0 in Roulette selection algorithm
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

  // normalization
  foreach (double key, map.keys()) { dist[key / sum] = map[key]; }

  // Roulette selection algorithm
  double choice = QRandomGenerator::global()->bounded(1.0);
  double accumulate = 0;
  best = tmpBest;
  foreach (double key, dist.keys()) {
    // the random number is in this section
    // choose this node
    if (accumulate < choice && accumulate + key >= choice) {
      if (key > 1.0 / count) best = dist[key];
      break;
    }
    // next section
    accumulate += key;
  }
  return best;
}

MCN *MCN::expand() {
  if (expandable()) {
    // randomly choose one children that is not expeneded and return it.
    auto choice = QRandomGenerator::global()->bounded(remainMovement_.size());
    auto move = remainMovement_.takeAt(choice);
    return new MCN(state_, ~type_, depth_ + 1, rule_, move, this);
  }
  // return itself if not expandable.
  return this;
}

void MCN::backUp(int delta) {
  // update N and Q.
  ++N_;
  Q_ += delta;
}

QList<MCN *> MCN::children() const {
  QList<MCN *> result;
  // iterate all the children and cast to MCN.
  for (auto child : QObject::children())
    result.append(dynamic_cast<MCN *>(child));
  return result;
}

MCN *MCN::parent() const {
  // cast parent to MCN.
  return dynamic_cast<MCN *>(QObject::parent());
}

double MCN::value(double const &c) const {
  // N must not be 0.
  Q_ASSERT(N_ != 0.0);
  // calulate by formula.
  double value = c * qSqrt(2.0 * qLn(parent()->N_) / N_) + Q_ * 1.0 / N_;
  return value;
}

int MCN::priorityOf(const size_t &x, const size_t &y) const {
  // iterate the priority table and get the priority level.
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
