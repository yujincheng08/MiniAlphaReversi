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

  bool valid(size_t const &x, size_t const &y,
             Config::Type const &player) const {
    return valid(x, y, player, state_);
  }

  Movement availableMovement(Config::Type const &player,
                             State const &state) const;

  inline Movement availableMovement(Config::Type const &player) const {
    return availableMovement(player, state_);
  }

  Movement priorityMoves(Config::PriorityTable const &priorityTable,
                         Config::Type const &player, State const &state) const;
 signals:
  void changed(Movement const &movement);

 public slots:
  void reset();

  void laozi(size_t const &x, size_t const &y, Config::Type const &player);

 private:
  State state_{Config::SIZE};
};

#endif  // RULE_H
