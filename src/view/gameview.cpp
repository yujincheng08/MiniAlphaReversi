#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent) {
  setScene(scene_);
  scene_->addItem(board_);
  scene_->addItem(pieces_);
}

void GameView::laozi(Config::Movement const &movement,
                     Config::Movement const &avalialbe) {
  pieces_->unsetAvaliable();
  pieces_->laozi(movement);
  pieces_->setAvaliable(avalialbe);
}

void GameView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  // x and y should swap;
  auto x = event->x() / Config::PIECE_SIZE - 1;
  auto y = event->y() / Config::PIECE_SIZE - 1;
  if (x >= Config::SIZE || y >= Config::SIZE) return;
  emit clicked(x, y);
}
