#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class Board : public QGraphicsItemGroup {
  // 8x8 size
  static unsigned constexpr SIZE = 8u;
  static unsigned constexpr LINES_COUNT = SIZE + 1u;

public:
  explicit Board(QGraphicsItem *parent = nullptr);

private:
  QGraphicsPixmapItem *background_ =
      new QGraphicsPixmapItem(QPixmap(":/image/ChessBoard.jpg"), this);
  QGraphicsItemGroup *rowLines = new QGraphicsItemGroup(this);
  QGraphicsItemGroup *colLines = new QGraphicsItemGroup(this);

  void drawLines();
};

#endif // BOARD_H
