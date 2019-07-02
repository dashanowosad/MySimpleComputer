#ifndef _MyReadKey_
#define _MyReadKey_

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "View.h"
struct termios savetty;
struct termios tty;


enum keys {l, s, r, t, v , i, p, F5, F6, UP, DOWN, LEFT, RIGHT, ENTER, NONE, q};


int rk_readkey(enum keys *, int flag);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
#endif
