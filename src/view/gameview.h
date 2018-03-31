#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "board.h"

#include <QGraphicsScene>
#include <QGraphicsView>

class GameView : public QGraphicsView {

public:
  explicit GameView(QWidget *parent = nullptr);

private:
  QGraphicsScene *scene_ = new QGraphicsScene(this);
  Board *board_ = new Board;
};

#endif // GAMEVIEW_H
