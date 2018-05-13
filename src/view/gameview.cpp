#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent) {
  // set the secne and add borad and piece
  setScene(scene_);
  scene_->addItem(board_);
  scene_->addItem(pieces_);
}

void GameView::laozi(Config::Movement const &movement,
                     Config::Movement const &avalialbe) {
  // unset avaliable and then laozi and set the avaliable
  pieces_->unsetAvaliable();
  pieces_->laozi(movement);
  pieces_->setAvaliable(avalialbe);
}

void GameView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  if (disabled_) return;
  // calculate the x and y
  auto x = event->x() / Config::PIECE_SIZE - 1;
  auto y = event->y() / Config::PIECE_SIZE - 1;
  if (x >= Config::SIZE || y >= Config::SIZE) return;
  // x and y should swap;
  emit clicked(y, x);
}
