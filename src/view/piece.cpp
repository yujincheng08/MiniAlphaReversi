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
  type_ = ~type_;
  updatePiece();
}

void Piece::laozi(const Piece::Type &type) {
  if (!!type_) {
    type_ = type;
    updatePiece();
  }
}

void Piece::updatePiece() {
  switch (type_) {
  case Config::WHITE:
    setPixmap(*whitePixmap);
    break;
  case Config::BLACK:
    setPixmap(*blackPixmap);
    break;
  default:
    break;
  }
  update();
}
