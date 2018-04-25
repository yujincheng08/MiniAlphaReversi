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
  explicit MCT(Config::State const &state, Config::Type const &type,
               QObject *parent = nullptr);
  unsigned defaultPolicy(MCN *node) const;
  MCN *treePolicy() const;
  Move search();

 signals:

 public slots:

 private:
  MCN *root;
  QThreadPool threadPool_{this};
  Rule rule_{this};

  void backUp(MCN *node, unsigned const &delta) const;
  bool intime();
};

#endif  // MCT_H
