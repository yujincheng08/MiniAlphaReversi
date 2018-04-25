#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "config.h"

class Piece : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  using Type = Config::Type;

  static QPixmap *blackPixmap;
  static QPixmap *whitePixmap;
  static QPixmap *emptyPixmap;
  static qreal whiteScale;
  static qreal blackScale;
  static bool initialized;

  static void initialize();

 public:
  explicit Piece(QGraphicsItem *parent = nullptr);

 public slots:
  void flip();
  void reset();
  void laozi(Type const &type);

 private:
  Type type_{Config::EMPTY};

  void updatePiece();
};

#endif  // PIECE_H
