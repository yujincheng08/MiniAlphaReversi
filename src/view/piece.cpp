#include "piece.h"

QPixmap *Piece::blackPixmap = nullptr;
QPixmap *Piece::whitePixmap = nullptr;
QPixmap *Piece::emptyPixmap = nullptr;
bool Piece::initialized = false;
qreal Piece::whiteScale = 0;
qreal Piece::blackScale = 0;

void Piece::initialize() {
  if (initialized) return;
  blackPixmap = new QPixmap(":/image/BlackChess.png");
  whitePixmap = new QPixmap(":/image/WhiteChess.png");
  emptyPixmap = new QPixmap;
  whiteScale = qMin((qreal)Config::PIECE_SIZE / whitePixmap->width(),
                    (qreal)Config::PIECE_SIZE / whitePixmap->height());
  blackScale = qMin((qreal)Config::PIECE_SIZE / blackPixmap->width(),
                    (qreal)Config::PIECE_SIZE / blackPixmap->height());
  initialized = true;
}

Piece::Piece(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
  initialize();
}

void Piece::flip() {
  type_ = ~type_;
  updatePiece();
}

void Piece::reset() { laozi(Config::EMPTY); }

void Piece::laozi(const Piece::Type &type) {
  type_ = type;
  updatePiece();
}

void Piece::updatePiece() {
  if (!initialized) return;
  switch (type_) {
    case Config::WHITE:
      setPixmap(*whitePixmap);
      setScale(whiteScale);
      break;
    case Config::BLACK:
      setPixmap(*blackPixmap);
      setScale(blackScale);
      break;
    default:
      break;
  }
  update();
}
