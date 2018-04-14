#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include "config.h"

class Piece : QGraphicsPixmapItem {
  using Type = Config::Type;

  static QPixmap *blackPixmap;
  static QPixmap *whitePixmap;
  static QPixmap *emptyPixmap;
  static bool initilized;

  static void initialize();

 public:
  explicit Piece(QGraphicsItem *parent = nullptr);

 public slots:
  void flip();

  void laozi(Type const &type);

 private:
  Type type_{Config::EMPTY};

  void updatePiece();
};

#endif  // PIECE_H
