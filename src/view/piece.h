#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>

class Piece : QGraphicsPixmapItem {

  static QPixmap *blackPixmap;
  static QPixmap *whitePixmap;
  static QPixmap *emptyPixmap;
  static bool initilized;

  static void initialize();

public:
  enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

  explicit Piece(QGraphicsItem *parent = nullptr);

public slots:
  void flip();

  void laozi(Type const &type);

private:
  Type type_ = EMPTY;

  void updatePiece();
};

#endif // PIECE_H
