#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "ai/mct.h"
#include "gameview.h"
#include "logic/rule.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow();

 public slots:
  void reset(Config::Type AIType);

 private:
  Rule *rule_{new Rule(this)};
  GameView *gameview{new GameView()};
  MCT *mct_{new MCT()};
  QPushButton *AIFirst{new QPushButton("AI First")};
  QPushButton *PlayerFirst{new QPushButton("Player First")};
  QWidget *widget{new QWidget(this)};

  void createWidgets();
  void createConnections();
};
#endif  // MAINWINDOW_H
