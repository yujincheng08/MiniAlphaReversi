#include "board.h"

Board::Board(QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
  addToGroup(background_);
  drawLines();
}

void Board::drawLines() {
  for (unsigned i = 0; i < LINES_COUNT; ++i) {
    new QGraphicsLineItem(Config::PIECE_SIZE + i * Config::PIECE_SIZE,
                          Config::PIECE_SIZE,
                          Config::PIECE_SIZE + i * Config::PIECE_SIZE,
                          (1 + Config::SIZE) * Config::PIECE_SIZE, colLines);
  }

  for (unsigned i = 0; i < LINES_COUNT; ++i) {
    new QGraphicsLineItem(
        Config::PIECE_SIZE, Config::PIECE_SIZE + i * Config::PIECE_SIZE,
        (Config::SIZE + 1) * Config::PIECE_SIZE,
        Config::PIECE_SIZE + i * Config::PIECE_SIZE, rowLines);
  }
}
