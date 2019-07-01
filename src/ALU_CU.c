#include <signal.h>
#include <sys/time.h>
#include "../include/ALU_CU.h"


void CheckFlags(void){
	int Flag, value,j;
	
	for(j = 0; j < 5; j++){
	 	
		Flag = j;
		sc_regGet(Flag,&value);
		if ((Flag == 0) && (value == 1)){
			mt_gotoXY(11,69);	
			mt_setbgcolor(3);
			mt_setfgcolor(1);		
			printf(" M ");
		}
		else if ((Flag == 0) && (value == 0)){
			mt_gotoXY(11,69);	
			mt_setbgcolor(0);
			mt_setfgcolor(8);		
			printf(" M ");
		}
		if ((Flag == 1) && (value == 1)){
			mt_gotoXY(11,75);	
			mt_setbgcolor(3);
			mt_setfgcolor(1);		
			printf(" E ");
		}
		else if ((Flag == 1) && (value == 0)){
			mt_gotoXY(11,75);	
			mt_setbgcolor(0);
			mt_setfgcolor(8);		
			printf(" E ");
		}
		if ((Flag == 2) && (value == 1)){
			mt_gotoXY(11,72);	
			mt_setbgcolor(3);
			mt_setfgcolor(1);		
			printf(" T ");
		}
		else if ((Flag == 2) && (value == 0)){
			mt_gotoXY(11,72);	
			mt_setbgcolor(0);
			mt_setfgcolor(8);		
			printf(" T ");
		}
		if ((Flag == 3) && (value == 1)){
			mt_gotoXY(11,66);	
			mt_setbgcolor(3);
			mt_setfgcolor(1);		
			printf(" P ");
		}
		else if ((Flag == 3) && (value == 0)){
			mt_gotoXY(11,66);	
			mt_setbgcolor(0);
			mt_setfgcolor(8);		
			printf(" P ");
		}
		if ((Flag == 4) && (value == 1)){
			mt_gotoXY(11,78);	
			mt_setbgcolor(3);
			mt_setfgcolor(1);		
			printf(" D ");
		}
		else if ((Flag == 4) && (value == 0)){
			mt_gotoXY(11,78);	
			mt_setbgcolor(0);
			mt_setfgcolor(8);		
			printf(" D ");
		}
	}
	mt_setbgcolor(0);
	mt_setfgcolor(8);

}

int ALU(int command, int operand) {
	int value;
	if (sc_memoryGet(operand, &value) == -1) {
		sc_regSet(M, 1);
		CheckFlags();
		return -1;
	}
	value &= 0x7FFF;
	switch(command) {
		case ADD: {
			Accumulator += value;
			if (Accumulator > 32767 || Accumulator < -32767) {
				sc_regSet(P, 1);
				sc_regSet(T, 0);
				CheckFlags();
				return -1;
			}
			InstructionCounter++;
			break;
		}
		case SUB: {
			Accumulator -= value;
			if (Accumulator > 32767 || Accumulator < -32767) {
				sc_regSet(P, 1);
				sc_regSet(T, 0);
				CheckFlags();
				return -1;
			}
			InstructionCounter++;
			break;
		}
		case MUL: {
			Accumulator *= value;
			if (Accumulator > 32767 || Accumulator < -32767) {
				sc_regSet(P, 1);
				sc_regSet(T, 0);
				CheckFlags();
				return -1;
			}
			InstructionCounter++;
			break;
		}
		case DIVIDE: {
			if (value == 0)	{
				sc_regSet(DEL, 1);
				sc_regSet(T, 0);
				CheckFlags();
				return -1;
			}
			Accumulator /= value;
			InstructionCounter++;
			break;
		}
		default: {
			return -1;
		}
	}
	return 0;
}


int CU() {
	int operand, command, value, tmp;
	sc_memoryGet(InstructionCounter, &value);
	sc_regSet(T, 1);
	sc_regSet(E, 0);
	if (sc_commandDecode(value, &command, &operand) == -1) {
		sc_regSet(E, 1);
		sc_regSet(T, 0);
		CheckFlags();
		return -1;
	}
	if (command >= 0x30 && command <= 0x33) {
		if(ALU(command, operand) == 0)
			return 0;
		else
			return -1;
	}else{
		switch(command) {
			case READ: {
				alarm(0);
				rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter cell  value: ");
				scanf("%d", &tmp);
				mt_gotoXY(25, 2);
				printf("                                                ");
				sc_memorySet(operand, tmp);
				rk_mytermregime(0, 1, 1, 0, 0);
				InstructionCounter++;
				alarm(1);
				break;
			}
			case WRITE: {
				alarm(0);
				rk_mytermrestore();
				sc_memoryGet(operand, &tmp);
				mt_gotoXY(25, 2);
				printf("                                                ");
				mt_gotoXY(25, 2);
				printf("Value = %d", tmp);
				rk_mytermregime(0, 1, 1, 0, 0);
				InstructionCounter++;
				alarm(1);
				break;
			}
			case LOAD: {
				sc_memoryGet(operand, &value);
				value &= 0x7FFF;
				Accumulator=value;
				InstructionCounter++;
				break;
			}
			case STORE: {
				sc_memorySet(operand, Accumulator);
				InstructionCounter++;
				break;
			}
			case JUMP: {
				InstructionCounter = operand;
				break;
			}	
			case JNEG: {
				if(Accumulator < 0)
					InstructionCounter = operand;
				else
					InstructionCounter++;
				break;
			}
			case JZ: {
				if (Accumulator == 0)
					InstructionCounter = operand;
				else
					InstructionCounter++;
				break;
			}
			
			case RCL: {
				if (Accumulator>>31==0)
					Accumulator = ((Accumulator << operand) | (Accumulator >> (31 - operand)) & (~(1 << 31)));
				else
    				Accumulator = ((Accumulator << operand) | (Accumulator >> (31 - operand)) | (1 << 31));
					InstructionCounter++;
				break;
			}
			case HALT: {
				sc_regSet(T, 0);
				alarm(0);
				key = NONE;
				break;
			}
			default: {
				return -1;
				break;			
			}
		}	
	
	}
	return 0;
}

