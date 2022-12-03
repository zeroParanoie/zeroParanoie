#include <stdio.h>
int checkRow(unsigned char (*problem)[9][9], int y, int num){
	//controllo sulla riga dell'inserzione nel sudoku
	int i;
	for(i=0;i<9;i++){
		if((*problem)[i][y]==num)
			return 1;
	}
	return 0;
}

int checkCol(unsigned char (*problem)[9][9], int x, int num){
	//controllo su colonna dell'inserzione nel sudoku
	int i;
	for(i=0;i<9;i++){
		if((*problem)[x][i]==num)
			return 1;
	}
	return 0;
}

int checkSq(unsigned char (*problem)[9][9], int x, int y, int num){
	int i;
	int j;
	
	//mappiamo la tabella in nove quadrati in base alle coordinate x/y: range -> [0,2];[3,5];[6,8]
	//se appartiene al range lo riportiamo alla cella in alto a sinistra, così da scorrere una sottomatrice 3x3
	
	if((x<=2)&&(x>=0))
	    x=0;
	if((x<=5)&&(x>=3))
	    x=3;
	if((x<=8)&&(x>=6))
	    x=6;
	
	if((y<=2)&&(y>=0))
	    y=0;
	if((y<=5)&&(y>=3))
	    y=3;
	if((y<=8)&&(y>=6))
	    y=6;
	
	for(i=x;i<x+3;i++){
		for(j=y;j<j+3;j++){
			if((*problem)[i][j]==num)
				return 1;
		}
	}
	return 0;
}

void solve(unsigned char (*problem)[9][9])
{
    int val=1;
    int x=0;
    int y=0;
    int temp_x;
    int temp_y;+
    //funzione ricorsiva, come andiamo avanti nella matrice?
    
    if(*problem[x][y] != 0){ //caso in cui abbiamo un numero inserito
        if(x<8){
            x++;
        } if((x==8)&&(y<8)){    //questi if annidati fungono anche da modulo per "incrementare"  la cella *
            y++;
            x=0;
        }
    }
    
    if(*problem[x][y] == 0){  //caso in cui bisogna inserire un numero
        while(val<10){
            if(!checkRow(problem, y, val) && !checkCol(problem, x, val) && !checkSq(problem, x, y, val)){
                *problem[x][y] = val;
                if(x<8){
                  x++;
                } if((x==8)&&(y<8)){    //questi if annidati fungono anche da modulo per "incrementare"  la cella *
                  y++;
                  x=0;
                }
                val++;    
            }
        }
    }
}
