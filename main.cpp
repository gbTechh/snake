#include <iostream>
#include <conio.h> // Para getch()
#include <cstdlib> // Para las funciones rand() y srand()
#include <ctime>
#include <windows.h> // Para Sleep()

int randNumber(int);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int key;
    int fila = 10, col = 20;
    char board[10][20];
    char block = '=', paint = 'O', head = '0', food = 'u';
    bool gameOver = false;
    int x = 2, y = 2;

    int intervalo_milisegundos = 1300;

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < col; j++) {
            board[i][j] = block;
        }
    }

    int countC = 3;
    int countF = 3;
    int dir = 1;
    int pressKey = -1;
    char coor = 'r';
    int cont = -1;
    int sizeArray = 1000000;
    int coorsArray[sizeArray][2];

    for (int i = 0; i < sizeArray; i++) {
        for (int j = 0; j < 2; j++) {
            coorsArray[i][j] = 103;
        }
    }

    int posF = 3, posC = 3;
    int randF = randNumber(fila - 1);
    int randC = randNumber(col - 1);
    bool primeraEntrada = false;
    int longSnake = 3;

    while (!gameOver) {
        if (_kbhit()) {
            key = _getch();
            if (key == 27) {
                key = _getch();
                switch (key) {
                    case 72: // Tecla UP
                        pressKey = 2;
                        break;
                    case 80: // Tecla DOWN
                        pressKey = 4;
                        break;
                    case 77: // Tecla RIGHT
                        pressKey = 3;
                        break;
                    case 75: // Tecla LEFT
                        pressKey = 1;
                        break;
                    default:
                        break;
                }
            }
        }

        if (pressKey == 1) {
            if (coor != 'r') {
                coor = 'l';
                dir = -1;
                countC--;
                countF += 0;
            } else {
                countC++;
            }
        } else if (pressKey == 2) {
            if (coor != 'b') {
                dir = -1;
                coor = 't';
                countC += 0;
                countF--;
            } else {
                countF++;
            }
        } else if (pressKey == 3) {
            if (coor != 'l') {
                coor = 'r';
                dir = 1;
                countC++;
                countF += 0;
            } else {
                countC--;
            }
        } else if (pressKey == 4) {
            if (coor != 't') {
                coor = 'b';
                dir = 1;
                countC += 0;
                countF++;
            } else {
                countF--;
            }
        } else if (pressKey == -1) {
            countC++;
        }
        cont++;
        coorsArray[cont][0] = countF;
        coorsArray[cont][1] = countC;

        // Rellenar los bloques del tablero
        for (int i = 0; i < fila; i++) {
            for (int j = 0; j < col; j++) {
                board[i][j] = block;
            }
        }

        if (countC >= col || countC < 0) {
            gameOver = true;
            intervalo_milisegundos = 1;
        } else if (countF >= fila || countF < 0) {
            gameOver = true;
            intervalo_milisegundos = 1;
        }

        bool setFood = true;
        while (setFood) {
            if (board[randF][randC] == paint) {
                setFood = false;
                break;
            } else {
                board[randF][randC] = food;
                break;
            }
        }
        int longSnakeForLoop = longSnake;
        for (int i = sizeArray - 1; i >= 0; i--) {
            if (coorsArray[i][0] != 103 && longSnakeForLoop > 0) {
                posF = std::abs(coorsArray[i][0]);
                posC = std::abs(coorsArray[i][1]);
                if (!primeraEntrada) {
                    primeraEntrada = true;
                    if (board[posF][posC] == food) {
                        longSnake++;
                        randF = randNumber(fila - 1);
                        randC = randNumber(col - 1);
                    }
                    std::cout << posF << ", " << posC << std::endl;
                    std::cout << "board: " << board[posF][posC] << "" << posC << std::endl;
                    board[posF][posC] = head;
                } else {
                    board[posF][posC] = paint;
                }
                longSnakeForLoop--;
            }
        }
        primeraEntrada = false;

        // Mostrar en consola el tablero
        for (int i = 0; i < fila; i++) {
            for (int j = 0; j < col; j++) {
                std::cout << board[i][j];
            }
            std::cout << randF << " " << randC << " " << countC << "\n";
        }

        std::cout << "\n";
        Sleep(intervalo_milisegundos);
        system("cls");
    }
    return 0;
}

int randNumber(int num) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randNumber = rand() % (num + 1);
    return randNumber;
}
