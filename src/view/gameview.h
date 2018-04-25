#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "board.h"
#include "pieces.h"

class GameView : public QGraphicsView {
  Q_OBJECT
 public:
  explicit GameView(QWidget *parent = nullptr);
 signals:
  void clicked(size_t const &x, size_t const &y);

 public slots:
  void laozi(Config::Movement const &movement);
  inline void reset() { pieces_->reset(); }

 protected:
  virtual void mousePressEvent(QMouseEvent *event) override;

 private:
  QGraphicsScene *scene_{new QGraphicsScene(this)};
  Board *board_{new Board};
  Pieces *pieces_{new Pieces};
};

#endif  // GAMEVIEW_H
