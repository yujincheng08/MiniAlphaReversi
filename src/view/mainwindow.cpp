#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setCentralWidget(gameview);
}

MainWindow::~MainWindow() {}
