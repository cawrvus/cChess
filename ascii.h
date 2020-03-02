#ifndef ASCII_H
#define ASCII_H

#include "types.h"

#define ASCII_HEIGHT 4
#define DIV_ASCII "+-------+-------+-------+-------+-------+-------+-------+-------+\n"
#define PADDING_ASCII " "
#define EMPTY_ASCII "     "

const char **get_ascii(Type t, Color c);

#endif /* ASCII_H */
