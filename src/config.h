#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include <QVector>
#include "logic/move.h"
#include "logic/position.h"

namespace Config {
// Board size. How many pieces in one row and one column.
static unsigned constexpr SIZE = 8U;

// How many pixels one piece has.
static unsigned constexpr PIECE_SIZE = 50u;

// Width and height of the board.
static unsigned constexpr WINDOW_WIDTH = (SIZE + 2) * PIECE_SIZE;
static unsigned constexpr WINDOW_HEIGHT = (SIZE + 2) * PIECE_SIZE;

// Time limit in searching.
static int constexpr timeLimit = 30000;

// After such a number of pieces in the board, we consider the game
// has gone into later staege.
static unsigned constexpr laterStage = 44u;

// How many types one board have.
enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

// Who is the first one to play.
static Type constexpr first = BLACK;

// A state of the game.
using State = QVector<QVector<Config::Type>>;

// A list of move calls movement.
using Movement = QList<Move>;

// PriorityTable is defined as a list of a position vector.
// In one vector means those positions have same priority.
using PriorityTable = QList<QVector<Position>>;

// The constant of calculating the value used by choosing the best child.
static double constexpr Cp = 1.0;

// Generate three times.
static unsigned constexpr simulationTime = 1u;

// Get the opposite player.
inline Type operator~(Type const &type) {
  return type == BLACK ? WHITE : type != EMPTY ? BLACK : EMPTY;
}

// Test if the type is not empty.
inline bool operator!(Type const &type) { return type != EMPTY; }

// Simply merge a state and movement regardless of the rule.
inline State operator+=(State &state, Movement const &movement) {
  for (auto const &move : movement) state[move.x()][move.y()] = move.type();
  return state;
}

// Simply apply a state and movement and return a new state regardless of the
// rule.
inline State operator+(State const &state, Movement const &movement) {
  State newState = state;
  newState += movement;
  return newState;
}

// The initial state defined by movement.
static Movement const initPieces = {{SIZE / 2U, SIZE / 2U, WHITE},
                                    {SIZE / 2U, SIZE / 2U - 1, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U - 1, WHITE}};

// The priority table we use.
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
