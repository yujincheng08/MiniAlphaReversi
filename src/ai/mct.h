#ifndef MCT_H
#define MCT_H

#include <QObject>
#include <QSemaphore>
#include <QThread>
#include <QThreadPool>
#include <QTime>
#include "config.h"
#include "mcn.h"

/*
 * Mento Carlo Tree
 */

class MCT : public QObject {
  Q_OBJECT
 public:
  /* @brief construct of MCT.
   * @params parent its parent.
   */
  explicit MCT(QObject *parent = nullptr);

  /* @brief apply default policy to the node.
   * @params node the node to apply policy.
   * @return the reward of the node.
   */
  int defaultPolicy(MCN *node) const;

  /* @brief apply tree policy and get a new node.
   * @return the new node.
   */
  MCN *treePolicy() const;

  /* @brief deconstructor, for deleting root MCN
   */
  virtual ~MCT();

 signals:
  /* @brief signal emitted when MCT makes a dicision.
   * @params x
   * @params y
   */
  void decision(size_t const &x, size_t const &y);

  /* @brief signal to disable or not the board.
   * @params disabled disable or not.
   */
  void disableBoard(bool disabled);
 public slots:
  /* @brief signal to trigger when player laozis.
   * @params x
   * @params y
   */
  void laozi(size_t const &x, size_t const &y);

  /* @brief reset the MCT
   * @params type the type of piece MCT can make disicions.
   */
  void reset(Config::Type type);

  /* @brief perform a search from the root MCN.
   */
  void search();

 private:
  // The thread MCT runs on.
  QThread *thread_{new QThread(this)};

  // The root MCN. It should be changed from time to time.
  MCN *root{nullptr};

  // The rule.
  Rule rule_{this};

  // The type of piece MCT can make dicisions.
  Config::Type type_;

  /* @brief update the tree by changing root when (x, y) is filled.
   * @params x
   * @params y
   */
  void updateTree(size_t const &x, size_t const &y);

  /* @brief backup the node with delta.
   * @params node node to update.
   * @params delta of the reward.
   */
  void backUp(MCN *node, int const &delta) const;
};

#endif  // MCT_H
