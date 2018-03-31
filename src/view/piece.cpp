#include "piece.h"

QPixmap *Piece::blackPixmap = nullptr;
QPixmap *Piece::whitePixmap = nullptr;
QPixmap *Piece::emptyPixmap = nullptr;
bool Piece::initilized = false;

void Piece::initialize() {
  if (initilized)
    return;
  blackPixmap = new QPixmap(":/image/BlackChess.png");
  whitePixmap = new QPixmap(":/image/WhiteChess.png");
  emptyPixmap = new QPixmap;
}

Piece::Piece(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
  initialize();
}

void Piece::flip() {
  switch (type_) {
  case WHITE:
    type_ = BLACK;
    break;
  case BLACK:
    type_ = EMPTY;
    break;
  default:
    break;
  }
  updatePiece();
}

void Piece::laozi(const Piece::Type &type) {
  if (type_ == EMPTY) {
    type_ = type;
    updatePiece();
  }
}

void Piece::updatePiece() {
  switch (type_) {
  case WHITE:
    setPixmap(*whitePixmap);
    break;
  case BLACK:
    setPixmap(*blackPixmap);
    break;
  default:
    break;
  }
  update();
}
