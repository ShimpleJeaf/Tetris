#ifndef TETRISGRID_H
#define TETRISGRID_H

#include <vector>
#include "bulk.h"

class TetrisGrid
{
    static const size_t width = 12;
    static const size_t height = 24;
    std::vector<std::vector<bool>> m_grid;
public:
    TetrisGrid();

    // 往下移一格后是否碰撞
    bool isDownBlock(Bulk bulk);
    bool isLeftBlock(Bulk bulk);
    bool isRightBlock(Bulk bulk);
    bool isBlock(Bulk bulk);

    bool isDot(size_t row, size_t col);

    bool add(Bulk bulk);

    int down();

    static size_t rowCount() { return height; }
    static size_t colCount() { return width; }
private:
    void dropRow(int row);
};

#endif // TETRISGRID_H
