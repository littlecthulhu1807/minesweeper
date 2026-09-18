#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include"Field.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #define WIN
#elif defined(__linux__)
    #include <poll.h>
    #include <termios.h>
    #include <unistd.h>
    #define LIN
#else
    #error "Unsupported Operating System"
#endif

class InputHandler{

    Field* m_fieldRef{nullptr};
    bool m_terminalIsSet{false};
    struct termios m_oldTerm, m_newTerm;
    bool* m_gamestateRef{nullptr};

    char m_ch = 0;
    bool m_inputAvailable = false;

public:
    InputHandler();
    InputHandler(Field* fieldRef, bool* ref);
    ~InputHandler();

    void inputCheck();

    bool linux_kbhit();
    void terminalSetup();
    void actionSwitch(char action);
};

#endif