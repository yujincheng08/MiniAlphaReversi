#include "gameview.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent) {
  setScene(scene_);
  scene_->addItem(board_);
}
