#ifndef CONFIG_H
#define CONFIG_H

#include <QVector>
#include <logic/movement.h>
#include <tuple>

namespace Config {
static unsigned constexpr SIZE = 8U;

enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

static Type constexpr first = BLACK;

using InitPiece = std::tuple<size_t, size_t, Type>;

using Composition = QVector<QVector<Config::Type>>;

inline Type operator~(Type const &type) {
  return type == BLACK ? WHITE : type != EMPTY ? BLACK : EMPTY;
}

inline bool operator!(Type const &type) { return type != EMPTY; }

static Movement const initPieces = {{SIZE / 2U, SIZE / 2U, WHITE},
                                    {SIZE / 2U, SIZE / 2U - 1, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U, BLACK},
                                    {SIZE / 2U - 1, SIZE / 2U - 1, WHITE}};
} // namespace Config
#endif // CONFIG_H
