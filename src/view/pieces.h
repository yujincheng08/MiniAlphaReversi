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
  void unsetAvaliable();
  void setAvaliable(Config::Movement const &avaliable);

 private:
  QVector<QVector<Piece *>> pieces_{Config::SIZE};
  Config::Movement lastAvaliable_;
};

#endif  // PIECES_H
