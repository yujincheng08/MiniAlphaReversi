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
  explicit MCT(QObject *parent = nullptr);
  int defaultPolicy(MCN *node) const;
  MCN *treePolicy() const;
  virtual ~MCT();

 signals:
  void decision(size_t const &x, size_t const &y);
  void disableBoard(bool disabled);
 public slots:
  void laozi(size_t const &x, size_t const &y);
  void reset(Config::Type type);
  void search();

 private:
  QThread *thread_{new QThread(this)};
  MCN *root{nullptr};
  // QThreadPool threadPool_{this}; // TODO: using it.
  Rule rule_{this};
  Config::Type type_;

  void updateTree(size_t const &x, size_t const &y);

  void backUp(MCN *node, unsigned const &delta) const;
};

#endif  // MCT_H
