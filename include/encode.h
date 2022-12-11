#ifndef ENCODE_H_
#define ENCODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "rfc.h"

#define READ_SIZE 3
#define ENCODE_SIZE 4
#define PADDING 64
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

#endif /* !ENCODE_H_ */
