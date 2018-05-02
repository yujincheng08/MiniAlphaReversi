#ifndef RULE_H
#define RULE_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include "config.h"
#include "logic/position.h"

class Rule : public QObject {
  Q_OBJECT

  using State = Config::State;
  using Movement = Config::Movement;

 public:
  explicit Rule(QObject *parent = nullptr);

  inline const State state() const { return state_; }

  bool valid(size_t const &x, size_t const &y, Config::Type const &player,
             State const &state) const;

  inline bool valid(size_t const &x, size_t const &y) const {
    return valid(x, y, player_, state_);
  }

  Movement availableMovement(Config::Type const &player,
                             State const &state) const;

  inline Movement availableMovement() const {
    return availableMovement(player_, state_);
  }

  const Movement apply(State const &state, Move const &move) const;

  Movement priorityMoves(Config::PriorityTable const &priorityTable,
                         Config::Type const &player, State const &state) const;

  int judge(State const &state, Config::Type const &player) const;
  inline int judge(Config::Type const &player) const {
    return judge(state_, player);
  }

  Movement getRivalMovement(State const &state, Move const &move) const {
    auto newState = state + apply(state, move);
    return availableMovement(~move.type(), newState);
  }

 signals:
  void changed(Movement const &movement, Movement const &availableMovement);
  void gameOver();
  void pass();

 public slots:
  void reset();

  void laozi(size_t const &x, size_t const &y);

 private:
  State state_{Config::SIZE};
  Config::Type player_ = Config::first;
  bool whiteMovable = true;
  bool blackMovalbe = true;
  // TODO: how about passing
};

#endif  // RULE_H
