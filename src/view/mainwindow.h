#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ai/mct.h"
#include "gameview.h"
#include "logic/rule.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

 public slots:
  void reset();

 private:
  Rule *rule_{new Rule(this)};
  GameView *gameview{new GameView(this)};
  MCT *mct_{new MCT()};

  void createConnections();
};
#endif  // MAINWINDOW_H
