#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QVector>
#include "piece.h"

/*
 * All the pieces to draw
 */

class Pieces : public QObject, public QGraphicsItemGroup {
  Q_OBJECT
 public:
  explicit Pieces(QGraphicsItem *parent = nullptr);

 public slots:
  /* @brief reset all pieces.
   */
  void reset();

  /* @brief laozi.
   * @params movement the movement.
   */
  void laozi(Config::Movement const &movement);

  /* @brief unset the avaliables.
   */
  void unsetAvaliable();

  /* @brief set avaliable movement.
   * @params avaliable the avaliable movement.
   */
  void setAvaliable(Config::Movement const &avaliable);

 private:
  // pieces.
  QVector<QVector<Piece *>> pieces_{Config::SIZE};

  // last avaliable, for unsetAvaliable.
  Config::Movement lastAvaliable_;
};

#endif  // PIECES_H
