#ifndef MAIN_H_
#define MAIN_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mode.h"
#include "rfc.h"
#include "args.h"

int parse_args(args_t *args, int argc, char const *argv[]);
int base64(const args_t *args);

#endif /* !MAIN_H_ */
