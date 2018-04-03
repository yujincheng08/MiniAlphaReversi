#include "rule.h"

Rule::Rule(QObject *parent) : QObject(parent) { reset(); }

void Rule::reset() {
  for (auto &row : composition_) {
    row.fill(Config::EMPTY, Config::SIZE);
  }
  for (auto &init : Config::initPieces) {
    Q_ASSERT(init.x() < Config::SIZE && init.y() < Config::SIZE);
    composition_[init.x()][init.y()] = init.type();
  }
  emit changed(Config::initPieces);
}

void Rule::laozi(const size_t &x, const size_t &y, const Config::Type &player) {
  Q_ASSERT(player != Config::EMPTY && x < Config::SIZE && y < Config::SIZE);
  if (valid(x, y, player))
    composition_[x][y] = player;
  Movement movement;
  // Left to right
  if (x < Config::SIZE - 2u && composition_[x + 1u][y] == ~player) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y] == player)
        for (size_t j = 1u; j < i; ++j) {
          composition_[x + j][y] = player;
          movement.push_back({x + j, y, player});
        }
      if (!!composition_[x + i][y])
        break;
    }
  }

  // Right to left
  if (x > 2u && composition_[x - 1u][y] == ~player) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x - j][y] = player;
          movement.push_back({x - j, y, player});
        }
      if (!!composition_[x - i][y])
        break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && composition_[x][y + 1u] == ~player) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x][y + j] = player;
          movement.push_back({x, y + j, player});
        }
      if (!!composition_[x][y + i])
        break;
    }
  }

  // Bottom to top
  if (y > 2u && composition_[x][y - 1u] == ~player) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x][y - j] = player;
          movement.push_back({x, y - j, player});
        }
      if (!!composition_[x][y - i])
        break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      composition_[x + 1u][y + 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x + j][y + j] = player;
          movement.push_back({x + j, y + j, player});
        }
      if (!!composition_[x + i][y + i])
        break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u &&
      composition_[x - 1u][y + 1u] == ~player) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x - j][y + j] = player;
          movement.push_back({x - j, y + j, player});
        }
      if (!!composition_[x - i][y + i])
        break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u &&
      composition_[x + 1u][y - 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x + j][y - j] = player;
          movement.push_back({x + j, y - j, player});
        }
      if (!!composition_[x + i][y - i])
        break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && composition_[x - 1u][y - 1u] == ~player) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          composition_[x - j][y - j] = player;
          movement.push_back({x - j, y - j, player});
        }
      if (!!composition_[x - i][y - i])
        break;
    }
  }
  emit changed(movement);
}

bool Rule::valid(const size_t &x, const size_t &y,
                 const Config::Type &player) const {
  Q_ASSERT(!player && x < Config::SIZE && y < Config::SIZE);
  if (!!composition_[x][y])
    return false;

  // Left to right
  if (x < Config::SIZE - 2u && composition_[x + 1u][y] == ~player) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y] == player)
        return true;
      if (!!composition_[x + i][y])
        break;
    }
  }

  // Right to left
  if (x > 2u && composition_[x - 1u][y] == ~player) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y] == player)
        return true;
      if (!!composition_[x - i][y])
        break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && composition_[x][y + 1u] == ~player) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x][y + i] == player)
        return true;
      if (!!composition_[x][y + i])
        break;
    }
  }

  // Bottom to top
  if (y > 2u && composition_[x][y - 1u] == ~player) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x][y - i] == player)
        return true;
      if (!!composition_[x][y - i])
        break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      composition_[x + 1u][y + 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y + i] == player)
        return true;
      if (!!composition_[x + i][y + i])
        break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u &&
      composition_[x - 1u][y + 1u] == ~player) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y + i] == player)
        return true;
      if (!!composition_[x - i][y + i])
        break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u &&
      composition_[x + 1u][y - 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x + i][y - i] == player)
        return true;
      if (!!composition_[x + i][y - i])
        break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && composition_[x - 1u][y - 1u] == ~player) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (composition_[x - i][y - i] == player)
        return true;
      if (!!composition_[x - i][y - i])
        break;
    }
  }
  return false;
}
