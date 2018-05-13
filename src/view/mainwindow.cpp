#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  createWidgets();
  createConnections();
  setCentralWidget(widget);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  adjustSize();
}

MainWindow::~MainWindow() {}

void MainWindow::reset(Config::Type AIType) {
  gameview->reset();
  rule_->reset();
  mct_->reset(AIType);
}

void MainWindow::createWidgets() {
  // create widgets and manage layout.
  auto mainLayout = new QVBoxLayout();
  gameview->setSceneRect(
      QRect(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
  gameview->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  gameview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gameview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mainLayout->addWidget(gameview);
  mainLayout->setMargin(0);
  auto buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(AIFirst, 1);
  buttonLayout->addWidget(PlayerFirst, 1);
  mainLayout->addLayout(buttonLayout);
  widget->setLayout(mainLayout);
}

void MainWindow::createConnections() {
  connect(gameview, &GameView::clicked, rule_, &Rule::laozi);

  connect(rule_, &Rule::changed, gameview, &GameView::laozi);
  connect(rule_, &Rule::pass, mct_, &MCT::search, Qt::QueuedConnection);
  connect(rule_, &Rule::gameOver, this, [this]() {
    gameview->disable();
    // judge who won.
    auto white = rule_->judge(Config::WHITE);
    auto black = rule_->judge(Config::BLACK);
    QString result;
    if (black && white)
      result = "both";
    else if (black)
      result = "black";
    else if (white)
      result = "white";
    QMessageBox::information(this, "Game over", result + " won!");
  });
  connect(mct_, &MCT::decision, rule_, &Rule::laozi, Qt::QueuedConnection);
  connect(gameview, &GameView::clicked, mct_, &MCT::laozi,
          Qt::QueuedConnection);
  connect(mct_, &MCT::disableBoard, gameview, &GameView::disable,
          Qt::QueuedConnection);
  connect(AIFirst, &QPushButton::clicked, this, [this]() {
    reset(Config::BLACK);
    gameview->disable(false);
  });

  connect(AIFirst, &QPushButton::clicked, mct_, &MCT::search,
          Qt::QueuedConnection);
  connect(PlayerFirst, &QPushButton::clicked, this, [this]() {
    reset(Config::WHITE);
    gameview->disable(false);
  });
}
