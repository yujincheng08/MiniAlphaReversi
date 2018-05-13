#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "board.h"
#include "pieces.h"

/*
 * The widget to show the game.
 */

class GameView : public QGraphicsView {
  Q_OBJECT
 public:
  /* @brief constructor
   * @params parent its parent
   */
  explicit GameView(QWidget *parent = nullptr);
 signals:
  /* @brief signal emitted when (x, y) is clicked.
   * @params x
   * @params y
   */
  void clicked(size_t const &x, size_t const &y);

 public slots:
  /* @brief laozi slot triggered when someone succefully laozis.
   * @params movement the movement.
   * @params alaiable the avaliable movement.
   */
  void laozi(Config::Movement const &movement,
             Config::Movement const &avalialbe);

  /* @brief reset the gameview
   */
  inline void reset() { pieces_->reset(); }

  /* @brief diable the board
   * @params disabled disable or not
   */
  inline void disable(bool disabled = true) { disabled_ = disabled; }

 protected:
  /* @brief event when the view is clicked
   * @params event the mouse event
   */
  virtual void mousePressEvent(QMouseEvent *event) override;

 private:
  // graphics scene
  QGraphicsScene *scene_{new QGraphicsScene(this)};

  // the borad
  Board *board_{new Board};

  // all pieces
  Pieces *pieces_{new Pieces};

  // if the board is disabled
  bool disabled_{true};
};

#endif  // GAMEVIEW_H
