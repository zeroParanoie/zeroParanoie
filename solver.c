#include <stdio.h>

struct temp_coords{       //in questa struttura i valori rappresentano le coordinate sul sudoku temporanee
    int tempx;
    int tempy;
};

int checkRow(unsigned char (*problem)[9][9], int y, int num){
	//controllo sulla riga dell'inserzione nel sudoku
	int i;
	for(i=0;i<9;i++){
		if((*problem)[i][y] == num)
			return 0;
	}
	return 1;
}

int checkCol(unsigned char (*problem)[9][9], int x, int num){
	//controllo su colonna dell'inserzione nel sudoku
	int i;
	for(i=0;i<9;i++){
		if((*problem)[x][i] == num)
			return 0;
	}
	return 1;
}

int checkSq(unsigned char (*problem)[9][9], int x, int y, int num){
	int i;
	int j;
	
	//mappiamo la tabella in nove quadrati in base alle coordinate x/y: range -> [0,2];[3,5];[6,8]
	//se appartiene al range lo riportiamo alla cella in alto a sinistra, così da scorrere una sottomatrice 3x3
	
	if((x <= 2) && (x >= 0))
	    x = 0;
	if((x <= 5) && (x >= 3))
	    x = 3;
	if((x <= 8) && (x >= 6))
	    x = 6;
	
	if((y <= 2) && (y >= 0))
	    y = 0;
	if((y <= 5) && (y >= 3))
	    y = 3;
	if((y <= 8) && (y >= 6))
	    y = 6;
	
	for(i=x;i<x+3;i++){
		for(j=y;j<j+3;j++){
			if((*problem)[i][j] == num)
				return 0;
		}
	}
	return 1;
}

int safe(int num, unsigned char (*problem)[9][9], int x, int y){   /*per rendere più compatto il codice chiamiamo una funzione sola che faccia tutto*/
    if(checkRow(problem, y, num) && checkCol(problem, x, num) && checkSq(problem, x, y, num))
        return 1;
    else
        return 0;
}

int true_solver(unsigned char (*problem)[9][9], int xc, int yc){
    struct temp_coords c;
    int val = 1;
    
    if(xc == 8 && yc == 8){ //ultima cella
        return 1;
    }
    
    if(*problem[xc][yc] > 0){    //caso in cui abbiamo un numero inserito
        if(xc < 8){
            xc++;
        } if((xc == 8) && (yc < 8)){    //questi if annidati fungono anche da modulo per "incrementare"  la cella *
            yc++;
            xc = 0;
        }
        if(true_solver(problem, xc, yc) == 1){
            return 1;
        } else {
            return 0;
        }
    }
    if(*problem[xc][yc] == 0){
        while(val < 10){
            if(safe(val, problem, xc, yc)){
                *problem[xc][yc] = val;
                 if(xc == 8 && yc == 8){  //ultima cella
                     return 1;
                 }
                 if(xc < 8){
                     c.tempx = xc + 1;
                 } if((xc == 8) && (yc < 8)){    //*
                     c.tempy = yc + 1;
                     c.tempx = 0;
                 }
                 if(true_solver(problem, c.tempx, c.tempy) == 1)
                    return 1;
            
            }
            val++;
        }
    }
    *problem[xc][yc] = 0;
    return 0;
}

void solve(unsigned char (*problem)[9][9])
{
    true_solver(problem, 0, 0);
}
