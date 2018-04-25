#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setCentralWidget(gameview);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  gameview->setSceneRect(
      QRect(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
  setFixedSize(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
  // setSizePolicy();j
}

MainWindow::~MainWindow() {}
