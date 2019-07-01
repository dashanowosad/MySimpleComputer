#include <stdio.h>
#include "../include/mySimpleComputer.h"
#include "../include/Const.h"

/*memory*/
int sc_memoryInit() {
	int i;
    for(i = 0; i < 100; i++)
		mass[i] = 0;
    return 0;
}

int sc_memorySet(int adress, int value) {
    if((adress < 0 ) || (adress > 100)) {
		sc_regSet(M, 1);
		return -1; 
    }
    else {
		mass[adress] = value;
		return 0;
    }
}

int sc_memoryGet(int adress, int *value) {
    if ((adress < 0 ) || (adress > 100)) {
		sc_regSet(M, 1);
		return -1; 
    }
    else {
		*value = mass[adress];
		return 0;
    }
}

int sc_memorySave(char *filename) {
    char f[100] = "..//Files//";
    char f1[100] = ".bin";
    strcat(f,filename);
    strcat(f,f1);
    FILE *file = fopen(f, "wb");
	if (file) {
		fwrite(mass, sizeof(int), 100, file);
		fclose(file);
		return 0;
	}else
		return -1;
}

int sc_memoryLoad(char *filename) {
	char f[100] = "..//Files//";
    	char f1[100] = ".bin";
    	strcat(f,filename);
    	strcat(f,f1);
	FILE *file = fopen(f, "rb");
	if (file) {
		fread(mass, sizeof(int), 100, file);
		fclose(file);
		return 0;
	}else
		return -1;
}

/*register*/

int sc_regInit(void) {
	F_reg = F_reg & 0;
	Accumulator = 0;
	InstructionCounter = 0;
	return 0;
}

int sc_regSet(int reg, int value) {
	if((reg > 0) || (reg < 31)) {
		if(value == 0) {
			F_reg = F_reg & (~(1 << reg));
			return 0;
		}else if (value == 1) {
			F_reg = F_reg | (1 << reg);
			return 0;
		} else 
			return 1; 
	}else 
		return -1;
}

int sc_regGet(int reg, int *value) {
	if ((reg > 0) || (reg < 31)) {
		*value = (F_reg >> reg) & 0x1;
		return 0;
	}else
		return -1;
}
/*command*/

int checkCommand(int command) {
	if( 
		command == READ   ||	command == WRITE  || command == LOAD   ||	command == STORE  ||
		command == ADD    ||	command == SUB    || command == DIVIDE ||	command == MUL    ||
		command == JUMP   ||	command == JNEG   || command == JZ     ||	command == HALT   ||
		command == RCL    
	)
		return 0;
	else {
		sc_regSet(E, 1);
		return -1;
        }
}

int sc_commandEncode(int command, int operand, int *value){
	if(operand < 128) {
		if (!checkCommand(command)) {
		*(value) = *(value) & 0x0;
		*(value) = *(value) | command;
		*(value) = *(value) << 8;
		*(value) = *(value) | operand;
		return 0;
		}
	else
		return -1;
	}
	return -1;
}

int sc_commandDecode(int value, int *command, int *operand) {
	if(value >> 15 == 0) {
		*(operand) = value & 0x7F;
		*(command) = (value >> 8) & 0x7F;
		if (!checkCommand(*command)) {
			return 0;			
		}	
		return -1;
	}
	return -1;
}
