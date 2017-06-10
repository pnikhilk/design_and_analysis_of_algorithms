#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int **board;
int tileCount;

/*
 * Initialize the Tromino board of size 2^n x 2^n with all zeros.
 * */
void initBoard(int size){
    int i, j;
    board = (int **)malloc(size * sizeof(int *)); 
    for(i = 0; i < size; i++){
        board[i] = (int *)malloc(size * sizeof(int));
        for(j = 0; j < size; j++){
            board[i][j] = 0;
        }
    }

    tileCount = 1;
}

/*
 * Free the allocated memory to Tromino board.
 * */
void freeBoard(int size){
    int i;

    for(i = 0; i < size; i++){
        free(board[i]);
    }
    free(board);
}

/*
 * Convert n x n board into Tromino board
 * */
void trominoTile(int startX, int startY, int x, int y, int size){
    int i, j, mid;
    int xUL, yUL, xUR, yUR, xLL, yLL, xLR, yLR, xMid, yMid;
    if(size == 2){
        //Base Case: 2x2 size board
        for(i = startX; i < startX + 2; i++){
            for(j = startY; j < startY + 2; j++){
                if((i == x) && (j == y)){
                    continue;
                }
                board[i][j] = tileCount;
            }
        }
    }
    else{
        mid  = size / 2;
        xMid = startX + mid;
        yMid = startY + mid;

        if(x < xMid){
            if(y < yMid){
                //Check if X is in Upper left board
                xUL = x;
                yUL = y;
                xUR = xMid - 1;
                yUR = yMid;
                xLL = xMid;
                yLL = yMid - 1;
                xLR = xMid;
                yLR = yMid;

                //Divide board into 4 parts, compute tromino recursively
                trominoTile(startX, startY, xUL, yUL, mid);
                trominoTile(startX, yMid, xUR, yUR, mid);
                trominoTile(xMid, startY, xLL, yLL, mid);
                trominoTile(xMid, yMid, xLR, yLR, mid);
    
                //Tromino to cover inserted holes
                board[xUR][yUR] = tileCount;
                board[xLL][yLL] = tileCount;
                board[xLR][yLR] = tileCount;
            }
            else{
                //Check if X is in Upper right board
                xUR = x;
                yUR = y;
                xUL = xMid - 1;
                yUL = yMid - 1;
                xLL = xMid;
                yLL = yMid - 1;
                xLR = xMid;
                yLR = yMid;

                //Divide board into 4 parts, compute tromino recursively
                trominoTile(startX, startY, xUL, yUL, mid);
                trominoTile(startX, yMid, xUR, yUR, mid);
                trominoTile(xMid, startY, xLL, yLL, mid);
                trominoTile(xMid, yMid, xLR, yLR, mid);

                //Tromino to cover inserted holes
                board[xUL][yUL] = tileCount;
                board[xLL][yLL] = tileCount;
                board[xLR][yLR] = tileCount;
            }
        }
        else{
            if(y < yMid){
                //Check if X is in Lower left board
                xLL = x;
                yLL = y;
                xUL = xMid - 1;
                yUL = yMid - 1;
                xUR = xMid - 1;
                yUR = yMid;
                xLR = xMid;
                yLR = yMid;

                //Divide board into 4 parts, compute tromino recursively
                trominoTile(startX, startY, xUL, yUL, mid);
                trominoTile(startX, yMid, xUR, yUR, mid);
                trominoTile(xMid, startY, xLL, yLL, mid);
                trominoTile(xMid, yMid, xLR, yLR, mid);
                
                //Tromino to cover inserted holes
                board[xUL][yUL] = tileCount;
                board[xUR][yUR] = tileCount;
                board[xLR][yLR] = tileCount;
            }
            else{
                //Check if X is in Lower right board
                xLR = x;
                yLR = y;
                xUL = xMid - 1;
                yUL = yMid - 1;
                xUR = xMid - 1;
                yUR = yMid;
                xLL = xMid;
                yLL = yMid - 1;

                //Divide board into 4 parts, compute tromino recursively
                trominoTile(startX, startY, xUL, yUL, mid);
                trominoTile(startX, yMid, xUR, yUR, mid);
                trominoTile(xMid, startY, xLL, yLL, mid);
                trominoTile(xMid, yMid, xLR, yLR, mid);
                
                //Tromino to cover inserted holes
                board[xUL][yUL] = tileCount;
                board[xUR][yUR] = tileCount;
                board[xLL][yLL] = tileCount;
            }
        }
    }
    tileCount++;
}

/*
 * Printing final Tromino board
 * */
void printBoard(int size){
    int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j ++){
            if(board[i][j] == 0){
                printf(" X  ");
            }
            else{
                printf("%2d  ", board[i][j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv){
    int n, x, y;

    if(argc != 4){
        printf("Enter 3 arguments.\n");
        return 1;
    }

    if(atoi(argv[1]) < 1){
        printf("Value of k should be greater than or equal to 1.\n");
        return 1;
    }
    n = pow(2,atoi(argv[1]));
    x = atoi(argv[2]);
    y = atoi(argv[3]);

    if((x >= n) || (y >= n)){
        printf("Values of x and y should be less than 2^k.\n");
        return 1;
    }
    
    initBoard(n);

    trominoTile(0, 0, x, y, n);
   
    printf("\n");
    printBoard(n);
    
    freeBoard(n);
}
