#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsGridLayout>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include "config.h"

class Board : public QGraphicsItemGroup {
  static unsigned constexpr LINES_COUNT = Config::SIZE + 1u;

 public:
  explicit Board(QGraphicsItem *parent = nullptr);

 private:
  QGraphicsPixmapItem *background_ =
      new QGraphicsPixmapItem(QPixmap(":/image/ChessBoard.jpg"), this);
  QGraphicsItemGroup *rowLines_{new QGraphicsItemGroup(this)};
  QGraphicsItemGroup *colLines_{new QGraphicsItemGroup(this)};

  void drawLines();
  void addPieces();
};

#endif  // BOARD_H
