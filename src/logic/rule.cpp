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
  emit changed(Config::initPieces, availableMovement());
}

void Rule::laozi(size_t const &x, size_t const &y) {
  Q_ASSERT(player_ != Config::EMPTY && x < Config::SIZE && y < Config::SIZE);
  auto movement = apply(state_, {x, y, player_});
  if (movement.size() == 0) return;
  state_ += movement;
  player_ = ~player_;
  auto available = availableMovement();
  if (available.size() == 0) {
    player_ = ~player_;
    available = availableMovement();
    if (available.size() == 0) {
      emit changed(movement, available);
      emit gameOver();
      qDebug() << "Game over";
      return;
    } else
      emit pass();
  }

  emit changed(movement, available);
}

bool Rule::judge(State const &state, Config::Type const &player) const {
  Q_ASSERT(player != Config::EMPTY);
  unsigned white = 0u;
  unsigned black = 0u;
  for (unsigned i = 0; i < Config::SIZE; ++i)
    for (unsigned j = 0; j < Config::SIZE; ++j)
      if (state[i][j] == Config::WHITE)
        ++white;
      else if (state[i][j] == Config::BLACK)
        ++black;
  return player == Config::BLACK ? black >= white : white >= black;
}

bool Rule::valid(size_t const &x, size_t const &y, Config::Type const &player,
                 State const &state) const {
  Q_ASSERT(x < Config::SIZE && y < Config::SIZE);
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

  // to bottom righ
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

const Rule::Movement Rule::apply(const Rule::State &state,
                                 const Move &move) const {
  auto x = move.x();
  auto y = move.y();
  auto player = move.type();
  Q_ASSERT(x < Config::SIZE && y < Config::SIZE);
  Movement movement;
  if (valid(x, y, player, state))
    movement.push_back({x, y, player});
  else
    return {};
  // Left to right
  if (x < Config::SIZE - 2u && state[x + 1u][y] == ~player) {
    auto range = Config::SIZE - x;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y] == player)
        for (size_t j = 1u; j < i; ++j) movement.push_back({x + j, y, player});
      if (!!state[x + i][y]) break;
    }
  }

  // Right to left
  if (x > 2u && state[x - 1u][y] == ~player) {
    auto range = x + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y] == player)
        for (size_t j = 1u; j < i; ++j) {
          movement.push_back({x - j, y, player});
        }
      if (!!state[x - i][y]) break;
    }
  }

  // Top to bottom
  if (y < Config::SIZE - 2u && state[x][y + 1u] == ~player) {
    auto range = Config::SIZE - y;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x][y + i] == player)
        for (size_t j = 1u; j < i; ++j) {
          movement.push_back({x, y + j, player});
        }
      if (!!state[x][y + i]) break;
    }
  }

  // Bottom to top
  if (y > 2u && state[x][y - 1u] == ~player) {
    auto range = y + 1u;
    for (size_t i = 2u; i < range; ++i) {
      if (state[x][y - i] == player)
        for (size_t j = 1u; j < i; ++j) movement.push_back({x, y - j, player});
      if (!!state[x][y - i]) break;
    }
  }

  // to topright
  if (x < Config::SIZE - 2u && y < Config::SIZE - 1u &&
      state[x + 1u][y + 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y + i] == player)
        for (size_t j = 1u; j < i; ++j)
          movement.push_back({x + j, y + j, player});
      if (!!state[x + i][y + i]) break;
    }
  }

  // to topleft
  if (x > 2u && y < Config::SIZE - 2u && state[x - 1u][y + 1u] == ~player) {
    auto range = qMin(x + 1u, Config::SIZE - y);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y + i] == player)
        for (size_t j = 1u; j < i; ++j)
          movement.push_back({x - j, y + j, player});
      if (!!state[x - i][y + i]) break;
    }
  }

  // to bottom right
  if (x < Config::SIZE - 2u && y > 2u && state[x + 1u][y - 1u] == ~player) {
    auto range = qMin(Config::SIZE - x, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x + i][y - i] == player)
        for (size_t j = 1u; j < i; ++j)
          movement.push_back({x + j, y - j, player});
      if (!!state[x + i][y - i]) break;
    }
  }

  // to bottom left
  if (x > 2u && y > 2u && state[x - 1u][y - 1u] == ~player) {
    auto range = qMin(x + 1u, y + 1u);
    for (size_t i = 2u; i < range; ++i) {
      if (state[x - i][y - i] == player)
        for (size_t j = 1u; j < i; ++j)
          movement.push_back({x - j, y - j, player});
      if (!!state[x - i][y - i]) break;
    }
  }
  return movement;
}
