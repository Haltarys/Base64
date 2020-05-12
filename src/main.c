#include "main.h"

static void display_help(char const *binname)
{
    printf("Usage: %s FILE [OPTION]\n\n", binname);
    printf("FILE: file to encode or decode in base 64\n");
    printf("OPTION: encode or decode the file (default is encode)\n");
    printf("Add the -d or --decode flag to decode the file.\n");
}

static int get_mode(char const *arg)
{
    if (!arg)
        return ENCODE;
    if (!strcmp("-d", arg) || !strcmp("--decode", arg))
        return DECODE;
    printf("Unrecognized option: %s. Ignored (encoding mode).\n", arg);
    return ENCODE;
}

int main(int argc, char const *argv[])
{
    if (argc == 1 || argc > 3)
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
    return base64(argv[1], get_mode(argv[2]), RFC_2045);
}
