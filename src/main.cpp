#include<iostream>


#include"Field.h"
#include"InputHandler.h"

#if defined(_WIN32) || defined(_WIN64)
    #define SLEEP Sleep(200);
    #define CLEAR std::system("cls");
#elif defined(__linux__)
    #define SLEEP usleep(200000);
    #define CLEAR std::system("clear");
#else
    #error "Unsupported Operating System"
#endif

int main(){

    bool gamestate{true};
    Field field = Field(30, &gamestate);
    InputHandler inputH = InputHandler(&field, &gamestate);

    inputH.terminalSetup();

    while(gamestate){
        CLEAR

        inputH.inputCheck();

        field.draw();

        SLEEP
    }
    std::cout << "\nQuitting! Goodbye\n";

    inputH.terminalSetup();

    return 0;
}