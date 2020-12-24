#ifndef CHINESE_CHESS__INIT_H_
#define CHINESE_CHESS__INIT_H_

static char EMPTY_PLATE[91] =
    "\'^^^^^^^\"(.......)(+.....+)[.+.+.+.](vvvvvvv)(^^^^^^^)[.+.+.+.](+.....+)(.......),vvvvvvv;";
const char* const PTR_EMPTY_PLATE = EMPTY_PLATE;
static char PIECE_TABLE[91] =
    "RHMGKGMHR.........-C-----C-S.S.S.S.S---------.........s-s-s-s-s.c.....c.---------rhmgkgmhr";
const char* const PTR_PIECE_TABLE = PIECE_TABLE;

#endif