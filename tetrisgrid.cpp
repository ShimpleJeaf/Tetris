#include "tetrisgrid.h"


TetrisGrid::TetrisGrid()
{
    for (size_t i = 0; i < height; i++) {
        m_grid.push_back(std::vector<bool>(width, false));
    }
    Bulk::setRowCount(height);
    Bulk::setColCount(width);
}

bool TetrisGrid::isDownBlock(Bulk bulk)
{
    Bulk tmpbulk = bulk;
    tmpbulk.down();
    return isBlock(tmpbulk);
}

bool TetrisGrid::isLeftBlock(Bulk bulk)
{
    Bulk tmpbulk = bulk;
    tmpbulk.left();
    return isBlock(tmpbulk);
}

bool TetrisGrid::isRightBlock(Bulk bulk)
{
    Bulk tmpbulk = bulk;
    tmpbulk.right();
    return isBlock(tmpbulk);
}

bool TetrisGrid::isBlock(Bulk bulk)
{
    int row = bulk.row(), col = bulk.col();
    const BulkPoint& bulkPoint = bulk.bulkPoint();
    for (int i = 0; i < 4; i++) {
        int rowtmp = row - 3 + i;
        if (rowtmp < 0)
            continue;
        for (int j = 0; j < 4; j++) {
            int coltmp = col + j;
            // ±ß½ç
            if ((rowtmp >= rowCount() || coltmp < 0 || coltmp >= colCount())
                && bulkPoint[i][j])
                return true;
            if (rowtmp >= 0 && rowtmp < rowCount()
                && coltmp >= 0 && coltmp < colCount()
                && m_grid[rowtmp][coltmp] && bulkPoint[i][j])
                return true;
        }
    }
    return false;
}

void TetrisGrid::dropRow(int row)
{
    for (int i = row; i > 0; i--) {
        for (int j = 0; j < colCount(); j++) {
            m_grid[i][j] = m_grid[i-1][j];
        }
    }
    for (int j = 0; j < colCount(); j++) {
        m_grid[0][j] = false;
    }
}

bool TetrisGrid::isDot(size_t row, size_t col)
{
    return m_grid[row][col];
}

bool TetrisGrid::add(Bulk bulk)
{
    const BulkPoint& bulkPoint = Bulk::bulkPoint(bulk.type());
    size_t row = bulk.row(), col = bulk.col();
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (bulkPoint[i][j]) {
                if (row-3+i < 0 || row-3+i >= rowCount()
                    || col+j < 0 || col+j >= colCount())
                    return false;
                m_grid[row-3+i][col+j] = true;
            }
        }
    }
    return true;
}

int TetrisGrid::down()
{
    int rowC = 0;
    for (int row = 0; row < rowCount(); row++) {
        bool bDrop = true;
        for (int col = 0; col < colCount(); col++) {
            if (!m_grid[row][col]) {
                bDrop = false;
                break;
            }
        }
        if (bDrop) {
            dropRow(row);
            rowC++;
        }
    }
    return rowC;
}
