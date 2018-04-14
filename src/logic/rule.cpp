#include "rule.h"

Rule::Rule(QObject *parent) : QObject(parent) { reset(); }

void Rule::reset() {
  for (auto &row : state_) {
    row.fill(Config::EMPTY, Config::SIZE);
  }
  for (auto const &init : Config::initPieces) {
    Q_ASSERT(init.x() < Config::SIZE && init.y() < Config::SIZE);
    state_[init.x()][init.y()] = init.type();
  }
  emit changed(Config::initPieces);
}

void Rule::laozi(size_t const &x, size_t const &y, Config::Type const &player) {
  Q_ASSERT(player != Config::EMPTY && x < Config::SIZE && y < Config::SIZE);
  if (valid(x, y, player)) state_[x][y] = player;
  Movement movement;
  // Left to right
  if (x < Config::SIZE - 2u && state_[x + 1u][y] == ~player) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y] == player)
        for (size_t j = 1u; j < i; ++j) {
          state_[x + j][y] = player;
          movement.push_back({x + j, y, player});
        }
      if (!!state_[x + i][y]) break;
    }
  }

  // Right to left
  if (x > 2u && state_[x - 1u][y] == ~player) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x - j][y] = player;
          movement.push_back({x - j, y, player});
        }
      if (!!state_[x - i][y]) break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && state_[x][y + 1u] == ~player) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x][y + j] = player;
          movement.push_back({x, y + j, player});
        }
      if (!!state_[x][y + i]) break;
    }
  }

  // Bottom to top
  if (y > 2u && state_[x][y - 1u] == ~player) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x][y - j] = player;
          movement.push_back({x, y - j, player});
        }
      if (!!state_[x][y - i]) break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      state_[x + 1u][y + 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x + j][y + j] = player;
          movement.push_back({x + j, y + j, player});
        }
      if (!!state_[x + i][y + i]) break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u && state_[x - 1u][y + 1u] == ~player) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y + i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x - j][y + j] = player;
          movement.push_back({x - j, y + j, player});
        }
      if (!!state_[x - i][y + i]) break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u && state_[x + 1u][y - 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x + j][y - j] = player;
          movement.push_back({x + j, y - j, player});
        }
      if (!!state_[x + i][y - i]) break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && state_[x - 1u][y - 1u] == ~player) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y - i] == player)
        for (size_t j = 2u; j < i; ++j) {
          state_[x - j][y - j] = player;
          movement.push_back({x - j, y - j, player});
        }
      if (!!state_[x - i][y - i]) break;
    }
  }
  emit changed(movement);
}

bool Rule::valid(size_t const &x, size_t const &y, Config::Type const &player,
                 State const &state) const {
  Q_ASSERT(!player && x < Config::SIZE && y < Config::SIZE);
  if (!!state[x][y]) return false;

  // Left to right
  if (x < Config::SIZE - 2u && state[x + 1u][y] == ~player) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y] == player) return true;
      if (!!state[x + i][y]) break;
    }
  }

  // Right to left
  if (x > 2u && state[x - 1u][y] == ~player) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y] == player) return true;
      if (!!state[x - i][y]) break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && state[x][y + 1u] == ~player) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x][y + i] == player) return true;
      if (!!state[x][y + i]) break;
    }
  }

  // Bottom to top
  if (y > 2u && state[x][y - 1u] == ~player) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x][y - i] == player) return true;
      if (!!state[x][y - i]) break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      state[x + 1u][y + 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y + i] == player) return true;
      if (!!state[x + i][y + i]) break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u && state[x - 1u][y + 1u] == ~player) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y + i] == player) return true;
      if (!!state[x - i][y + i]) break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u && state[x + 1u][y - 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y - i] == player) return true;
      if (!!state[x + i][y - i]) break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && state[x - 1u][y - 1u] == ~player) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y - i] == player) return true;
      if (!!state[x - i][y - i]) break;
    }
  }
  return false;
}

Rule::Movement Rule::availableMovement(Config::Type const &player,
                                       const State &state) const {
  Movement movement;
  for (size_t i = 0u; i < Config::SIZE; ++i)
    for (size_t j = 0u; j < Config::SIZE; ++j)
      if (valid(i, j, player, state)) movement.push_back({i, j, player});
  return movement;
}

Rule::Movement Rule::priorityMoves(Config::PriorityTable const &priorityTable,
                                   Config::Type const &player,
                                   const State &state) const {
  Movement movement;
  for (auto const &level : priorityTable) {
    for (auto const &position : level) {
      if (valid(position.x(), position.y(), player, state))
        movement.push_back({position.x(), position.y(), player});
    }
    if (!movement.empty()) break;
  }
  return movement;
}
