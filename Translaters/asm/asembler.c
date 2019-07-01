#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int CheckComand(char *S){
	if(strcmp(S,"READ") == 0) return 0x10;
	else if(strcmp(S,"WRITE") == 0) return 0x11;
	else if(strcmp(S,"LOAD") == 0) return 0x20;
	else if(strcmp(S,"STORE") == 0) return 0x21;
	else if(strcmp(S,"ADD") == 0) return 0x30;
	else if(strcmp(S,"SUB") == 0) return 0x31;
	else if(strcmp(S,"DIVIDE") == 0) return 0x32;
	else if(strcmp(S,"MUL") == 0) return 0x33;
	else if(strcmp(S,"JUMP") == 0) return 0x40;
	else if(strcmp(S,"JNEG") == 0) return 0x41;
	else if(strcmp(S,"JZ") == 0) return 0x42;
	else if(strcmp(S,"HALT") == 0) return 0x43;
	else if(strcmp(S,"JNP") == 0) return 0x59;
	else return -1;
}

int from16to10(char *S){
	int i, k, p, m = 0;
	p = 3;
	for(i = 0; S[i] != '\0'; i++){	
		if (S[i] =='0')
			k = 0;
		else if (S[i] =='1')
			k = 1;
		
		else if (S[i] =='2')
			k = 2;

		else if (S[i] =='3')
			k = 3;		
					
		else if (S[i] =='4')
			k = 4;
		
		else if (S[i] =='5')
			k = 5;
		
		else if (S[i] =='6')
			k = 6;
		
		else if (S[i] =='7')
			k = 7;
		
		else if (S[i] =='8')
			k = 8;
		
		else if (S[i] =='9')
			k = 9;
		
		else if (S[i] =='a')
			k = 10;
		
		else if (S[i] =='b')
			k = 11;
		
		else if (S[i] =='c')
			k = 12;
		
		else if (S[i] =='d')
			k = 13;
		
		else if (S[i] =='e')
			k = 14;
		
		else if (S[i] =='f')
			k = 15;
		
		m = m + k * pow(16,p);
		p--;
		
	}
	return m;
	
}

int main(){
	FILE *f1, *f2;
	f1 = fopen("factorial.txt","r");
	f2 = fopen("factorial.bin", "wb");
	int A[100], adr,com, op, i, res;
	char adress[3], command[10], operand[3], result[10];
	char  c[2],o[2], co[4]; // в 16-ричном c - строка командыб о - строка операнда, со - склеянные
	char space; //для пробела 

	for(i = 0; i < 100; i++)
		A[i] = 0;	
	if (f1) {
		while(!feof(f1)){
			fscanf(f1,"%s",&adress);
			adr = atof(adress); //получили адрес ячейки
		
			fscanf(f1, "%c",&space);

			fscanf(f1,"%s",&command);
			if (CheckComand(command) != -1){ //если у нас команда
				com = CheckComand(command); //получили команду в 10-й системе счисления
				
				fscanf(f1, "%c",&space);
		
				fscanf(f1,"%s", &operand);
				op = atof(operand);//получили операнд (адрес новой ячейки)
				
				fscanf(f1, "%c",&space);
				/////////////перевели в 16-ричную и склеили строку
				sprintf(c, "%01x", com); 
				strcpy(co,c);
				if (op > 9) sprintf(o, "%01x", op);
				else sprintf(o, "0%01x", op);
				strcat(co,o);		
				//////////
				res = from16to10(co);
				
				
				A[adr] = res; 
				printf("%d  %d\n",adr,res);
			}
			else {
				if(strcmp(command, "=") == 0){
					fscanf(f1, "%c",&space);
					fscanf(f1, "%s",&command);
					com = atof(command);
					A[adr] = com;
					printf("%d  %d  \n",adr,com);
				}
					
				
			}
			
			
		}
		fclose(f1);
	}
	else 
		return -1;
	if(f2){
		fwrite(A, sizeof(int), 100, f2);
		fclose(f2);
	}
	else
		return -1;
	return 0;
}
