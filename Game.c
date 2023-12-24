#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINES 15

void printBoard(char board[][SIZE], int showMines);
void placeMines(char board[][SIZE]);
int countAdjacentMines(char board[][SIZE], int row, int col);

int main() {
    char board[SIZE][SIZE];
    int row, col;
    int i,j;
    int minesLeft = MINES;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = '#';
        }
    }

    placeMines(board);

    while (minesLeft > 0) {
        printBoard(board, 0);
        printf("Enter row and column (e.g., 1 2): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (board[row][col] == 'X') {
            printf("Game Over! You hit a mine.\n");
            printBoard(board, 1); 
            break;
        }

        int adjacentMines = countAdjacentMines(board, row, col);
        board[row][col] = (char)(adjacentMines + '0');

        if (adjacentMines == 0) {
            for (i = row - 1; i <= row + 1; i++) {
                for (j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == '#') {
                        int adj = countAdjacentMines(board, i, j);
                        board[i][j] = (adj == 0) ? ' ' : (char)(adj + '0');
                    }
                }
            }
        }

        minesLeft--;

        if (minesLeft == 0) {
            printf("Congratulations! You won!\n");
            printBoard(board, 1);
            break;
        }
    }

    return 0;
}

void printBoard(char board[][SIZE], int showMines) {
    printf("\n  ");
    int i,j;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X' && !showMines) {
                printf("# ");
            } else {
                printf("%c ", board[i][j]);
            }
        }
        printf("\n");
    }
}

void placeMines(char board[][SIZE]) {
	int i;
    for (i = 0; i < MINES; i++) {
        int row, col;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (board[row][col] == 'X');
        board[row][col] = 'X';
    }
}

int countAdjacentMines(char board[][SIZE], int row, int col) {
    int count = 0;
    int i,j;
    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == 'X') {
                count++;
            }
        }
    }
    return count;
}


