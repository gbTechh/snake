#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int detectKey();

int main(int argc, char *argv[])
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);


    int ch;
    int key;
    int fila{5}, col{25};
    char board[fila][col];
    char block = '=', paint='0';
    bool gameOver = false;
    int x = 2, y = 2;
    int longSnake =3;
  
    int intervalo_segundos = 500;
    
    for (int i = 0; i < fila ; i ++){
        for (int j = 0; j < col ; j ++) {
            board[i][j] = block;
        }
    }

    int countC = 3;
    int countF = 3;
    int dir = 1;
    int pressKey = -1;
    char coor = 'r';
    while (!gameOver) {
        while ((key = detectKey()) != -1) {
            pressKey = key;
        }


        if(pressKey == 1){
            if(coor != 'r'){
                coor = 'l';
                dir = -1;
                countC--;
                countF+=0;
            }else{
                countC++;
            }
            
        }else if(pressKey == 2) {
            if(coor != 'b'){
                dir = -1;
                coor = 't';
                countC += 0;
                countF--;
            }else{
                countF++;
            }
           
        }else if(pressKey == 3) {
            if(coor != 'l'){
                coor = 'r';
                dir = 1;
                countC++;
                countF += 0;
            }else{
                countC--;
            }          
            
        }else if(pressKey == 4 ) {
            if(coor != 't'){
                coor = 'b';
                dir = 1;
                countC+=0;
                countF++;
            }else{
                countF--;
            }
        }else if(pressKey == -1){
            countC++;
        }

        //rellenar los bloques del tablero
        for (int i = 0; i < fila; i++) {
            for (int j = 0; j < col; j++) {
                board[i][j] = block;               
            }
        }

        if (countC >= col  || countC < 0) {
            gameOver = true;
            intervalo_segundos = 1;

        }else if (countF >= fila || countF < 0) {
            gameOver = true;
            intervalo_segundos = 1;

        }
        // board[countF][countC-1] = paint;
        for(int i = longSnake; i > 0; i-- ){

            board[countF][countC+i-longSnake] = paint;
        }

        //mostrar en consola el tablero
        for (int i = 0; i < fila; i++) {
            for (int j = 0; j < col; j++) {
                std::cout << board[i][j];
            }
            std::cout<<coor<<" "<<countC<<"\n";
        }

        
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalo_segundos));
        system("clear");

    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}

int detectKey (){
    int key = -1;
    int ch = getchar();

    if (ch != EOF) {
        if (ch == 27) {
            ch = getchar(); 
            if (ch == 91) {
                ch = getchar(); 
                switch (ch) {
                    case 65: // Tecla UP
                        key = 2;
                        break;
                    case 66: // Tecla DOWN
                        key = 4;
                        break;
                    case 67: // Tecla RIGHT
                        key = 3;
                        break;
                    case 68: // Tecla LEFT
                        key = 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return key;
}