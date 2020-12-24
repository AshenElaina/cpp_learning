#ifndef CHINESE_CHESS__CHESS_PIECE_H_
#define CHINESE_CHESS__CHESS_PIECE_H_

#include "chinese_chess__init.h"
#include <iostream>
using namespace std;

class ChessPiece {
private:
    int m_pos_x;
    int m_pos_y;
    bool m_is_red;
    char m_type;
public:
    virtual void printDisplayName();
    ChessPiece() {}
    ChessPiece(int x, int y) {
        this->m_pos_x = x;
        this->m_pos_y = y;
        this->m_type = '.';
    }
    void init(int x, int y, bool is_red, char type) {
        this->m_is_red = is_red;
        this->m_pos_x = x;
        this->m_pos_y = y;
        this->m_type = type;
    }
    virtual bool isMoveLegal(int x, int y, int end_x, int end_y) {
        return false;
    }
    virtual int getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses) {
        return 0;
    }
    bool isRed() {
        return this->m_is_red;
    }
    bool isVoid() {
        return (this->m_type == '.');
    }
    char getType() {
        return this->m_type;
    }
    void setPosition(int x, int y) {
        this->m_pos_x = x;
        this->m_pos_y = y;
    }
    void getPosition(int* ptr_x, int* ptr_y) {
        *ptr_x = this->m_pos_x;
        *ptr_y = this->m_pos_y;
    }
};

class King: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    King(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'k');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "帥]" : "將)");
    }
};

class Guard: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    Guard(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'g');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "仕]" : "士)");
    }

};

class Minister: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    int getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses);
    Minister(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'm');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "相]" : "象)");
    }
};

class Horse: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    int getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses);
    Horse(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'h');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "傌]" : "馬)");
    }
};

class Rook: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    int getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses);
    Rook(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'r');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "俥]" : "車)");
    }
};

class Cannon: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    int getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses);
    Cannon(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 'c');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "炮]" : "砲)");
    }
};

class Soldier: public ChessPiece {
public:
    bool isMoveLegal(int x, int y, int end_x, int end_y);
    Soldier(int x, int y, bool is_red = true) {
        this->init(x, y, is_red, 's');
    }
    void printDisplayName() {
        cout << (this->isRed() ? "兵]" : "卒)");
    }
};

#include "chinese_chess__chess_piece.cc"

#endif