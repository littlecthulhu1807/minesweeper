#ifndef FIELD_H
#define FIELD_H

#include"Cell.h"
#include"RandomEngine.hpp"

class Field{
    unsigned int m_size;
    Cell* m_cells;
    RandomEngine m_randEngine{RandomEngine()};
    int m_mineChance{15};
    unsigned int m_cursor{0};
    bool* m_gamestateRef{nullptr};
    bool m_firstSetupDone{false};

    void init();
    

public:
    Field();
    Field(unsigned int size, bool* ref);

    ~Field();

    void draw();
    void move(int input);

    void fieldCheck();
    void setFlag();
    void reveal(int cellNum);

    int neigborCheck(int cell);

    void floodFill(int start);
    bool setFloodFillIds(int start, int* arrayRef, int arrayPos);
    bool floodFillBufferCkeck(int buffer, int* arrayRef, int arrayPos);


};

#endif
