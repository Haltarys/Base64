#include "encode.h"

static void encode_bytes(uint8_t const *buffer, ssize_t bytes_read, char const *alphabet)
{
    uint8_t bytes[ENCODE_SIZE];
    char chars[ENCODE_SIZE] = {0};

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

    fwrite(chars, sizeof(char), ENCODE_SIZE, stdout);
}

int encode(char const *filename, int rfc)
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
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    if (rfc == RFC_4648)
        alphabet[62] = '-', alphabet[63] = '_';
    while ((bytes_read = fread(buffer, sizeof(char), READ_SIZE, file)) > 0)
    {
        encode_bytes(buffer, bytes_read, alphabet);
        memset(buffer, 0, READ_SIZE);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
