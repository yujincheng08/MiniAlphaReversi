#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include <QVector>
#include "logic/move.h"
#include "logic/position.h"

namespace Config {
static unsigned constexpr SIZE = 8U;

static unsigned constexpr PIECE_SIZE = 50u;

static unsigned constexpr WINDOW_WIDTH = (SIZE + 2) * PIECE_SIZE;
static unsigned constexpr WINDOW_HEIGHT = (SIZE + 2) * PIECE_SIZE;

static int constexpr timeLimit = 30000;

static unsigned constexpr laterStage = 54u;

enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

static Type constexpr first = BLACK;

using State = QVector<QVector<Config::Type>>;

using Movement = QList<Move>;

using PriorityTable = QList<QVector<Position>>;

// The constant of calculating the value used by choosing the best child.
static double constexpr Cp = 1.0;

static unsigned constexpr simulationTime = 3u;  // Generate three times.

inline Type operator~(Type const &type) {
  return type == BLACK ? WHITE : type != EMPTY ? BLACK : EMPTY;
}

inline bool operator!(Type const &type) { return type != EMPTY; }

inline State operator+=(State &state, Movement const &movement) {
  for (auto const &move : movement) state[move.x()][move.y()] = move.type();
  return state;
}

inline State operator+(State const &state, Movement const &movement) {
  State newState = state;
  newState += movement;
  return newState;
}
static Movement const initPieces = {{SIZE / 2U, SIZE / 2U, WHITE},
                                    {SIZE / 2U, SIZE / 2U - 1, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U - 1, WHITE}};

static PriorityTable const priorityTable = {
    {{0, 0}, {0, 7}, {7, 0}, {7, 7}},
    {{0, 2}, {0, 5}, {2, 0}, {2, 7}, {5, 0}, {5, 7}, {7, 2}, {7, 5}},
    {{2, 2}, {2, 5}, {5, 2}, {5, 5}},
    {{0, 3}, {0, 4}, {3, 0}, {3, 7}, {4, 0}, {4, 7}, {7, 3}, {7, 4}},
    {{2, 3}, {2, 4}, {3, 2}, {3, 5}, {4, 2}, {4, 5}, {5, 3}, {5, 4}},
    {{3, 3}, {3, 4}, {4, 3}, {4, 4}},
    {{1, 3}, {1, 4}, {3, 1}, {3, 6}, {4, 1}, {4, 6}, {6, 3}, {6, 4}},
    {{1, 2}, {1, 5}, {2, 1}, {2, 6}, {5, 1}, {5, 6}, {6, 2}, {6, 5}},
    {{0, 1}, {0, 6}, {1, 0}, {1, 7}, {6, 0}, {6, 7}, {7, 1}, {7, 6}},
    {{1, 1}, {1, 6}, {6, 1}, {6, 6}}};

}  // namespace Config
#endif  // CONFIG_H
