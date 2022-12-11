#ifndef BASE64_H_
#define BASE64_H_

#include "mode.h"
#include "args.h"

int encode(char const *filename, int rfc, int wrap);
int decode(char const *filename, int rfc);

#endif /* !BASE64_H_ */
