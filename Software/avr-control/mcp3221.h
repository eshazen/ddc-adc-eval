#ifndef _MCP3221_H_INCLUDED
#define _MCP3221_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "i2c.h"

void init_3221();
uint16_t read_3221();


#endif

