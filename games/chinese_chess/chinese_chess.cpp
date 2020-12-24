#include <iostream>
#include <Windows.h>
using namespace std;

static char EMPTY_PLATE[91] =
    "\'^^^^^^^\"(.......)(+.....+)[.+.+.+.](vvvvvvv)(^^^^^^^)[.+.+.+.](+.....+)(.......),vvvvvvv;";
const char* const PTR_EMPTY_PLATE = EMPTY_PLATE;
static char PIECE_TABLE[91] =
    "RHMGKGMHR.........-C-----C-S.S.S.S.S---------.........s-s-s-s-s.c.....c.---------rhmgkgmhr";
const char* const PTR_PIECE_TABLE = PIECE_TABLE;

class ChessPiece;
class ChessPlate;

void GamePlay(ChessPlate* ptr_plate);
void Replay(ChessPlate* ptr_plate);

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

void ChessPiece::printDisplayName() {
    char display_shape = *(PTR_EMPTY_PLATE + 9 * this->m_pos_x + this->m_pos_y);
    switch (display_shape) {
    case '\'': cout << " ┌─";   break;
    case '\"': cout << "─┐ ";   break;
    case ',': cout << " └─";    break;
    case ';': cout << "─┘ ";    break;
    case '^': cout << "─┬─";    break;
    case 'v': cout << "─┴─";    break;
    case '(': cout << " ├─";    break;
    case ')': cout << "─┤ ";    break;
    case '[': cout << " ╞═";    break;
    case ']': cout << "═╡ ";    break;
    case '+': cout << "═╬═";    break;
    case '.': cout << "─┼─";
    }
}

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


bool King::isMoveLegal(int x, int y, int end_x, int end_y) {
    bool cond1 = false, cond2 = false;
    if (((end_x - x == 1 || end_x - x == -1) && end_y - y == 0)
            || ((end_y - y == 1 || end_y - y == -1) && end_x - x == 0)) {
        cond1 = true;
    }
    if ((this->isRed() && (3 <= end_y && end_y <= 5) && (0 <= end_x && end_x <= 2))
            || (!this->isRed() && (3 <= end_y && end_y <= 5) && (7 <= end_x && end_x <= 9))) {
        cond2 = true;
    }
    return (cond1 && cond2);
}

bool Guard::isMoveLegal(int x, int y, int end_x, int end_y) {
    bool cond1 = false, cond2 = false;
    if ((end_x - x == 1 || end_x - x == -1)
            && (end_y - y == 1 || end_y - y == -1)) {
        cond1 = true;
    }
    if ((this->isRed() && (3 <= end_y && end_y <= 5) && (0 <= end_x && end_x <= 2))
            || (!this->isRed() && (3 <= end_y && end_y <= 5) && (7 <= end_x && end_x <= 9))) {
        cond2 = true;
    }
    return (cond1 && cond2);
}

bool Minister::isMoveLegal(int x, int y, int end_x, int end_y) {
    bool cond1 = false, cond2 = false;
    if ((end_x - x == 2 || end_x - x == -2)
            && (end_y - y == 2 || end_y - y == -2)) {
        cond1 = true;
    }
    if ((this->isRed() && (0 <= end_y && end_y <= 8) && (0 <= end_x && end_x <= 4))
            || (!this->isRed() && (0 <= end_y && end_y <= 8) && (5 <= end_x && end_x <= 9))) {
        cond2 = true;
    }
    return (cond1 && cond2);
}

bool Horse::isMoveLegal(int x, int y, int end_x, int end_y) {
    if (((end_x - x == 2 || end_x - x == -2) && (end_y - y == 1 || end_y - y == -1))
            || ((end_x - x == 1 || end_x - x == -1) && (end_y - y == 2 || end_y - y == -2))) {
        return true;
    }
    return false;
}

bool Rook::isMoveLegal(int x, int y, int end_x, int end_y) {
    if ((end_x == x && end_y != y)
            || (end_x != x && end_y == y)) {
        return true;
    }
    return false;
}

bool Cannon::isMoveLegal(int x, int y, int end_x, int end_y) {
    if ((end_x == x && end_y != y)
            || (end_x != x && end_y == y)) {
        return true;
    }
    return false;
}

bool Soldier::isMoveLegal(int x, int y, int end_x, int end_y) {
    bool cond1 = false, cond2 = false;
    if (((end_x - x == 1 || end_x - x == -1) && (end_y - y == 0))
            || ((end_y - y == 1 || end_y - y == -1) && (end_x - x == 0))) {
        cond1 = true;
    }
    if ((this->isRed() && (x > 5 || end_x > x || (x = 5 && end_x >= x)))
            || (!this->isRed() && (x < 4 || end_x < x || (x = 4 && end_x <= x)))) {
        cond2 = true;
    }
    return (cond1 && cond2);
}


int Minister::getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses) {
    *ptr_poses = (end_x + x) / 2;
    *(ptr_poses + 1) = (end_y + y) / 2;
    return 1;
}

int Horse::getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses) {
    if (end_x - x == 1 || end_x - x == -1) {
        *ptr_poses = x;
        *(ptr_poses + 1) = y + ((end_y > y) ? 1 : -1);
    } else {
        *(ptr_poses + 1) = y;
        *ptr_poses = x + ((end_x > x) ? 1 : -1);
    }
    return 1;
}

int Rook::getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses) {
    int count = 0;
    if (end_x == x) {
        count = ((end_y > y) ? (end_y - y) : (y - end_y)) - 1;
        for (int i = 1; i <= count; i++) {
            *(ptr_poses + 2 * i - 2) = x;
            *(ptr_poses + 2 * i - 1) = y + ((end_y > y) ? i : -i);
        }
    } else {
        count = ((end_x > x) ? (end_x - x) : (x - end_x)) - 1;
        for (int i = 1; i <= count; i++) {
            *(ptr_poses + 2 * i - 2) = x + ((end_x > x) ? i : -i);
            *(ptr_poses + 2 * i - 1) = y;
        }
    }
    return count;
}

int Cannon::getObstaclePositions(int x, int y, int end_x, int end_y, int* ptr_poses) {
    int count = 0;
    if (end_x == x) {
        count = ((end_y > y) ? (end_y - y) : (y - end_y));
        for (int i = 1; i <= count; i++) {
            *(ptr_poses + 2 * i - 2) = x;
            *(ptr_poses + 2 * i - 1) = y + ((end_y > y) ? i : -i);
        }
    } else {
        count = ((end_x > x) ? (end_x - x) : (x - end_x));
        for (int i = 1; i <= count; i++) {
            *(ptr_poses + 2 * i - 2) = x + ((end_x > x) ? i : -i);
            *(ptr_poses + 2 * i - 1) = y;
        }
    }
    return count;
}


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
    int isGameOver(bool is_red_turn);
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

ChessPlate::ChessPlate() {
    this->m_is_last_operation_sucessful = false;
    this->m_ptr_ptr_pieces = new ChessPiece*[90];
    this->m_ptr_history = new char[4096];
    this->m_round = 0;
    ChessPiece* ptr_piece;
    char type;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            type = *(PTR_PIECE_TABLE + i * 9 + j);
            switch (type) {
            case 'R': ptr_piece = new Rook(i, j);               break;
            case 'H': ptr_piece = new Horse(i, j);              break;
            case 'M': ptr_piece = new Minister(i, j);           break;
            case 'G': ptr_piece = new Guard(i, j);              break;
            case 'K': ptr_piece = new King(i, j);               break;
            case 'C': ptr_piece = new Cannon(i, j);             break;
            case 'S': ptr_piece = new Soldier(i, j);            break;
            case 'r': ptr_piece = new Rook(i, j, false);        break;
            case 'h': ptr_piece = new Horse(i, j, false);       break;
            case 'm': ptr_piece = new Minister(i, j, false);    break;
            case 'g': ptr_piece = new Guard(i, j, false);       break;
            case 'k': ptr_piece = new King(i, j, false);        break;
            case 'c': ptr_piece = new Cannon(i, j, false);      break;
            case 's': ptr_piece = new Soldier(i, j, false);     break;
            case '.': case '-': ptr_piece = new ChessPiece(i, j);
            }
            *(this->m_ptr_ptr_pieces + i * 9 + j) = ptr_piece;
        }
    }
}

void ChessPlate::getKingPosition(int* ptr_x, int* ptr_y, bool is_red) {
    ChessPiece* ptr_piece;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            ptr_piece = *(this->m_ptr_ptr_pieces + i * 9 + j);
            if (ptr_piece->getType() == 'k' && ptr_piece->isRed() == is_red) {
                ptr_piece->getPosition(ptr_x, ptr_y);
                break;
            }
        }
    }
}

bool ChessPlate::isCheckmate() {
    bool result = false;
    ChessPiece* ptr_piece;
    int rking_x, rking_y, bking_x, bking_y;
    this->getKingPosition(&rking_x, &rking_y, true);
    this->getKingPosition(&bking_x, &bking_y, false);
    for (int i = 0; i < 10 && !result; i++) {
        for (int j = 0; j < 9; j++) {
            ptr_piece = *(this->m_ptr_ptr_pieces + i * 9 + j);
            if ((this->isOperationLegal(ptr_piece, i, j, rking_x, rking_y))
                    || (this->isOperationLegal(ptr_piece, i, j, bking_x, bking_y))) {
                result = true;
                break;
            }
        }
    }
    cout << (result ? "將軍！\n" : "");
    return result;
}

int ChessPlate::isGameOver(bool is_red_turn) {
    bool is_red_king = false;
    bool is_black_king = false;
    bool is_king_kill_king = false;
    int rking_x, bking_x, rking_y, bking_y;
    ChessPiece* ptr_piece;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9 && !(is_red_king && is_black_king); j++) {
            ptr_piece = *(this->m_ptr_ptr_pieces + i * 9 + j);
            if (ptr_piece->getType() == 'k' && ptr_piece->isRed()) {
                is_red_king = true;
                ptr_piece->getPosition(&rking_x, &rking_y);
            } else if (ptr_piece->getType() == 'k' && !ptr_piece->isRed()) {
                is_black_king = true;
                ptr_piece->getPosition(&bking_x, &bking_y);
            }
        }
    }
    if (is_red_king && is_black_king && rking_y == bking_y) {
        is_king_kill_king = true;
        for (int i = rking_x + 1; i < bking_x; i++) {
            ptr_piece = *(this->m_ptr_ptr_pieces + i * 9 + rking_y);
            if (!ptr_piece->isVoid()) {
                is_king_kill_king = false;
            }
        }
    }

    if (!is_black_king || (is_king_kill_king && is_red_turn)) {
        return 1;
    } else if (!is_red_king || (is_king_kill_king && !is_red_turn)) {
        return 2;
    }
    return 0;
}

void ChessPlate::printLine(int line) {
    int position = line * 9;
    ChessPiece* ptr_piece;
    for (int i = 1; i <= 9; i++) {
        ptr_piece = *(this->m_ptr_ptr_pieces + position++);
        ptr_piece->printDisplayName();
        cout << (i != 9 ? "──" : "");
    }
    cout << " ┃" << endl;
}

void ChessPlate::printBackGroundLine(int line) {
    switch (line) {
    case -1: cout << "      1    2    3    4    5    6    7    8    9" << endl;
        cout << "   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n A ┃ ";
        break;
    case 0: cout << "   ┃  │    │    │    │ ＼ │ ／ │    │    │    │  ┃\n B ┃ "; break;
    case 1: cout << "   ┃  │    │    │    │ ／ │ ＼ │    │    │    │  ┃\n C ┃ "; break;
    case 2: cout << "   ┃  │    │    │    │    │    │    │    │    │  ┃\n D ┃ "; break;
    case 3: cout << "   ┃  │    │    │    │    │    │    │    │    │  ┃\n E ┃ "; break;
    case 4: cout << "   ┃  │     楚     河           漢     界     │  ┃\n F ┃ "; break;
    case 5: cout << "   ┃  │    │    │    │    │    │    │    │    │  ┃\n G ┃ "; break;
    case 6: cout << "   ┃  │    │    │    │    │    │    │    │    │  ┃\n H ┃ "; break;
    case 7: cout << "   ┃  │    │    │    │ ＼ │ ／ │    │    │    │  ┃\n I ┃ "; break;
    case 8: cout << "   ┃  │    │    │    │ ／ │ ＼ │    │    │    │  ┃\n J ┃ "; break;
    case 9: cout <<
                     "   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    }
}

bool ChessPlate::isOperationLegal(ChessPiece* ptr_piece, int x, int y, int end_x, int end_y) {
    ChessPiece* ptr_end_piece;
    ptr_end_piece = *(this->m_ptr_ptr_pieces + end_x * 9 + end_y);
    bool cond1, cond2, cond3 = true;
    cond1 = ptr_piece->isMoveLegal(x, y, end_x, end_y);
    cond2 = (ptr_end_piece->isVoid() || ptr_end_piece->isRed() != ptr_piece->isRed());
    if (cond1 && cond2) {
        int* ptr_obstacle_positions = new int[16];
        int obst_x, obst_y, max_obstacle_count, real_obstacle_count = 0;
        ChessPiece* ptr_obst;
        max_obstacle_count =
            ptr_piece->getObstaclePositions(x, y, end_x, end_y, ptr_obstacle_positions);
        for (int i = 1; i <= max_obstacle_count; i++) {
            obst_x = *(ptr_obstacle_positions + i * 2 - 2);
            obst_y = *(ptr_obstacle_positions + i * 2 - 1);
            ptr_obst = *(this->m_ptr_ptr_pieces + obst_x * 9 + obst_y);
            real_obstacle_count += (ptr_obst->isVoid() ? 0 : 1);
        }
        if (ptr_piece->getType() == 'c' && !ptr_end_piece->isVoid()
                && (ptr_end_piece->isRed() != ptr_piece->isRed())) {
            cond3 = !(real_obstacle_count == 1 || real_obstacle_count >= 3);
        } else {
            cond3 = !(real_obstacle_count >= 1);
        }
        delete [] ptr_obstacle_positions;
    }
    return (cond1 && cond2 && cond3);
}

void ChessPlate::pieceMove(int x, int y, int end_x, int end_y) {
    ChessPiece* ptr_piece;
    ChessPiece* ptr_end_piece;
    ptr_piece = *(this->m_ptr_ptr_pieces + x * 9 + y);
    ptr_end_piece = *(this->m_ptr_ptr_pieces + end_x * 9 + end_y);
    if (this->isOperationLegal(ptr_piece, x, y, end_x, end_y)) {
        if (ptr_end_piece->isVoid()) {
            ptr_piece->printDisplayName();
            cout << " 移動。" << endl;
        } else if (ptr_piece->isRed() != ptr_end_piece->isRed()) {
            ptr_piece->printDisplayName();
            cout << " 吃掉了 ";
            ptr_end_piece->printDisplayName();
            cout << "。" << endl;
        }
        delete ptr_end_piece;
        ptr_piece->setPosition(end_x, end_y);
        *(this->m_ptr_ptr_pieces + end_x * 9 + end_y) = ptr_piece;
        *(this->m_ptr_ptr_pieces + x * 9 + y) = new ChessPiece(x, y);
        this->setIsLastOperationSucessful(true);

    } else {
        ptr_piece->printDisplayName();
        cout << ": 無法移動。" << endl;
    }
}

void ChessPlate::actionOperate(char* ptr_command, bool is_red) {
    int x = 0, y = 0, end_x = 0, end_y = 0;
    if (('A' <= *ptr_command && *ptr_command <= 'J')
            && ('1' <= *(ptr_command + 1) && *(ptr_command + 1) <= '9')
            && ('A' <= *(ptr_command + 2) && *(ptr_command + 2) <= 'J')
            && ('1' <= *(ptr_command + 3) && *(ptr_command + 3) <= '9')
            && (*(ptr_command + 4) == '\n')) {
        x = *ptr_command - 'A';
        y = *(ptr_command + 1) - '1';
        end_x = *(ptr_command + 2) - 'A';
        end_y = *(ptr_command + 3) - '1';
        ChessPiece* ptr_piece;
        ptr_piece = *(this->m_ptr_ptr_pieces + x * 9 + y);
        if (ptr_piece->isVoid()) {
            cout << "這裡沒有棋子。" << endl;
        } else if (ptr_piece->isRed() != is_red) {
            cout << "你只能動自己的棋子。" << endl;
        } else {
            this->pieceMove(x, y, end_x, end_y);
        }
    } else {
        cout << "無效的指令。" << endl;
    }
}


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
    while (!ptr_plate->isGameOver(is_red_turn)) {
        ptr_plate->isCheckmate();
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
    if (ptr_plate->isGameOver(is_red_turn) == 1) {
        cout << "紅方勝。" << endl;
    } else if (ptr_plate->isGameOver(is_red_turn) == 2) {
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