#ifndef RULE_H
#define RULE_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include "config.h"
#include "logic/position.h"

/*
 * Rule of this game
 */

class Rule : public QObject {
  Q_OBJECT

  using State = Config::State;
  using Movement = Config::Movement;

 public:
  /* @brief constructor.
   * @params parent its parent.
   */
  explicit Rule(QObject *parent = nullptr);

  /* @brief get its state.
   * @return its state.
   */
  inline const State state() const { return state_; }

  /* @brief if it's valid for player to place a piece in (x,y) under state.
   * @params x
   * @params y
   * @params player the player.
   * @params state the state.
   * @return if valid.
   */
  bool valid(size_t const &x, size_t const &y, Config::Type const &player,
             State const &state) const;

  /* @brief if it's valid not to player in (x,y).
   * @parms x
   * @parms y
   * @return if valid.
   */
  inline bool valid(size_t const &x, size_t const &y) const {
    return valid(x, y, player_, state_);
  }

  /* @brief get all avaliable movement for player under the state.
   * @params player the player.
   * @params state the state.
   * @return all avaliable movement.
   */
  Movement availableMovement(Config::Type const &player,
                             State const &state) const;

  /* @biref get all avaliable movement for now.
   * @return all avaliable movement.
   */
  inline Movement availableMovement() const {
    return availableMovement(player_, state_);
  }

  /* @biref apply the move to the state.
   * @params state the state.
   * @params move the move.
   * @return the delta movement
   */
  const Movement apply(State const &state, Move const &move) const;

  /* @brief get the priority movement for player under priority table and the
   * state.
   * @params priorityTable the priority table.
   * @params player the player.
   * @params state the state.
   * @return the movement of the top priority.
   */
  Movement priorityMoves(Config::PriorityTable const &priorityTable,
                         Config::Type const &player, State const &state) const;

  /* @brief judge if player is won unser state.
   * @params state the state.
   * @params player the player.
   * @return if its won.
   */
  bool judge(State const &state, Config::Type const &player) const;

  /* @brief judge if player is won now.
   * @params player the player.
   * @return if its won.
   */
  inline bool judge(Config::Type const &player) const {
    return judge(state_, player);
  }

  /* @brief get avaliable movement of rival after move is apply to the state.
   * @params state the state.
   * @params move the move.
   * @return the abaliable movement.
   */
  Movement getRivalMovement(State const &state, Move const &move) const {
    auto newState = state + apply(state, move);
    return availableMovement(~move.type(), newState);
  }

 signals:
  /* @brief changed signal emitted if someone succefully laozis.
   * @params movement the delta movement.
   * @params avaliableMovement the new avaliableMovement.
   */
  void changed(Movement const &movement, Movement const &availableMovement);

  /* @brief game over signal emitted if game over
   */
  void gameOver();

  /* @brief pass signal emitted when the current player has to pass.
   */
  void pass();

 public slots:

  /* @brief reset the rule
   */
  void reset();

  /* @brief laozi on (x, y)
   * @params x
   * @params y
   */
  void laozi(size_t const &x, size_t const &y);

 private:
  // the current state
  State state_{Config::SIZE};

  // the current player
  Config::Type player_ = Config::first;
};

#endif  // RULE_H
