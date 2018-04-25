#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QVector>
#include "piece.h"

class Pieces : public QObject, public QGraphicsItemGroup {
  Q_OBJECT
 public:
  explicit Pieces(QGraphicsItem *parent = nullptr);

 public slots:
  void reset();
  void laozi(Config::Movement const &movement);

 private:
  QVector<QVector<Piece *>> pieces_{Config::SIZE};
};

#endif  // PIECES_H
