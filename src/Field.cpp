#include"Field.h"
#include<iostream>

Field::Field(){}

Field::Field(unsigned int size, bool* ref):
m_size(size),
m_gamestateRef(ref){
    init();
}

Field::~Field(){
    delete[] m_cells;
}

void Field::init(){
    m_cells = new Cell[m_size * m_size];

    for(int i{0}; i < (m_size * m_size); i++){
        m_cells[i].state = Cell::Flag::DEFAULT;
    }
}

void Field::draw(){
    std::cout << "MOVE WITH : W A S D\nF TO SET/REMOVE THE FLAG\nR TO REVELA\n";
    for(int y{0}; y < m_size; y++){
            for(int x{0}; x < m_size; x++){

                //Check the field for being the active cursor and draw it accordingly
                if((x + (y * m_size)) == m_cursor){
                    //Default and not Flagged
                    if(m_cells[x + (y * m_size)].state == Cell::Flag::DEFAULT && m_cells[x + (y * m_size)].state != Cell::Flag::FLAGGED){
                        //Draw the Cursor
                        std::cout << "\033[5;32;103m" << '#' << "\033[0m";
                    }
                    //Flagged
                    else if(m_cells[x + (y * m_size)].state == Cell::Flag::FLAGGED){
                        //Draw a flag with the cursor on it
                        std::cout << "\033[5;31;103m" << 'F' << "\033[0m";
                    }
                    else if(m_cells[x + (y * m_size)].state == Cell::Flag::DEFAULT && m_cells[x + (y * m_size)].state != Cell::Flag::FLAGGED){
                        //Draw the Cursor
                        std::cout << "\033[5;32;103m" << '#' << "\033[0m";
                    }
                    
                    else if(m_cells[x + (y * m_size)].state == Cell::Flag::CLEAR){
                        //
                        if(m_cells[x + (y * m_size)].neighborMines > 0){
                            std::cout << "\033[5;32;103m" << m_cells[x + (y * m_size)].neighborMines << "\033[0m";
                        }
                        else{
                            std::cout << "\033[5;32;103m" << '_' << "\033[0m";
                        } 
                    }
                    
                }
                //Draw the other fields by default
                else {
                    if(m_cells[x + (y * m_size)].state == Cell::Flag::DEFAULT){
                        //Base case, drawing the hidden cell
                        std::cout << "\033[1;32;40m" << '#' << "\033[0m";
                    }
                    else if(m_cells[x + (y * m_size)].state == Cell::Flag::FLAGGED){
                        //Draw a default flag
                        std::cout << "\033[1;31;40m" << 'F' << "\033[0m";
                    }
                    else if(m_cells[x + (y * m_size)].state == Cell::Flag::CLEAR ){
                        //
                        if(m_cells[x + (y * m_size)].neighborMines > 0){
                            std::cout << "\033[1;32;107m" << m_cells[x + (y * m_size)].neighborMines << "\033[0m";
                        }
                        else{
                            std::cout << "\033[1;32;107m" << '_' << "\033[0m";
                        }
                    }
                    //DEBUG
                    else{
                        //Error exception
                        std::cout << "\033[1;31;40m" << 'E' << "\033[0m";
                    }
                }
            }
        std::cout << '\n';
    }
}

void Field::move(int input){
    switch(input){
        case 1:
            if((int)m_cursor - (int)m_size < 0){
                m_cursor = m_cursor;
            }
            else{
                m_cursor = m_cursor - m_size;
            }
            break;
        case 2:
            if((int)m_cursor - 1 <= 0){
                m_cursor = m_cursor;
            }
            else{
                m_cursor = m_cursor - 1;
            }
            break;
        case 3:
            if(m_cursor + m_size >= m_size * m_size){
                m_cursor = m_cursor;
            }
            else{
                m_cursor = m_cursor + m_size;
            }
            break;
        case 4:
            if(m_cursor + 1 >= m_size * m_size){
                m_cursor = m_cursor;
            }
            else{
                m_cursor = m_cursor + 1;
            }
            break;
        default:
            m_cursor = m_cursor;
    }
}

void Field::fieldCheck(){
    Cell* cellRefBuffer{nullptr};

    if (!m_firstSetupDone){
        for(int i{0}; i < m_size * m_size; i++){
            bool mineBuffer{m_randEngine.randomBool(m_mineChance)};
            if (mineBuffer && i != m_cursor){
                m_cells[i].isMine = mineBuffer;
            }
        }

        for(int i{0}; i < m_size * m_size; i++){

            cellRefBuffer = &m_cells[i];
            int neighborBuffer{neigborCheck(i)};
            cellRefBuffer->neighborMines = neighborBuffer;
        }
        m_firstSetupDone = true;
    }


    if(m_cells[m_cursor].isMine){
        reveal(m_cursor);
        *m_gamestateRef = false;
        std::cout << "BOOM! YOU HIT A MINE!\n";
        return;
    }
    else{
        reveal(m_cursor);
        floodFill(m_cursor);
    }
}

void Field::setFlag(){
    if(m_cells[m_cursor].state == Cell::Flag::DEFAULT){
        m_cells[m_cursor].state = Cell::Flag::FLAGGED;
    }
    else if(m_cells[m_cursor].state == Cell::Flag::FLAGGED){
        m_cells[m_cursor].state = Cell::Flag::DEFAULT;
    }
}

void Field::reveal(int cellNum){
    m_cells[cellNum].state = Cell::Flag::CLEAR;
}

int Field::neigborCheck(int cell){

    int surroundingMines{0};
    int indexBuffer{0};
    Cell* cellRefBuffer{nullptr};

    //if cell is valid(inside of playboard) && if the cell is a mine add neighbor
    if((cell - (m_size + 1)) >= 0){
        indexBuffer = cell - (m_size + 1);
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell - m_size) >= 0){
        indexBuffer = cell - m_size;
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell - (m_size - 1)) >= 0){
        indexBuffer = cell - (m_size - 1);
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell - 1) >= 0){
        indexBuffer = cell - 1;
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell + 1) < m_size * m_size){
        indexBuffer = cell + 1;
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell + (m_size - 1)) < m_size * m_size){
        indexBuffer = cell + (m_size - 1);
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell + m_size) < m_size * m_size){
        indexBuffer = cell + m_size;
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    if((cell + (m_size + 1)) < m_size * m_size){
        indexBuffer = cell + (m_size + 1);
        cellRefBuffer = &m_cells[indexBuffer];
        if(cellRefBuffer->isMine){
            surroundingMines++;
        }
    }
    
    return surroundingMines;
}

void Field::floodFill(int start){
    
    int ids[8]{};
    int iterator{0};

    for(int i{0}; i < 8; i++){
        ids[i] = -1;
        if(setFloodFillIds(start, ids, i)){
            iterator++;
        }
    }

    if(iterator <= 0){
        return;
    }
    else{
        for(int i{0}; i < 8; i++){
            if(ids[i] != -1){
                floodFill(ids[i]);
            }
        }
    }
}

bool Field::setFloodFillIds(int start, int* arrayRef, int arrayPos){

    int indexBuffer{0};
    bool logicBuffer{false};

    switch (arrayPos){
    case 0:
        indexBuffer = start - (m_size + 1);
        if(indexBuffer >= 0){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 1:
        indexBuffer = start - m_size;
        if(indexBuffer >= 0){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        } 
        break;
    case 2:
        indexBuffer = start - (m_size - 1);
        if(indexBuffer >= 0){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 3:
        indexBuffer = start - 1;
        if(indexBuffer >= 0){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 4:
        indexBuffer = start + 1;
        if(indexBuffer < m_size * m_size){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 5:
        indexBuffer = start + (m_size - 1);
        if(indexBuffer < m_size * m_size){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 6:
        indexBuffer = start + m_size;
        if(indexBuffer < m_size * m_size){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    case 7:
        indexBuffer = start + (m_size + 1);
        if(indexBuffer < m_size * m_size){
            logicBuffer = floodFillBufferCkeck(indexBuffer, arrayRef, arrayPos);
            return logicBuffer;
        }
        break;
    default:
        return logicBuffer;
        break;
    }

    return logicBuffer;
}

bool Field::floodFillBufferCkeck(int buffer, int* arrayRef, int arrayPos){

    if(m_cells[buffer].state != Cell::Flag::CLEAR && m_cells[buffer].isMine == false){  // Unrevealed cell
        reveal(buffer);  // Always reveal it first
        
        if(m_cells[buffer].neighborMines == 0){  // Only recurse if 0 neighboring mines
            arrayRef[arrayPos] = buffer;
            return true;
        }
    }
    return false;
}