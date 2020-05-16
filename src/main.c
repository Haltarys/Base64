#include "main.h"

static void display_help(char const *binname)
{
    printf("Usage: %s [OPTIONS] FILE\n\n", binname);
    printf("FILE: file to encode or decode in base 64\nOPTION:\n");
    printf("    -d, --decode    decode the file (default is encode mode)\n");
    printf("    -r, --rfc4648   use RFC 4648 instead of RFC 2045\n");
    printf("                    '+' and '/' respectively become '-' and '_'\n");
}

static int parse_args(int argc, char const *argv[], args_t *args)
{
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("-d", argv[i]) || !strcmp("--decode", argv[i]))
            args->mode = DECODE;
        else if (!strcmp("-r", argv[i]) || !strcmp("--rfc4648", argv[i]))
            args->rfc = RFC_4648;
        else
        {
            if (args->filename != NULL)
            {
                printf("Invalid argument: %s\n", argv[i]);
                return -1;
            }
            args->filename = argv[i];
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        display_help(argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("-h", argv[i]) ||
            !strcmp("--help", argv[i]))
        {
            display_help(argv[0]);
            return EXIT_SUCCESS;
        }
    }

    args_t args = {NULL, ENCODE, RFC_2045, 76};

    if (parse_args(argc, argv, &args) < 0)
        return EXIT_FAILURE;
    return base64(&args);
}
