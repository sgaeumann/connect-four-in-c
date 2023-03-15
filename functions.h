//
// Created by sarah.gaumann on 14.12.2022.
//

#ifndef PUISSANCE_QUATRE_FUNCTIONS_H
#define PUISSANCE_QUATRE_FUNCTIONS_H

typedef struct Coordinates Coordinates;
struct Coordinates {
    int coord_y;
    int coord_x;
};

typedef struct User User;
struct User{
    char first_name[25];
    char last_name[25];
    float time;
};

void displayGrid(char plateau[7][6], char token);
int tab_full(char plateau[7][6]);
void drain_grid (char plateau[7][6] );
Coordinates input_joueur(char plateau[7][6], char token);
int horizontal_win(char plateau[7][6], struct Coordinates value, char token);
int vertical_win(char plateau[7][6], struct Coordinates value, char token);
int diagonal_win(char plateau[7][6], struct Coordinates value, char token);
int diagonal_bottom_left(char plateau[7][6], struct Coordinates value, char token);
int diagonal_bottom_right(char plateau[7][6], struct Coordinates value, char token);
int diagonal_top_right(char plateau[7][6], struct Coordinates value, char token);
int diagonal_top_left(char plateau[7][6], struct Coordinates value, char token);
int hasWon(char plateau[7][6], struct Coordinates value, char token);
void register_winner(struct User,float *p_timer);
void display_winners();

#endif //PUISSANCE_QUATRE_FUNCTIONS_H