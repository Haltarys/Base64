#include "decode.h"

static int is_char_valid(char c)
{
    return isalnum(c) || c == '+' || c == '/' || c == '=';
}

static uint8_t decode_char(char c)
{
    if (isupper(c))
        return c - 'A';
    if (islower(c))
        return c - 'a' + 0b011010;
    if (isdigit(c))
        return c - '0' + 0b110100;
    if (c == '+')
        return 0b111110;
    if (c == '/')
        return 0b111111;
    return 0;
}

static void decode_chars(char const *buffer)
{
    uint8_t decoded[READ_SIZE];
    uint8_t bytes[DECODE_SIZE];
    size_t write_size = 3;

    for (int i = 0; i < READ_SIZE; i++)
        decoded[i] = decode_char(buffer[i]);

    bytes[0] = (decoded[0] << 2) | ((decoded[1] & 0b110000) >> 4);
    if (buffer[2] == PADDING)
        write_size = 1;
    else
    {
        bytes[1] = (decoded[1] << 4) | ((decoded[2] & 0b111100) >> 2);
        if (buffer[3] == PADDING)
            write_size = 2;
        else
            bytes[2] = (decoded[2] << 6) | decoded[3];
    }

    write(1, bytes, write_size * sizeof(uint8_t));
}

int decode(char const *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        printf("Error while trying to open %s.\n", filename);
        printf("Check that the file exists and has correct access rights..\n");
        return EXIT_FAILURE;
    }

    char buffer[READ_SIZE] = {0};
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, READ_SIZE)) > 0)
    {
        if (bytes_read != READ_SIZE)
        {
            printf("Error: invalid file size!\n");
            return EXIT_FAILURE;
        }
        for (int i = 0; i < READ_SIZE; i++)
        {
            if (!is_char_valid(buffer[i]))
            {
                printf("Error: unrecognized character %c\n", buffer[i]);
                return EXIT_FAILURE;
            }
        }
        decode_chars(buffer);
        memset(buffer, 0, READ_SIZE);
    }

    close(fd);
    return EXIT_SUCCESS;
}
