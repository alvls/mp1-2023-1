#include "additional.h"

bool isLatinSymbol(char t) {
    return ('a' <= t && t <= 'z') || ('A' <= t && t <= 'Z');
}
