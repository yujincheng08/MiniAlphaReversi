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
  void laozi(Config::Movement const &movement,
             Config::Movement const &avalialbe);
  inline void reset() { pieces_->reset(); }
  inline void disable(bool disabled = true) { disabled_ = disabled; }

 protected:
  virtual void mousePressEvent(QMouseEvent *event) override;

 private:
  QGraphicsScene *scene_{new QGraphicsScene(this)};
  Board *board_{new Board};
  Pieces *pieces_{new Pieces};
  bool disabled_{true};
};

#endif  // GAMEVIEW_H
