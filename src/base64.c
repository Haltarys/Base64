#include "base64.h"

int base64(const args_t *args)
{
    if (args->mode == ENCODE)
        return encode(args->filename, args->rfc, args->wrap);
    else
        return decode(args->filename, args->rfc);
}
