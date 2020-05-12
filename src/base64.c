#include "base64.h"

int base64(char const *filename, int mode, int rfc)
{
    if (mode == ENCODE)
        return encode(filename, rfc);
    else
        return decode(filename, rfc);
}
