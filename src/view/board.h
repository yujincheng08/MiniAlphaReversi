#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsGridLayout>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include "config.h"

/*
 * The Board to draw
 */

class Board : public QGraphicsItemGroup {
  // lines in the board.
  static unsigned constexpr LINES_COUNT = Config::SIZE + 1u;

 public:
  /* @brief constructor.
   */
  explicit Board(QGraphicsItem *parent = nullptr);

 private:
  // background pixmap
  QGraphicsPixmapItem *background_ =
      new QGraphicsPixmapItem(QPixmap(":/image/ChessBoard.jpg"), this);
  // row lines group
  QGraphicsItemGroup *rowLines_{new QGraphicsItemGroup(this)};
  // column lines group
  QGraphicsItemGroup *colLines_{new QGraphicsItemGroup(this)};

  /* @breif draw lines in the board.
   */
  void drawLines();
};

#endif  // BOARD_H
