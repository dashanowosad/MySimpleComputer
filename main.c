#include "include/mySimpleComputer.h"
#include "include/View.h"
#include "include/BigChar.h"
#include "include/MyReadKey.h"
#include "include/ALU_CU.h"

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void timer(){
	if(CU() == -1){
		alarm(0);
		key = NONE;
	}
}
void reset(void){
	sc_memoryInit();
	Accumulator = 0;
	InstructionCounter = 0;
}




void printCandO(){
	int tmp, operand, command;
	char com[2], op[2];
	sc_memoryGet(InstructionCounter, &tmp);
	printf("              ");
	mt_gotoXY(8, 68);
	if(sc_commandDecode(tmp, &command, &operand) == 0){
		sprintf(com, "%01x", command);
		printf(" %s :",com);
		sprintf(op, "%0x", operand);
		printf(" %s", op);
		
	}else
		printf("+ 00 : 00");
		
}




int console(void) {
	char filename[80];
	char z[6];
	int flag = 1;
	int tmp;
	signal(SIGALRM, timer);
	signal(SIGUSR1, reset);
    rk_mytermsave();
	while(flag) {
		View();
		CheckFlags();
        rk_mytermregime(0, 1, 1, 0, 0);
		printf(inv);
		fflush(stdout);
		mt_setbgcolor(3);
		fflush(stdout);
		mt_gotoXY((InstructionCounter / 10) + 2, (InstructionCounter % 10) * 6 + 2);
		fflush(stdout);
		sc_memoryGet(InstructionCounter, &tmp);
		if(((tmp >> 15) & 0x1) == 0) {
			sprintf(z, "+%04x", tmp);
			fflush(stdout);
		} else {
			tmp &= 0x7FFF;
            sprintf(z, "-%04x", tmp);
			fflush(stdout);
		}
		printf("%s", z);
		fflush(stdout);
		mt_setbgcolor(8);
        fflush(stdout);
    	if (key != r) rk_readkey(&key);
		switch(key) {
			case F5: {
				rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter Accumulator value: ");
				scanf("%d", &Accumulator);
				mt_gotoXY(25, 2);
				printf("                                            ");
				rk_mytermregime(0, 1, 1, 0, 0);
				break;
			}
			case F6: {
            	rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter RC value: ");
				scanf("%d", &InstructionCounter);
				mt_gotoXY(25, 2);
				printf("                                            ");
                rk_mytermregime(0, 1, 1, 0, 0);
                break;
			}
			case q: {
				flag = 0;
				rk_mytermrestore();
				mt_gotoXY(27, 1);
				break;	
			}
			case l: {
				rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter filename: ");
				scanf("%s", filename);
				mt_gotoXY(25, 2);
				printf("                                           ");
				sc_memoryLoad(filename);
				rk_mytermregime(0, 1, 1, 0 ,0);
				break;
			}

			case s: {
				rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter filename: ");
				scanf("%s", filename);
				mt_gotoXY(25, 2);
				printf("                                           ");
				sc_memorySave(filename);
				rk_mytermregime(0, 1, 1, 0 ,0);
				break;
			}
			case i: {
				raise(SIGUSR1);
				break;
			}
			case w: {
				rk_mytermrestore();
				mt_gotoXY(25, 2);
				printf("Enter cell  value: ");
				scanf("%d", &tmp);
				mt_gotoXY(25, 2);
				printf("                                           ");
				sc_memorySet(InstructionCounter, tmp);
				rk_mytermregime(0, 1, 1, 0, 0);
				break;
			}
			case r: {
				F_reg = 0;
				alarm(1);
				break;		
			}
			case t: {
				CU();
				sc_regSet(T, 0);
				rk_mytermrestore();
				CheckFlags();
				rk_mytermregime(0, 1, 1, 0, 0);
				break;
			}
			case DOWN: {
				if(InstructionCounter + 10 < 100)
					InstructionCounter += 10;
				break;
			}
			case UP: {
				if(InstructionCounter - 10 >= 0)
					InstructionCounter -= 10;
				break;
			}
			case LEFT: {
				if(InstructionCounter - 1 >= 0)
					InstructionCounter--;
				break;
			}
			case RIGHT: {
				if(InstructionCounter + 1 < 100)
					InstructionCounter++;
				break;
			}
			case NONE: {
				break;		
			}
			default: {
				break;
	        }
		}
		if (key == r)
			pause();
		rk_mytermrestore();
	}
	return 0;
}

int main() {
	mt_clrscr();
	console();
	return 0;
}

