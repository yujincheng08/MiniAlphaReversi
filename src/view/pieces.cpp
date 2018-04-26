#include "pieces.h"
#include "config.h"

Pieces::Pieces(QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
  for (unsigned i = 0u; i < Config::SIZE; ++i) {
    pieces_[i].resize(Config::SIZE);
    for (unsigned j = 0u; j < Config::SIZE; ++j) {
      auto piece = new Piece(this);
      piece->setX((j + 1) * Config::PIECE_SIZE);
      piece->setY((i + 1) * Config::PIECE_SIZE);
      pieces_[i][j] = piece;
    }
  }
  reset();
}

void Pieces::reset() {
  for (auto &row : pieces_)
    for (auto &piece : row) piece->reset();
  for (auto const &init : Config::initPieces)
    pieces_[init.x()][init.y()]->laozi(init.type());
}

void Pieces::laozi(const Config::Movement &movement) {
  for (auto const &move : movement) {
    pieces_[move.x()][move.y()]->laozi(move.type());
  }
}

void Pieces::unsetAvaliable() {
  for (auto const &move : lastAvaliable_) {
    pieces_[move.x()][move.y()]->unsetAvaliable();
  }
  lastAvaliable_.erase(lastAvaliable_.begin(), lastAvaliable_.end());
}

void Pieces::setAvaliable(Config::Movement const &avaliable) {
  for (auto const &move : avaliable) {
    pieces_[move.x()][move.y()]->setAvaliable(move.type());
  }
  lastAvaliable_ = avaliable;
}
