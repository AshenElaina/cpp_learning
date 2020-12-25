#include <iostream>
#include <Windows.h>
#include "include/chinese_chess__chess_piece.h"
#include "include/chinese_chess__chess_plate.h"
using namespace std;

void GamePlay(ChessPlate* ptr_plate);
void Replay(ChessPlate* ptr_plate);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "=====================================================" << endl;
    cout << "[基於 C++ 的中國象棋終端遊戲]" << endl;
    cout << "版本：ver. 2.0.0" << endl;
    cout << "作者：AnarchYin" << endl;
    cout << "開發日期：23-Dec-20" << endl;
    cout << "為了更好的畫面效果，建議您使用 Sarasa Mono 系列字體。" << endl;
    cout << "=====================================================" << endl;
    ChessPlate* ptr_plate = NULL;
    int command = 1;
    while (command) {
        cout << "\n 0 : 退出。\n 1 : 開始新遊戲。\n 2 : 回顧上局。" << endl;
        cout << "請輸入指令: ";
        cin >> command;
        switch (command) {
        case 0: break;
        case 1:
            if (ptr_plate != NULL) {
                delete ptr_plate;
            }
            ptr_plate = new ChessPlate();
            ptr_plate->print();
            GamePlay(ptr_plate);
            break;
        case 2:
            if (ptr_plate == NULL) {
                cout << "沒有上局遊戲的信息。" << endl;
            } else {
                Replay(ptr_plate);
            }
            break;
        default:
            cout << "無效的指令。" << endl;
        }
    }
    return 0;
}

void GamePlay(ChessPlate* ptr_plate) {
    bool is_red_turn = true;
    char* ptr_str = new char[128];
    cin.get();
    while (!ptr_plate->getStatus(is_red_turn)) {
        if (ptr_plate->isCheckmate()) {
            cout << (result ? "將軍！\n" : "");
        }
        ptr_plate->setIsLastOperationSucessful(false);
        while (!ptr_plate->getIsLastOperationSucessful()) {
            cout << (is_red_turn ? "紅方" : "黑方") << ": ";
            for (int i = 0; * (ptr_str + i - 1) != '\n'; i++) {
                *(ptr_str + i) = cin.get();
            }
            ptr_plate->actionOperate(ptr_str, is_red_turn);
            ptr_plate->print();
        }
        is_red_turn = !is_red_turn;
        ptr_plate->storage(ptr_str);
    }
    if (ptr_plate->getStatus(is_red_turn) == 1) {
        cout << "紅方勝。" << endl;
    } else {
        cout << "黑方勝。" << endl;
    }
    delete [] ptr_str;
}

void Replay(ChessPlate* ptr_plate) {
    ChessPlate* ptr_rep_plate = NULL;
    char* ptr_op = new char[6];
    ptr_rep_plate = new ChessPlate();
    int count = ptr_plate->getRoundCount();
    bool is_red_turn = true;
    ptr_rep_plate->print();
    for (int i = 1; i <= count; i++) {
        Sleep(3000);
        ptr_plate->getHistory(i, ptr_op);
        *(ptr_op + 4) = '\n';
        ptr_rep_plate->actionOperate(ptr_op, is_red_turn);
        ptr_rep_plate->print();
        is_red_turn = !is_red_turn;
    }
    delete [] ptr_op;
    delete ptr_rep_plate;
}