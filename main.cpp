#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib> // Para las funciones rand() y srand()
#include <ctime>

int detectKey();
int randNumber(int);

int main(int argc, char *argv[])
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    srand(time(NULL));
    int ch;
    int key;
    int fila{10}, col{20};
    char board[fila][col];
    char block = '=', paint='O', head = '0', food='u';
    bool gameOver = false;
    int x = 2, y = 2;
  
    int intervalo_segundos = 1300;
    
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
    int cont = -1;
    int sizeArray = 1000000;
    int coorsArray[sizeArray][2];
    
    
    for (int i = 0; i < sizeArray; i++) {
        for (int j = 0; j < 2; j++) {
            coorsArray[i][j] = 103;
        }
    }
    
   

    int posF=3, posC=3;
    int randF = randNumber(fila - 1);
    int randC = randNumber(col - 1);
    bool primeraEntrada = false;
    int longSnake = 3;
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
            std::cout<<"entra aqui"<<std::endl;
            countC++;
        }
        cont++;
        coorsArray[cont][0] = countF;
        coorsArray[cont][1] = countC;

        
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

        bool setFood = true;
        while(setFood){
        
            if(board[randF][randC] == paint){
                setFood = false;
                break;
            }else{
                board[randF][randC] = food;
                break;
            }
        }
        int longSnakeForLoop = longSnake;
        for(int i = sizeArray - 1; i >= 0; i--){
            if (coorsArray[i][0] != 103 && longSnakeForLoop > 0 ) {
                // std::cout << "entra" << std::endl;
                posF = std::abs(coorsArray[i][0]);
                posC = std::abs(coorsArray[i][1]);
                // std::cout <<"postC: "<< posC <<" postF: " <<posF<< "\n";
                if(!primeraEntrada){
                    primeraEntrada = true;
                    
                    if(board[posF][posC] == food){
                        longSnake++;
                        randF = randNumber(fila - 1);
                        randC = randNumber(col - 1);
                    }
                    std::cout<<posF<<", "<<posC<<std::endl;
                    std::cout<<"board: "<<board[posF][posC]<<""<<posC<<std::endl;
                    board[posF][posC] = head;
                    
                }else{
                    board[posF][posC] = paint;
                }

                longSnakeForLoop--; 
            }
            
        }
        primeraEntrada = false;
        
       //mostrar en consola el tablero
        for (int i = 0; i < fila; i++) {
           for (int j = 0; j < col; j++) {
               std::cout << board[i][j];
           }
           std::cout<<randF<<" "<<randC<<" "<<countC<<"\n";
        }

        
        // for (int i = 0; i < 50; i++) {
        //     std::cout << "[" << coorsArray[i][0] << ", " << coorsArray[i][1] << "]";
        //     if (i < sizeArray - 1) {
        //         std::cout << ", ";
        //     }
        // }
        std::cout<<"\n";

        
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

int randNumber(int num){  
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randNumber = std::rand() % (num + 1);
    return randNumber;
}