#include "base64.h"

int base64(char const *filename, int mode)
{
    if (mode == ENCODE)
        return encode(filename);
    else
        return decode(filename);
}
