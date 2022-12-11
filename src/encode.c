#include "encode.h"

static int counter = 0;

static int write_chars(char const *chars, int wrap)
{
    switch (wrap)
    {
    case 0:
        printf("%s", chars);
        return 0;
    case ENCODE_SIZE:
        printf("%s\n", chars);
        return 0;
    default:
        break;
    }

    int diff = wrap - counter;
    int len = strlen(chars);

    if (diff >= len)
    {
        printf("%s", chars);
        counter += len;
        return 1;
    }

    fwrite(chars, sizeof(char), diff, stdout);
    printf("\n");
    counter = 0;
    if (len - diff > 0)
        return write_chars(chars + diff, wrap);

    return 0;
}

static void encode_bytes(char *chars, uint8_t const *buffer, ssize_t bytes_read, char const *alphabet)
{
    uint8_t bytes[ENCODE_SIZE];

    bytes[0] = buffer[0] >> 2;
    bytes[1] = ((buffer[0] & 0b000011) << 4) | (buffer[1] >> 4);
    if (bytes_read >= 2)
        bytes[2] = ((buffer[1] & 0b001111) << 2) | (buffer[2] >> 6);
    else
        bytes[2] = PADDING;
    if (bytes_read == 3)
        bytes[3] = buffer[2] & 0b111111;
    else
        bytes[3] = PADDING;

    for (int i = 0; i < ENCODE_SIZE; i++)
        chars[i] = alphabet[bytes[i]];
}

int encode(char const *filename, int rfc, int wrap)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("Error while trying to open %s.\n", filename);
        printf("Check that the file exists and has correct access rights.\n");
        return EXIT_FAILURE;
    }

    uint8_t buffer[READ_SIZE] = {0};
    ssize_t bytes_read;
    char alphabet[] = ALPHABET;
    int newline = 0;

    if (rfc == RFC_4648)
        alphabet[62] = '-', alphabet[63] = '_';
    while ((bytes_read = fread(buffer, sizeof(char), READ_SIZE, file)) > 0)
    {
        char chars[ENCODE_SIZE + 1] = {0};

        encode_bytes(chars, buffer, bytes_read, alphabet);
        memset(buffer, 0, READ_SIZE);
        newline = write_chars(chars, wrap);
    }

    if (newline)
        printf("\n");
    fclose(file);
    return EXIT_SUCCESS;
}
