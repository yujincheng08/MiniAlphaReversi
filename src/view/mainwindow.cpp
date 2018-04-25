#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setCentralWidget(gameview);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  gameview->setSceneRect(
      QRect(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
  setFixedSize(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
  createConnections();
  reset();
}

MainWindow::~MainWindow() {}

void MainWindow::reset() {
  rule_->reset();
  gameview->reset();
}

void MainWindow::createConnections() {
  connect(gameview, &GameView::clicked, rule_, &Rule::laozi);
  connect(rule_, &Rule::changed, gameview, &GameView::laozi);
}
