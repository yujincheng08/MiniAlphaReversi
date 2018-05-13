#include "piece.h"

QPixmap *Piece::blackPixmap = nullptr;
QPixmap *Piece::whitePixmap = nullptr;
QPixmap *Piece::emptyPixmap = nullptr;
bool Piece::initialized = false;
qreal Piece::whiteScale = 0;
qreal Piece::blackScale = 0;

void Piece::initialize() {
  if (initialized) return;
  // new all pixmap
  blackPixmap = new QPixmap(":/image/BlackChess.png");
  whitePixmap = new QPixmap(":/image/WhiteChess.png");
  emptyPixmap = new QPixmap;
  // calculate the scale
  whiteScale = qMin((qreal)Config::PIECE_SIZE / whitePixmap->width(),
                    (qreal)Config::PIECE_SIZE / whitePixmap->height());
  blackScale = qMin((qreal)Config::PIECE_SIZE / blackPixmap->width(),
                    (qreal)Config::PIECE_SIZE / blackPixmap->height());
  initialized = true;
}

Piece::Piece(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
  initialize();
  // set it smooth.
  setTransformationMode(Qt::SmoothTransformation);
}

void Piece::flip() {
  // flip and update.
  type_ = ~type_;
  updatePiece();
}

void Piece::reset() {
  // set it empty.
  laozi(Config::EMPTY);
}

void Piece::laozi(const Piece::Type &type) {
  // set type and update.
  type_ = type;
  updatePiece();
}

void Piece::setAvaliable(const Piece::Type &type) {
  if (!initialized) return;
  // set avalialbe opacity.
  setOpacity(0.4);
  laozi(type);
}

void Piece::unsetAvaliable() {
  // set to untransparent.
  setOpacity(1);
  laozi(Config::EMPTY);
}

void Piece::updatePiece() {
  if (!initialized) return;
  // set pixmap and update.
  switch (type_) {
    case Config::WHITE:
      setPixmap(*whitePixmap);
      setScale(whiteScale);
      break;
    case Config::BLACK:
      setPixmap(*blackPixmap);
      setScale(blackScale);
      break;
    case Config::EMPTY:
      setPixmap(*emptyPixmap);
      break;
  }
  update();
}
