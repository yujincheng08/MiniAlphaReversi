#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "config.h"

/*
 * A piece to draw
 */

class Piece : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  using Type = Config::Type;
  // pixmap and scale of all type of piece.
  static QPixmap *blackPixmap;
  static QPixmap *whitePixmap;
  static QPixmap *emptyPixmap;
  static qreal whiteScale;
  static qreal blackScale;
  static bool initialized;

  /* @brief initialize pixmaps and scale.
   */
  static void initialize();

 public:
  explicit Piece(QGraphicsItem *parent = nullptr);

 public slots:
  /* @brief flip the piece.
   */
  void flip();

  /* @brief rest the piece.
   */
  void reset();

  /* @brief set the type of the piece.
   */
  void laozi(Type const &type);

  /* @brief set it avaliable.
   * @params type which type of avaliable
   */
  void setAvaliable(Type const &type);

  /* @brief reset its avaliable state.
   */
  void unsetAvaliable();

 private:
  // type of the piece.
  Type type_{Config::EMPTY};

  // update the piece to the widget.
  void updatePiece();
};

#endif  // PIECE_H
