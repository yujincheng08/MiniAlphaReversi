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
  /* @brief constructor of the node
   * @params lastState the state of its parent.
   * @params type which type of the piece it will serach by.
   * @params depth the depth of the node.
   * @params move the move from its parent to itself.
   * @params parent the parent node.
   */
  explicit MCN(State const &lastState, Type const &type, const unsigned &depth,
               Rule const &rule,
               const Move &move = {0, 0, Config::EMPTY},  // dummy
               MCN *parent = nullptr);

  /* @brief return the best children
   * @params c constant of the formula.
   * @return the node it chose.
   */
  MCN *bestChild(const double &c) const;

  /* @brief make a final decision to choose a children.
   * @params c constant of the formula.
   * @params turn how many turns it is.
   * @return the node it chose.
   */
  MCN *finalDecision(const double &c, int turn) const;

  /* @brief value the node.
   * @params c constatn of the formula.
   * @return the value.
   */
  double value(const double &c) const;

  /* @brief get a list of children.
   * @return list of children.
   */
  QList<MCN *> children() const;

  /* @brief get its parent.
   * @return its parent.
   */
  MCN *parent() const;

  /* @brief expand this node.
   * @return the new children node.
   */
  MCN *expand();

  /* @brief update this node's reward
   * @params delta delta of the reward
   */
  void backUp(int delta);

  /* @brief get the state of the node.
   * @return state of the node.
   */
  inline State state() const { return state_; }

  /* @brief get the type of the node.
   * @return type of the node.
   */
  inline Type type() const { return type_; }

  /* @brief get the depth of the node.
   * @return depth of the node.
   */
  inline unsigned depth() const { return depth_; }

  /* @brief judge if the node is expandable.
   * @return if the node is expandable.
   */
  inline bool expandable() { return remainMovement_.size() > 0; }

  /* @brief if the node is terminal.
   * @return if the node is terminal.
   */
  inline bool terminal() { return !expandable() && children().size() == 0; }

  /* @brief get the move from its parent to itself.
   * @return the move from its parent to itself.
   */
  inline Move move() { return move_; }

 protected:
  /* @brief protected constructor.
   * @params parent of QObject.
   */
  explicit MCN(QObject *parent = nullptr);

 private:
  // state of the node.
  State state_;

  // player of the node.
  Type type_;

  // depth of the node.
  unsigned depth_;

  // move form its parent to itself.
  Move move_;

  // reference of the rule.
  Rule const &rule_;

  // remain movement not expanded.
  Movement remainMovement_;

  // N in the formula.
  int N_{0};

  // Q in the formula.
  int Q_{0};

  /* @brief get the priority level of (x, y)
   * @params x
   * @params y
   * @return priority level
   */
  int priorityOf(size_t const &x, size_t const &y) const;
};

#endif  // MCN_H
