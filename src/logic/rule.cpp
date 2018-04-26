#include "rule.h"
#include <QDebug>
#include <iostream>

Rule::Rule(QObject *parent) : QObject(parent) { reset(); }

void Rule::reset() {
  for (auto &row : state_) {
    row.fill(Config::EMPTY, Config::SIZE);
  }
  for (auto const &init : Config::initPieces) {
    Q_ASSERT(init.x() < Config::SIZE && init.y() < Config::SIZE);
    state_[init.x()][init.y()] = init.type();
  }
  player_ = Config::first;
  // emit changed(Config::initPieces, availableMovement());
}

void Rule::laozi(size_t const &x, size_t const &y) {
  Q_ASSERT(player_ != Config::EMPTY && x < Config::SIZE && y < Config::SIZE);
  if (valid(x, y))
    state_[x][y] = player_;
  else
    return;
  Movement movement;
  movement.push_back({x, y, player_});
  // Left to right
  if (x < Config::SIZE - 2u && state_[x + 1u][y] == ~player_) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x + j][y] = player_;
          movement.push_back({x + j, y, player_});
        }
      if (!!state_[x + i][y]) break;
    }
  }

  // Right to left
  if (x > 2u && state_[x - 1u][y] == ~player_) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x - j][y] = player_;
          movement.push_back({x - j, y, player_});
        }
      if (!!state_[x - i][y]) break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && state_[x][y + 1u] == ~player_) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x][y + i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x][y + j] = player_;
          movement.push_back({x, y + j, player_});
        }
      if (!!state_[x][y + i]) break;
    }
  }

  // Bottom to top
  if (y > 2u && state_[x][y - 1u] == ~player_) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x][y - i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x][y - j] = player_;
          movement.push_back({x, y - j, player_});
        }
      if (!!state_[x][y - i]) break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      state_[x + 1u][y + 1u] == ~player_) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y + i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x + j][y + j] = player_;
          movement.push_back({x + j, y + j, player_});
        }
      if (!!state_[x + i][y + i]) break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u && state_[x - 1u][y + 1u] == ~player_) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y + i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x - j][y + j] = player_;
          movement.push_back({x - j, y + j, player_});
        }
      if (!!state_[x - i][y + i]) break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u && state_[x + 1u][y - 1u] == ~player_) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x + i][y - i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x + j][y - j] = player_;
          movement.push_back({x + j, y - j, player_});
        }
      if (!!state_[x + i][y - i]) break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && state_[x - 1u][y - 1u] == ~player_) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state_[x - i][y - i] == player_)
        for (size_t j = 1u; j < i; ++j) {
          state_[x - j][y - j] = player_;
          movement.push_back({x - j, y - j, player_});
        }
      if (!!state_[x - i][y - i]) break;
    }
  }
  player_ = ~player_;
  auto available = availableMovement();
  if (available.size() == 0) player_ = ~player_;
  available = availableMovement();

  emit changed(movement, available);

  whiteCount = 0;
  blackCount = 0;
  //   check the state_ map
  for (unsigned int i = 0; i < Config::SIZE; i++) {
    for (unsigned int j = 0; j < Config::SIZE; j++) {
      if (state_[i][j] == Config::WHITE) {
        whiteCount++;
      }
      if (state_[i][j] == Config::BLACK) {
        blackCount++;
      }
      std::cout << (char)state_[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  if (isGameOver()) {
    qDebug() << "Game Over";
  }
}

bool Rule::valid(size_t const &x, size_t const &y, Config::Type const &player,
                 State const &state) const {
  Q_ASSERT(!player && x < Config::SIZE && y < Config::SIZE);
  if (!state[x][y]) return false;

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

// Rule::Movement Rule::priorityMoves(Config::PriorityTable const
// &priorityTable,
//                                   Config::Type const &player,
//                                   const State &state) const {
//  Movement movement;
//  for (auto const &level : priorityTable) {
//    for (auto const &position : level) {
//      if (valid(position.x(), position.y(), player, state))
//        movement.push_back({position.x(), position.y(), player});
//    }
//    if (!movement.empty()) break;
//  }
//  return movement;
//}

bool Rule::isGameOver() {
  qDebug() << "white: " << whiteCount;
  qDebug() << "black: " << blackCount;

  // the map is full
  if ((whiteCount + blackCount == Config::SIZE * Config::SIZE)
      // both of black and white can not move
      || (!whiteMovable && !blackMovalbe)) {
    return true;
  }
  return false;
}
