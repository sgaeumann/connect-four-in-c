#include <stdio.h>
#include "functions.h"
#include <time.h>

/**
 * To print the game grid
 * @param plateau : grid
 */
void displayGrid(char plateau[7][6], char token) {
    printf("\n");
    printf("   A B C D E F G \n");
    // each line
    for (int i = 0; i < 6; ++i) {
        printf("  +-+-+-+-+-+-+-+\n");
        printf("%d ", i + 1);
        //each column
        for (int j = 0; j < 7; ++j) {
            printf("|");
            printf("%c", plateau[j][i]);
        }
        printf("|");
        printf("\n");
    }
    printf("  +-+-+-+-+-+-+-+\n");
    printf("\n");
    if (token == 'X') {
        printf("Player 2:\n");//if the last placed token was X (which corresponds to Joueur 1), then print Joueur 2
    } else {
        printf("Player 1:\n");//so that the first input is player 1 (token=NULL)
    }
}

/**
 * function to check if te grid is full
 * @param plateau
 * @return
 */
int tab_full(char plateau[7][6]) {
    int tab_max = 42;
    int counter = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++)
            if (plateau[i][j] != ' ') {
                counter++;
            }
    }
    if (counter == tab_max) {
        printf("The game board is full.\n");
        return 1;
    } else {
        return 0;
    }
}


/**
 *
 * @param plateau : grid
 * @param token : X or O, depends which player is playing
 * @return
 */
Coordinates input_joueur(char plateau[7][6], char token) {
    Coordinates user;
    char tmp;
    print:
    printf("Enter a coordinate, e.g: A, : ");
    fflush(stdin);
    scanf("%c", &tmp);

    user.coord_x = tmp - 'A';

    //test x coordinates
    if (user.coord_x < 0 || user.coord_x >= 7) {
        printf("There is an error in coordinates, try again\n");
        goto print;
    }

    //find y
    user.coord_y = -1;
    for (int i = 5; i >= 0; i--) {
        if (plateau[user.coord_x][i] == ' ') {
            user.coord_y = i;
            break;
        }
    }

    //test y coordinates
    if (user.coord_y == -1) {
        printf("Column is full, try again\n");
        goto print;
    } else if (tab_full(plateau)==1) {
        printf("Problem.");
    }

    //place token
    plateau[user.coord_x][user.coord_y] = token;
    return user;
}


/**
 * Function to drain the grid
 * @param plateau : grid
 */
void drain_grid(char plateau[7][6]) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
            plateau[i][j] = ' ';
        }
    }
}


/**
 * Function to check the victory statement
 * Check horizontally
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int horizontal_win(char plateau[7][6], struct Coordinates value, char token) {
    //counter set to -1 so that it doesn't count 2 times the token (left / right)
    int counter_h = -1;

    for (int i = value.coord_x; i < 8; ++i) {
        if (plateau[i][value.coord_y] == token) {
            counter_h++;
        } else {
            break;
        }
    }
    for (int j = value.coord_x; j >= 0; j--) {
        if (plateau[j][value.coord_y] == token) {
            counter_h++;
        } else {
            break;
        }
    }
    if (counter_h == 4) {
        return 1;
    }
    return 0;
}

/**
 * Function to check the victory statement, checks vertical alignment
 * @param plateau : grid
 * @param value : coordinates of the player
 * @param token : X or O
 * @return 1 if a vertical alignment was found, or 0 if not
 */
int vertical_win(char plateau[7][6], struct Coordinates value, char token) {
    int counter_h = 0;
    for (int i = value.coord_y; i < 7; i++) {
        if (plateau[value.coord_x][i] == token) {
            counter_h++;
        } else {
            break;
        }
    }
    if (counter_h == 4) {
        return 1;
    }
    return 0;
}

/**
 * check diagonal from top to bottom left
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int diagonal_top_left(char plateau[7][6], struct Coordinates value, char token) {
    int counter_h = 1;
    for (int i = 0; i < 8; i++) {
        value.coord_x = value.coord_x - 1;
        value.coord_y = value.coord_y + 1;
        if ((value.coord_x >= 0 && value.coord_x < 8) && (value.coord_y >= 0 && value.coord_y < 7)) {
            if (plateau[value.coord_x][value.coord_y] == token) {
                counter_h++;
            } else {
                break;
            }
        } else {
            return 0;
        };
        if (counter_h == 4) {
            return 1;
        }
    }
}

/**
 * check diagonal from bottom to top right
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int diagonal_top_right(char plateau[7][6], struct Coordinates value, char token) {
    int counter_h = 1;
    for (int i = 0; i < 8; i++) {
        value.coord_x = value.coord_x + 1;
        value.coord_y = value.coord_y + 1;
        if ((value.coord_x >= 0 && value.coord_x < 8) && (value.coord_y >= 0 && value.coord_y < 7)) {
            if (plateau[value.coord_x][value.coord_y] == token) {
                counter_h++;
            } else {
                break;
            }
        } else {
            return 0;
        }
        if (counter_h == 4) {
            return 1;
        }
    }
}


/**
 * check diagonal from bottom to top right
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int diagonal_bottom_right(char plateau[7][6], struct Coordinates value, char token) {
    int counter_h = 1;
    for (int i = 0; i < 8; i++) {
        value.coord_x = value.coord_x + 1;
        value.coord_y = value.coord_y - 1;
        if ((value.coord_x >= 0 && value.coord_x < 8) && (value.coord_y >= 0 && value.coord_y < 7)) {
            if (plateau[value.coord_x][value.coord_y] == token) {
                counter_h++;
            } else {
                break;
            }
        } else {
            return 0;
        };
        if (counter_h == 4) {
            return 1;
        }
    }
}
/**
 * check diagonal from bottom to top left
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int diagonal_bottom_left(char plateau[7][6], struct Coordinates value, char token) {
    int counter_h = 1;
    for (int i = 0; i < 8; i++) {
        value.coord_x = value.coord_x - 1;
        value.coord_y = value.coord_y - 1;
        if ((value.coord_x >= 0 && value.coord_x < 8) && (value.coord_y >= 0 && value.coord_y < 7)) {
            if (plateau[value.coord_x][value.coord_y] == token) {
                counter_h++;
            } else {
                break;
            }
        } else {
            return 0;
        };
        if (counter_h == 4) {
            return 1;
        }
    }
}

/**
 * Function to check the victory statement
 * Check diagonally
 * @param plateau
 * @param value
 * @param token
 * @return
 */
int diagonal_win(char plateau[7][6], struct Coordinates value, char token) {
    if (diagonal_bottom_left(plateau, value, token) == 1) {
        return 1;
    } else if (diagonal_bottom_right(plateau, value, token) == 1) {
        return 1;
    } else if (diagonal_top_right(plateau, value, token) == 1) {
        return 1;
    } else if (diagonal_top_left(plateau, value, token) == 1) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * To check if the game is over
 * @param plateau
 * @param input_user
 * @param token
 * @return 1 if someone won, 2 if the grid is full, 0 if neither
 */
int hasWon(char plateau[7][6], struct Coordinates input_user, char token) {
    if (vertical_win(plateau, input_user, token) == 1 || horizontal_win(plateau, input_user, token) == 1 ||
        diagonal_win(plateau, input_user, token) == 1) {
        return 1;
    } else if (tab_full(plateau) == 1) {
        return 2;
    } else {
        return 0;
    }
}

/**
 * Register winners in file 'winners.txt'
 * @param info
 * @param p_timer : timer at the end of the game
 */
void register_winner(struct User info, float *p_timer){
    FILE *fichier = NULL;
    fichier = fopen("winners.txt", "a+");
    if (fichier != NULL) {
        printf("\n");
        printf("Save the winner's info: \n");
        printf("First name:  \n");
        scanf("%s", info.first_name );
        printf("Last name: \n");
        scanf("%s", info.last_name);
        info.time=*p_timer;
        fprintf(fichier, "%s %s %.2f seconds\n", info.first_name, info.last_name, info.time);
    }
    fclose(fichier);
}

/**
 * function that displays the content of the "winners.txt" file
 */
void display_winners() {
    FILE *fichier = NULL;
    fichier = fopen("winners.txt", "r");
    int taille = 100;
    char word[taille];
    printf("\nList of winners *****************\n");
    if (fichier != NULL) {
        while(fgets(word, taille, fichier)!=NULL){
            printf("%s", word);
        }
    }
    printf("\n************************************\n");
    fclose(fichier);
}