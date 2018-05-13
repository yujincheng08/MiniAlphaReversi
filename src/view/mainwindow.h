#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "ai/mct.h"
#include "gameview.h"
#include "logic/rule.h"

/*
 * The main window
 */

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /* @brief constructor.
   * @params parent its parent.
   */
  explicit MainWindow(QWidget *parent = nullptr);

  /* @brief disconstructor
   */
  virtual ~MainWindow();

 public slots:
  /* @brief reset.
   * @params AIType the type piece of the AI.
   */
  void reset(Config::Type AIType);

 private:
  // the rule.
  Rule *rule_{new Rule(this)};

  // the game. view
  GameView *gameview{new GameView()};

  // the MCT.
  MCT *mct_{new MCT()};

  // two button.
  QPushButton *AIFirst{new QPushButton("AI First")};
  QPushButton *PlayerFirst{new QPushButton("Player First")};

  // warpper widget.
  QWidget *widget{new QWidget(this)};

  /* @brief create widgets.
   */
  void createWidgets();

  /* @brief create connections.
   */
  void createConnections();
};
#endif  // MAINWINDOW_H
