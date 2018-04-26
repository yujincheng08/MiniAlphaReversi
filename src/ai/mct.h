#ifndef MCT_H
#define MCT_H

#include <QObject>
#include <QThreadPool>
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
  Move search();

 signals:
  void decision(size_t const &x, size_t const &y);
 public slots:
  void laozi(size_t const &x, size_t const &y);
  void reset(Config::Type type);

 private:
  MCN *root{nullptr};
  QThreadPool threadPool_{this};
  Rule rule_{this};
  Config::Type type_;

  void updateTree(size_t const &x, size_t const &y);

  void backUp(MCN *node, unsigned const &delta) const;
  bool intime();
};

#endif  // MCT_H
