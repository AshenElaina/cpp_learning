#include "chinese_chess__chess_plate.h"

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
    return result;
}

int ChessPlate::getStatus(bool is_red_turn) {
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