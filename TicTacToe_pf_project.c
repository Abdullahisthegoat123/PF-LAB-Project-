#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void display_instructions() {
	printf("\e[1;36m");
    printf("\n");
    printf("*                                                            *\n");
    printf("*             WELCOME TO THE TIC TAC TOE GAME!              *\n");
    printf("*                                                            *\n");
    printf("\n\e[m");

    printf("\e[1;33m");
    printf("+------------------------------------------------------------+\n");
    printf("¦                    \e[1;34mHOW TO PLAY\e[1;33m                           ¦\n");
    printf("¦                                                          ¦\n");
    printf("¦  1. The game is played on a 3x3 grid.                    ¦\n");
    printf("¦  2. Players take turns to place their marker:            ¦\n");
    printf("¦     - \e[1;31mPlayer 1: X\e[1;33m                                  ¦\n");
    printf("¦     - \e[1;34mPlayer 2: O\e[1;33m (or AI if playing in AI mode).    ¦\n");
    printf("¦  3. The first player to align three markers horizontally,¦\n");
    printf("¦     vertically, or diagonally wins the game.             ¦\n");
    printf("¦  4. If all squares are filled and no one wins, it's a    ¦\n");
    printf("¦     draw!                                                ¦\n");
    printf("¦                                                          ¦\n");
    printf("¦                 \e[1;34mGAME CONTROLS\e[1;33m                          ¦\n");
    printf("¦  - Enter the row and column numbers (1-3) to place your  ¦\n");
    printf("¦    marker.                                               ¦\n");
    printf("¦  - For example, to place a marker in the top left,       ¦\n");
    printf("¦    enter 1 for the row and 1 for the column.             ¦\n");
    printf("¦                                                          ¦\n");
    printf("¦                 \e[1;32mGAME MODES\e[1;33m                             ¦\n");
    printf("¦  1. Play against another player.                         ¦\n");
    printf("¦  2. Play against the AI.                                 ¦\n");
    printf("¦  3. Exit the game.                                       ¦\n");
    printf("¦                                                          ¦\n");
    printf("+------------------------------------------------------------+\n\e[m");

    printf("\e[1;36m");
    printf("\n");
    printf("*                      ENJOY THE GAME!                      *\n");
    printf("\n\e[m");
}
void show(int grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == -1) {
                printf("   ");
            } else if (grid[i][j] == 1) {
                printf(" \e[1;31mX\e[m ");
            } else {
                printf(" \e[1;34mO\e[m ");
            }
            if (j == 0 || j == 1) {
                printf("\e[1;33m|\e[m");
            }
        }
        printf("\n");
        if (i == 0 || i == 1) {
            printf("\e[1;33m---|---|---\n\e[m");
        }
    }
}

int check_winner(int grid[3][3], int currentPlayer) {
    for (int i = 0; i < 3; i++) {
        if ((grid[i][0] == currentPlayer && grid[i][1] == currentPlayer && grid[i][2] == currentPlayer) ||
            (grid[0][i] == currentPlayer && grid[1][i] == currentPlayer && grid[2][i] == currentPlayer)) {
            return 1;
        }
    }
    if ((grid[0][0] == currentPlayer && grid[1][1] == currentPlayer && grid[2][2] == currentPlayer) ||
        (grid[0][2] == currentPlayer && grid[1][1] == currentPlayer && grid[2][0] == currentPlayer)) {
        return 1;
    }
    return 0;
}

void ai_move(int grid[3][3]) {
    int moveX, moveY;
    while (1) {
        moveX = rand() % 3;
        moveY = rand() % 3;
        if (grid[moveX][moveY] == -1) {
            grid[moveX][moveY] = 2;
            break;
        }
    }
}

int main() {
    int player1 = 0, player2 = 0, gamesAi = 0, gamesP = 0, playerAi = 0;
    int play, ch1, mode;
    srand(time(NULL));

    while (1) {
        printf("\e[1;33m\tTIC TAC TOE \e[m \n");
        printf("The Choices are:\n1. Play with another player\n2. Play with AI\n3. View instructions\n4. Display stats\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch1);

        if (ch1 == 1 || ch1 == 2) {
            play = 1;
            mode = ch1;
            if (mode == 1) {
                gamesP++;
            } else if (mode == 2) {
                gamesAi++;
            }
        } else if (ch1 == 5) {
            printf("Thank you for playing!\n");
            return 0;
        } else if(ch1 == 4) {
        	printf("\nCurrent Stats:\n");
        	printf("Player 1 Wins: %d\n", player1);
        	printf("Player 2 Wins: %d\n", player2);
        	printf("Games Against AI: %d\n", gamesAi);
        	printf("Games Between Players: %d\n", gamesP);
        	printf("AI Wins: %d\n\n", playerAi);
        	continue;
		}
		else if(ch1==3) {
			display_instructions();
			continue;
		}else {
            printf("Wrong input! Please try again.\n");
            continue;
        }

        int grid[3][3], currentPlayer = 1, moveX, moveY, moves = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = -1;
            }
        }

        while (play) {
            show(grid);
            if (mode == 1 || (mode == 2 && currentPlayer == 1)) {
                printf("Enter Row (1-3) Player %d: ", currentPlayer);
                scanf("%d", &moveX);
                printf("Enter Column (1-3) Player %d: ", currentPlayer);
                scanf("%d", &moveY);

                moveX--;
                moveY--;

                if (moveX >= 0 && moveX <= 2 && moveY >= 0 && moveY <= 2 && grid[moveX][moveY] == -1) {
                    grid[moveX][moveY] = currentPlayer;
                    moves++;
                } else {
                    printf("Invalid move! Try again.\n");
                    continue;
                }
            } else if (mode == 2 && currentPlayer == 2) {
                printf("AI is making a move...\n");
                ai_move(grid);
                moves++;
            }

            if (check_winner(grid, currentPlayer)) {
                show(grid);
                if (mode == 1) {
                    printf("Player %d Won!\n", currentPlayer);
                    if (currentPlayer == 1) player1++;
                    else player2++;
                } else if (mode == 2) {
                    if (currentPlayer == 1) {
                        printf("You Won!\n");
                        player1++;
                    } else {
                        printf("AI Won!\n");
                        playerAi++;
                    }
                }
                play = 0;
            }

            if (!play) break;

            if (moves == 9) {
                show(grid);
                printf("It's a Draw!\n");
                play = 0;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
		FILE *ptr = fopen("data.txt","w");
		fprintf(ptr,"\nCurrent Stats:\n");
        fprintf(ptr,"Player 1 Wins: %d\n", player1);
        fprintf(ptr,"Player 2 Wins: %d\n", player2);
        fprintf(ptr,"Games Against AI: %d\n", gamesAi);
        fprintf(ptr,"Games Between Players: %d\n", gamesP);
        fprintf(ptr,"AI Wins: %d\n", playerAi);
        fclose(ptr);
    }
}
