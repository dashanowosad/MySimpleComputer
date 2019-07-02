#include "../include/View.h"


int mt_clrscr(void){
printf("\E[H\E[2J");
return 0;
}

int mt_gotoXY(int X,int Y){
printf("\E[%d;%dH",X,Y);
mt_setfgcolor(8);
return 0;
}

int mt_getscreensize(int *rows,int *cols){
struct winsize ws;
	if (!ioctl(1,TIOCGWINSZ,&ws)){
		(*rows) = ws.ws_row;
		(*cols) = ws.ws_col;
		return 0;
	}
	else return -1;
}

int mt_setfgcolor(enum colors A){
	if (A >= 8) printf("\E[37m");
	else printf("\E[3%dm", A);
return 0;
}

int mt_setbgcolor(enum colors B){
	if (B >= 8) printf("\E[00m");
	else printf("\E[4%dm", B);
return 0;
}

void View(int flag){
	int tmp, i, j, z = 3, y = 2, c = 0;
	char s[6];
	int A[2] = {0x0, 0x0};
	mt_gotoXY(2, 2);
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			sc_memoryGet(c, &tmp);
			if(((tmp >> 15) & 0x1) == 0)
				sprintf(s, "+%04x", tmp);
			else{
				tmp = tmp & 0x7FFF;
				sprintf(s, "-%04x", tmp);
			}
			printf("%s ", s);
			c++;
		}
		mt_gotoXY(z, 2);
		z++;
	}
	bc_box(1, 1, 12, 61);
	mt_gotoXY(1, 29);
	printf("Memory");	
	bc_box(13, 1, 24, 46);
	for(i = 1; i < 11; i += 3)
		bc_box(i, 62, i+2, 82);
	mt_gotoXY(1, 67);
	printf("Accumulator");
	mt_gotoXY(2, 70);
	tmp = Accumulator;
        if(((tmp >> 15) & 0x1) == 0)
			sprintf(s, "+%04x", tmp);
		else {
			tmp = tmp & 0x7FFF;
			sprintf(s, "-%04x", tmp);
		}
	printf("%s ", s);
	mt_gotoXY(4, 64);
	printf("InstructionCounter");
	mt_gotoXY(5, 70);
	tmp = InstructionCounter;
	if(((tmp >> 15) & 0x1) == 0)
		sprintf(s, "+%04x", tmp);
    printf("%s ", s);
	mt_gotoXY(7, 68);
    printf("Operation");
	mt_gotoXY(8, 68);
	printCandO(); 
	mt_gotoXY(10, 70);
    printf("Flags");
	mt_gotoXY(11, 65 );
	//printf(" P  M  T  E  D ");			
	bc_box(13, 47, 24, 82);
	mt_gotoXY(13, 48);
    printf("Keys:");
	mt_gotoXY(14, 48);
	printf("l  - load");
	mt_gotoXY(15, 48);
	printf("s  - save");
	mt_gotoXY(16, 48);
	printf("r  - run");
	mt_gotoXY(17, 48);
	printf("t  - step");
	mt_gotoXY(18, 48);
	printf("i  - reset");
	mt_gotoXY(19, 48);
	printf("q  - exit");
	mt_gotoXY(20, 48);
	printf("v  - set the value");
	mt_gotoXY(21, 48);
	printf("p  - change regime");
	mt_gotoXY(22, 48);
	printf("F5 - accumulator");
	mt_gotoXY(23, 48);
	printf("F6 - instructionCounter");
	bc_box(25, 1, 27, 40);
	mt_gotoXY(26,2);
	if (flag == 1){
		mt_setbgcolor(3);
		mt_setfgcolor(1);
	}
	else {
		mt_setbgcolor(8);
		mt_setfgcolor(7);	
	}
	printf("  1. Arrows: UP, DOWN, LEFT, RIGHT    ");	
	if (flag == 1) {
		mt_setbgcolor(8);
		mt_setfgcolor(7);
	}
	bc_box(25, 42, 27, 82);
	mt_gotoXY(26,43);
	if (flag == 2){
		mt_setbgcolor(3);
		mt_setfgcolor(1);	
	}
	else {
		mt_setbgcolor(8);
		mt_setfgcolor(7);	
	}
	printf("  2. UP: W  DOWN: S  RIGHT: D  LEFT: A ");
	if (flag == 2) {
		mt_setbgcolor(8);
		mt_setfgcolor(7);
	}
	mt_gotoXY(25,38);
	printf("Regime");
	bc_box(28, 1, 30, 48);	
	mt_gotoXY(28, 19);
    	printf("Input/Output");	
	sc_memoryGet(InstructionCounter, &tmp);
	if(((tmp >> 15) & 0x1) == 0)
		sprintf(s, "+%04x", tmp);
    else {
		tmp &= 0x7FFF;
		sprintf(s, "-%04x", tmp);
	}
	for (i = 0; i < 5; i++) {
		bc_initbigchar(s[i], A);
		bc_printbigchar(A, 14, y, 8, 4);
		y += 9;
	}
	mt_gotoXY(25, 1);
}
