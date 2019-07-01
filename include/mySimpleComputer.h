#ifndef _MY_SIMPLE_COMP
#define _MY_SIMPLE_COMP_

#include "Const.h"

/*memory*/
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
/*register*/
int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
/*command*/
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

#endif
