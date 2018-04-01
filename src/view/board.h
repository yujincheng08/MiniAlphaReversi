#ifndef BOARD_H
#define BOARD_H
#include "config.h"
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class Board : public QGraphicsItemGroup {
  static unsigned constexpr LINES_COUNT = Config::SIZE + 1u;

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
