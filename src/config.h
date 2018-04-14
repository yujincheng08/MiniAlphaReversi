#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include <QVector>
#include "logic/move.h"
#include "logic/position.h"

namespace Config {
static unsigned constexpr SIZE = 8U;

enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

static Type constexpr first = BLACK;

using State = QVector<QVector<Config::Type>>;

using Movement = QList<Move>;

using PriorityTable = QList<QVector<Position>>;

// The constant of calculating the value used by choosing the best chhild.
static double const Cp = 1.0;

inline Type operator~(Type const &type) {
  return type == BLACK ? WHITE : type != EMPTY ? BLACK : EMPTY;
}

inline bool operator!(Type const &type) { return type != EMPTY; }

inline State operator+(State const &state, Movement const &movement) {
  State newState = state;
  for (auto const &move : movement) {
    newState[move.x()][move.y()] = move.type();
  }
  return newState;
}

static Movement const initPieces = {{SIZE / 2U, SIZE / 2U, WHITE},
                                    {SIZE / 2U, SIZE / 2U - 1, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U - 1, WHITE}};

static PriorityTable const priorityTable = {{{0, 0}, {0, 7}, {7, 0}, {7, 7}},
                                            {{2, 2},
                                             {2, 3},
                                             {2, 4},
                                             {2, 5},
                                             {3, 2},
                                             {3, 3},
                                             {3, 4},
                                             {3, 5},
                                             {4, 2},
                                             {4, 3},
                                             {4, 4},
                                             {4, 5},
                                             {5, 2},
                                             {5, 3},
                                             {5, 4},
                                             {5, 5}},
                                            {{2, 0},
                                             {3, 0},
                                             {4, 0},
                                             {5, 0},
                                             {2, 7},
                                             {3, 7},
                                             {4, 7},
                                             {5, 7},
                                             {0, 2},
                                             {0, 3},
                                             {0, 4},
                                             {0, 5},
                                             {7, 2},
                                             {7, 3},
                                             {7, 4},
                                             {7, 5}},
                                            {{2, 1},
                                             {3, 1},
                                             {4, 1},
                                             {5, 1},
                                             {2, 6},
                                             {3, 6},
                                             {4, 6},
                                             {5, 6},
                                             {1, 2},
                                             {1, 3},
                                             {1, 4},
                                             {1, 5},
                                             {6, 2},
                                             {6, 3},
                                             {6, 4},
                                             {6, 5}},
                                            {{0, 1},
                                             {1, 0},
                                             {1, 1},
                                             {1, 6},
                                             {0, 6},
                                             {1, 7},
                                             {6, 1},
                                             {6, 0},
                                             {7, 1},
                                             {6, 6},
                                             {6, 7},
                                             {7, 6}}};

}  // namespace Config
#endif  // CONFIG_H
