#include "board.h"

Board::Board(QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
  addToGroup(background_);
  drawLines();
}

void Board::drawLines() {
  for (unsigned i = 0; i < LINES_COUNT; ++i) {
    new QGraphicsLineItem(10 + i * 10, 10, 10 + i * 10, 90, colLines);
  }

  for (unsigned i = 0; i < LINES_COUNT; ++i) {
    new QGraphicsLineItem(10, 10 + i * 10, 90, 10 + i * 10, rowLines);
  }
}
