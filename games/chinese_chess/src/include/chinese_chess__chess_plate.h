#ifndef CHINESE_CHESS__CHESS_PLATE_H_
#define CHINESE_CHESS__CHESS_PLATE_H_

#include "chinese_chess__init.h"

class ChessPlate {
private:
    ChessPiece** m_ptr_ptr_pieces;
    int m_round;
    char* m_ptr_history;
    bool m_is_last_operation_sucessful;

    void printLine(int line);
    void printBackGroundLine(int line);
    bool isOperationLegal(ChessPiece* ptr_piece, int x, int y, int end_x, int end_y);
    void getKingPosition(int* ptr_x, int* ptr_y, bool is_red);
public:
    ChessPlate();
    bool isCheckmate();
    int getStatus(bool is_red_turn);
    void pieceMove(int x, int y, int end_x, int end_y);
    void actionOperate(char* ptr_command, bool is_red);

    ~ChessPlate() {
        delete [] this->m_ptr_ptr_pieces;
        delete [] this->m_ptr_history;
    }
    void print() {
        this->printBackGroundLine(-1);
        for (int i = 0; i < 10; i++) {
            this->printLine(i);
            this->printBackGroundLine(i);
        }
    }
    void setIsLastOperationSucessful(bool is) {
        this->m_is_last_operation_sucessful = is;
    }
    bool getIsLastOperationSucessful() {
        return this->m_is_last_operation_sucessful;
    }
    void storage(char* ptr_op) {
        this->m_round++;
        for (int i = 0; i < 4; i++) {
            *(this->m_ptr_history + this->m_round * 4 + i - 4) = *(ptr_op + i);
        }
    }
    int getRoundCount() {
        return this->m_round;
    }
    void getHistory(int round_index, char* ptr_op) {
        for (int i = 0; i < 4; i++) {
            *(ptr_op + i) = *(this->m_ptr_history + round_index * 4 + i - 4);
        }
    }
};

#include "chinese_chess__chess_plate.cc"

#endif