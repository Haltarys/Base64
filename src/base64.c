#include "base64.h"

int base64(char const *filename, int mode)
{
    printf("filename: '%s', mode = %s\n", filename, mode == 0 ? "ENCODE" : "DECODE");
    if (mode == ENCODE)
        return encode(filename);
    else
        return decode(filename);
}
