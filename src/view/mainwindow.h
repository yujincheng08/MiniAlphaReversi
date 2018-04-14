#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameview.h"

#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

 private:
  GameView *gameview{new GameView(this)};
};
#endif  // MAINWINDOW_H
