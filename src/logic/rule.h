#ifndef RULE_H
#define RULE_H

#include "config.h"
#include <QObject>
#include <QPoint>
#include <QVector>

class Rule : public QObject {
  Q_OBJECT

  using Composition = Config::Composition;

public:
  explicit Rule(QObject *parent = nullptr);

  inline const Composition composition() const { return composition_; }

signals:
  void changed(const Movement &movement);
public slots:
  void reset();
  void laozi(size_t const &x, size_t const &y, Config::Type const &player);
  bool valid(size_t const &x, size_t const &y,
             Config::Type const &player) const;

private:
  Composition composition_ = Composition(Config::SIZE);
};

#endif // RULE_H
