#ifndef MAIN_H_
#define MAIN_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mode.h"
#include "rfc.h"

int base64(char const *filename, int mode, int rfc);

#endif /* !MAIN_H_ */
