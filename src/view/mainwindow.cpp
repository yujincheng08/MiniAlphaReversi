#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setCentralWidget(gameview);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  gameview->setSceneRect(
      QRect(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
  gameview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gameview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFixedSize(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
  createConnections();
  reset();
}

MainWindow::~MainWindow() {}

void MainWindow::reset() {
  gameview->reset();
  rule_->reset();
}

void MainWindow::createConnections() {
  connect(gameview, &GameView::clicked, rule_, &Rule::laozi);
  connect(rule_, &Rule::changed, gameview, &GameView::laozi);
}
