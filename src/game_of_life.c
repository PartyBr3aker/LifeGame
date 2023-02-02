// Copyright 2022 doretaa ronnelmi tardisad
#include <stdio.h>
#include <stdlib.h>
#define X_MAX 80
#define Y_MAX 25
#define NUMBER_OF_ELEMENTS 2000
void Full(char** matr, int* buffer);
void Display(char** matr);
int DeadOrAlive(char** matr, int y_ini, int x_ini);
void Turn(char** matr, char** matr2);
void Copy(char** matr, char** matr2);
int Input(int *massive);
void StartGame(char** matr, int *buf, char** matr2);
void GameProcess(char** matr, char** matr2, int* buffer);
void GameOver(int* buffer, char** matr);
void transform(char* buffer, char** matr);
void GameStart(int* buffer, char** matr);

int main(void) {
    int binary_int[NUMBER_OF_ELEMENTS];
    char playgr[Y_MAX][X_MAX];
    char playgrn[Y_MAX][X_MAX];
    char* play_ground[Y_MAX];
    char* p = (char *)playgr;
    char* play_ground_next[Y_MAX];
    char* p1 = (char *)playgrn;
    transform(p, play_ground);
    transform(p1, play_ground_next);
    GameStart(binary_int, play_ground);
    if (Input(binary_int)) {
        StartGame(play_ground, binary_int, play_ground_next);
        GameProcess(play_ground, play_ground_next, binary_int);
    } else {
        printf("n/a");
    }
    return 0;
}

int Input(int *massive) {
    int works = 1;
    char c;
    for (int i = 0; i < 2000; i++) {
        massive[i] = -1;
    }
    for (int i = 0; i < 2000; i++) {
        scanf("%1d", &massive[i]);
        if (massive[i] == 1 || massive[i] == 0) {
        } else {
            works = 0;
        }
    }
    c = getchar();
    if (c != (int)(EOF) && c != '\n' && (massive[1999] == 1 || massive[1999] == 0)) {
        works = 0;
    }
    return works;
}

void Full(char** matr, int* buffer) {
    int m = 0;
    for (int i = 0; i < Y_MAX; i++) {
        for (int j = 0; j < X_MAX; j++) {
            if ( buffer[m] == 1)
            matr[i][j] = '#';
            else
            matr[i][j] = ' ';
            ++m;
        }
    }
}

void Display(char** matr) {
    for (int i = 0; i < Y_MAX; i++) {
        for (int j = 0; j < X_MAX; j++) {
            printf("%c", matr[i][j]);
        }
        if (i != Y_MAX - 1) {
            printf("\n");
        }
    }
}

int DeadOrAlive(char** matr, int y_ini, int x_ini) {
    int counter = 0;
    for (int i = y_ini - 1; i <= y_ini + 1; i++) {
        for (int j = x_ini - 1; j <= x_ini + 1; j++) {
            if (i != y_ini || j != x_ini) {
                if (i < 0 && j < 0) {
                    if (matr[Y_MAX + i][X_MAX + j] == '#')
                        counter++;
                }
                if (i < 0 && j >= 0) {
                    if (matr[Y_MAX + i][j % X_MAX] == '#')
                        counter++;
                }
                if (i >= 0 && j >= 0) {
                    if (matr[i % Y_MAX][j % X_MAX] == '#')
                        counter++;
                }
                if (i >= 0 && j < 0) {
                    if (matr[i % Y_MAX][X_MAX + j] == '#')
                        counter++;
                }
            }
        }
    }
    return counter;
}

void Turn(char** matr, char** matr2) {
    for (int i = 0; i < Y_MAX; i++) {
        for (int j = 0; j < X_MAX; j++) {
            if (matr[i][j] == '#') {
                if (DeadOrAlive(matr, i, j) < 2 \
                || DeadOrAlive(matr, i, j) > 3) {
                    matr2[i][j] = ' ';
                }
                if (DeadOrAlive(matr, i, j) == 2 \
                || DeadOrAlive(matr, i, j) == 3) {
                    matr2[i][j] = '#';
                }
            }
            if (matr[i][j] == ' ') {
                if (DeadOrAlive(matr, i, j) == 3) {
                    matr2[i][j] = '#';
                }
            }
        }
    }
}

void Copy(char** matr, char** matr2) {
     for (int i = 0; i < Y_MAX; i++) {
        for (int j = 0; j < X_MAX; j++) {
            matr2[i][j] = matr[i][j];
        }
    }
}

void StartGame(char** matr, int *buf, char** matr2) {
    if (freopen("/dev/tty", "rw", stdin) != NULL) {
        Full(matr, buf);
        Display(matr);
        printf("Generation 1\n");
        Copy(matr, matr2);
    }
}

void GameProcess(char** matr, char** matr2, int* buffer) {
    int step = 1;
    while (1) {
        char control = getchar();
        if (control == (int)(EOF)) {
            if (freopen("/dev/tty", "rw", stdin) != NULL) {
                Display(matr);
                printf("Generation %d\n", step);
            }
        } else if (control == '\n') {
            Display(matr);
            printf("Generation %d\n", step);
        } else {
            char done = getchar();
            if (control == ' ' && done == '\n') {
                Turn(matr, matr2);
                Copy(matr2, matr);
                Display(matr);
                step++;
                printf("Generation %d\n", step);
            } else if ((control == 'q' || control == 'Q') && done == '\n') {
                GameOver(buffer, matr);
                break;
            } else {
                Display(matr);
                printf("Generation %d\n", step);
                while (control != '\n') {
                    control = getchar();
                }
            }
        }
    }
}

void GameOver(int* buffer, char** matr) {
    FILE *file;
    file = fopen("data/gameover.txt", "r");
    for (int i = 0; i < 2000; i++) {
        fscanf(file, "%1d", &buffer[i]);
    }
    Full(matr, buffer);
    Display(matr);
}

void transform(char* buffer, char** matr) {
    for (int i = 0; i <= Y_MAX; i++)
        matr[i] = buffer + i * X_MAX;
}

void GameStart(int* buffer, char** matr) {
    FILE *file1;
    file1 = fopen("data/gamestart.txt", "r");
    for (int i = 0; i < 2000; i++) {
        fscanf(file1, "%1d", &buffer[i]);
    }
    Full(matr, buffer);
    Display(matr);
}
