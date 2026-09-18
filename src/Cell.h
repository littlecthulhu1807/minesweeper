#ifndef CELL_H
#define CELL_H

class Cell{

public:
    Cell();
    ~Cell();

    enum Flag {DEFAULT, CLEAR, FLAGGED};
    bool isMine{false};
    bool init{false};
    int neighborMines{0};

    Flag state{};

};

#endif