#include "parse.h"

static int str_isnum(char const *str)
{
    if (!str || *str == 0)
        return 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int parse_args(args_t *args, int argc, char const *argv[])
{
    if (!args)
        return -1;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("-d", argv[i]) || !strcmp("--decode", argv[i]))
            args->mode = DECODE;
        else if (!strcmp("-r", argv[i]) || !strcmp("--rfc4648", argv[i]))
            args->rfc = RFC_4648;
        else if (!strcmp("-w", argv[i]))
        {
            if (str_isnum(argv[i + 1]))
            {
                args->wrap = atoi(argv[i + 1]);
                i++;
            }
            else
            {
                if (argv[i + 1])
                    printf("Invalid wrap value: %s\n", argv[i + 1]);
                else
                    printf("Missing wrap value!\n");
                return -1;
            }
        }
        else if (!strncmp("--wrap=", argv[i], 7))
        {
            if (str_isnum(argv[i] + 7))
            {
                args->wrap = atoi(argv[i] + 7);
            }
            else
            {
                if (argv[i][7] == 0)
                    printf("Missing wrap value!\n");
                else
                    printf("Invalid wrap value: %s\n", argv[i + 1] + 7);
                return -1;
            }
        }
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
