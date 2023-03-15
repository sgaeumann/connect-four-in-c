#include <stdio.h>
#include "functions.h"
#include <time.h>


int main() {
    char game_board[7][6];
    int choice;
    Coordinates input_user;
    User info;
    clock_t start, end;
    play:
    drain_grid(game_board);
    printf("\n");
    printf("\t\t************************************ Bienvenue au Puissance 4 ************************************\n\n");
    display_winners();
    displayGrid(game_board, ' ');
    start = clock(); //Timer starts
    while (1) {
        input_user = input_joueur(game_board, 'X');
        displayGrid(game_board, 'X');
        hasWon(game_board, input_user, 'X');
        if (hasWon(game_board, input_user, 'X') == 1) {
            end = clock() - start; //Timer ends
            float timer = ((float) end) / CLOCKS_PER_SEC;
            printf("Player 1 won!\n");
            break;
        }
        input_user = input_joueur(game_board, 'O');
        displayGrid(game_board, 'O');
        hasWon(game_board, input_user, 'O');
        if (hasWon(game_board, input_user, 'O') == 1) {
            end = clock() - start; //Timer ends
            printf("Player 2 won!\n");
            break;
        }
        if (tab_full(game_board) == 1) {
            end = clock() - start; //Timer ends
            printf("Tie match.\n");
            break;
        }
    }
    if ((hasWon(game_board, input_user, 'X') == 1) || hasWon(game_board, input_user, 'O') == 1) {
        float timer = ((float) end) / CLOCKS_PER_SEC;
        float *p_timer = &timer;
        printf("Congratulation!\n");
        printf("The game lasted %.3f seconds.\n", timer);
        register_winner(info, p_timer);
    } else if (hasWon(game_board, input_user, 'X') == 2 || hasWon(game_board, input_user, 'O') == 2) {
        printf("\nNo one won :(\n");
        end = clock() - start; //Timer ends
        float timer = ((float) end) / CLOCKS_PER_SEC;
        printf("The game lasted %.3f seconds.\n", timer);
    } else {
        printf("\nError.\n");
    }
    printf("Would you like to play again? [1] Yes [2] No\nYour choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            goto play;
        case 2:
            printf("\nGoodbye! :)\n");
            return 0;
        default:
            printf("The entered number is incorrect.\n");
    }

    return 0;
}