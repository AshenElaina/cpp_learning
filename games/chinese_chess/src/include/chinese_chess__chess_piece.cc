#include "chinese_chess__chess_piece.h"

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