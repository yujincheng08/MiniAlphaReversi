#ifndef MCN_H
#define MCN_H

#include <QObject>
#include "config.h"
#include "logic/rule.h"

/*
 * Monte Carlo Tree Node
 */

class MCN : public QObject {
  using State = Config::State;
  using Movement = Config::Movement;
  using Type = Config::Type;
  Q_OBJECT
 public:
  explicit MCN(State const &lastState, Type const &type, const unsigned &depth,
               Rule const &rule, Movement const &movement = Movement(),
               MCN *parent = nullptr);

  MCN *bestChild(const double &c) const;

  double value(const double &c) const;

  QList<MCN *> children() const;

  MCN *parent() const;

  MCN *expand();

  void backUp(unsigned delta);

  inline State state() const { return state_; }
  inline Type type() const { return type_; }
  inline unsigned depth() const { return depth_; }
  inline bool expandable() { return remainMovement_.size() > 0; }
  inline bool terminal() { return !expandable() && children().size() == 0; }
  inline Movement movement() { return movement_; }
 signals:

 public slots:

 protected:
  explicit MCN(QObject *parent = nullptr);

 private:
  State state_;
  Type type_;
  unsigned depth_;
  Movement movement_;
  Rule const &rule_;
  Movement remainMovement_;
  unsigned N_{0u};
  unsigned Q_{0u};
};

#endif  // MCN_H
