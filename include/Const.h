#ifndef _CONST_
#define _CONST_

/*flags*/
#define M 0	//Выход за границы
#define E 1	//Неправильная команда
#define T 2	//Игнорирование импульсов
#define P 3	//Переполнение при операции
#define DEL 4	//Деление на 0

/*colors*/
enum colors {Dark, Red, Green,Yellow, Dark_Blue, Purple,Blue, White, Standart};

/*paint*/
#define inv "\E[?25l"
#define vis "\E[?12;25h"

#define S_tab "\E(0"
#define F_tab "\E(B"

#define ACS_CKBOARD "a"
#define line "q"
#define vline "x"
#define ula "l"
#define ura "k"
#define dla "m"
#define dra "j"

/*commands*/
enum {
		/*I/O*/
	READ   = 0x10,
	WRITE  = 0x11,
		/*Loading/overloading in accum*/
	LOAD   = 0x20,
	STORE  = 0x21,
		/*Arithmethic operations*/
	ADD    = 0x30,
	SUB    = 0x31,
	DIVIDE = 0x32,
	MUL    = 0x33,
		/*R*/
	JUMP   = 0x40,
	JNEG   = 0x41,
	JZ     = 0x42,
	HALT   = 0x43,
		/*User operations*/
	RCL    = 0x62,
	
};
/*const*/
#define swap "Files/swap.bin"
int mass[100];
int Accumulator;
int InstructionCounter;
int F_reg;
#endif
