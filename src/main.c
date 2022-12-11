#include "main.h"

static void display_help(char const *binname)
{
    printf("Usage: %s [OPTIONS] FILE\n\n", binname);
    printf("FILE: file to encode or decode in base 64\n");
    printf("OPTIONS:\n");
    printf("\t-d,\t--decode\tdecode the file (default is encoding mode)\n");
    printf("\t-r,\t--rfc4648\tuse RFC 4648 instead of RFC 2045\n");
    printf("\t\t\t\t(uses '+' and '/' instead of '-' and '_')\n");
    printf("\t-w COLS, --wrap=COLS\twrap encoded lines after COLS characters\n");
    printf("\t\t\t\t(default is 76). Use 0 to disable line wrapping.\n");
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

    if (parse_args(&args, argc, argv) < 0)
        return EXIT_FAILURE;
    return base64(&args);
}
