#include"InputHandler.h"

#include<iostream>
#include<limits>

//Check the current operating system and include the appropriate header


InputHandler::InputHandler(){}

InputHandler::InputHandler(Field* fieldRef, bool* ref):
m_fieldRef(fieldRef),
m_gamestateRef(ref){

}

InputHandler::~InputHandler(){}

//Assign the right input checking method based on the OS
#if defined(WIN)
void InputHandler::inputCheck(){
    std::cout << "Windows OS!\n";
    if (_kbhit()) {
        m_ch = _getch();
        m_inputAvailable = true;
    }
    if (m_inputAvailable) {
        actionSwitch(m_ch);
        m_inputAvailable = false;
        //std::cin.clear();
    }
}

bool InputHandler::linux_kbhit(){};
oid InputHandler::terminalSetup(){};
    
#elif defined(LIN)
bool InputHandler::inputCheck(){
    if (linux_kbhit()) {
        read(STDIN_FILENO, &m_ch, 1);
        m_inputAvailable = true;
    }
    if (m_inputAvailable) {
        actionSwitch(m_ch);
        m_inputAvailable = false;
        //std::cin.clear();
    }
    return m_inputAvailable;
}

bool InputHandler::linux_kbhit(){
    // 1. Set up poll structure for stdin (file descriptor 0)
    struct pollfd pfd;
    pfd.fd = 0; 
    pfd.events = POLLIN;

    // 2. Poll stdin for 0 milliseconds (return immediately)
    // Returns > 0 if data is ready to be read
    return poll(&pfd, 1, 0) > 0;
};

void InputHandler::terminalSetup(){
    if(!m_terminalIsSet){
        // Save original terminal settings and disable buffered input (canonical mode)
        tcgetattr(STDIN_FILENO, &m_oldTerm);
        m_newTerm = m_oldTerm;
        m_newTerm.c_lflag &= ~(ICANON | ECHO); // Turn off Enter buffering and echoing
        tcsetattr(STDIN_FILENO, TCSANOW, &m_newTerm);
        m_terminalIsSet = true;
    }
    else if(m_terminalIsSet){
        // Restore original terminal settings before exiting
        tcsetattr(STDIN_FILENO, TCSANOW, &m_oldTerm);
    }
}
    
#else
void InputHandler::inputCheck(){
    std::cout << "ERROR UNSUPPORTED SYSTEM OS!\n";
    return;
}

bool InputHandler::linux_kbhit(){};
oid InputHandler::terminalSetup(){};
#endif

void InputHandler::actionSwitch(char action){
    switch (action){
    case 'w':
        m_fieldRef->move(1);
        break;
    case 'a':
        m_fieldRef->move(2);
        break;
    case 's':
        m_fieldRef->move(3);
        break;
    case 'd':
        m_fieldRef->move(4);
        break;
    case 'f':
        m_fieldRef->setFlag();
        break;
    case 'r':
        m_fieldRef->fieldCheck();
        break;
    case 'q':
        *m_gamestateRef = false;
        break;
    
    default:
        m_fieldRef->move(0);
    }
};