#ifndef BULK_H
#define BULK_H

#include <vector>

/// L
//  X            XX                           X              XX
//  X    XXX      X        X                  X      X       X       XXX
//  XX   X        X      XXX                 XX      XXX     X         X

/// Z
//   X         X
//  XX  XX     XX    XX
//  X    XX     X   XX

/// T
//          X                X
//   X      XX     XXX      XX
//  XXX     X       X        X

/// I
//  X
//  X
//  X
//  X       XXXX

/// O
//
//  XX
//  XX

typedef std::vector<std::vector<bool> > BulkPoint;

enum ShapeType {
    L_Type = 0,
    T_Type = 1,
    Z_Type = 2,
    I_Type = 3,
    O_Type = 4
};

class BulkType
{
    ShapeType m_shape;
    unsigned m_form;

public:
    BulkType(ShapeType type, unsigned form);
    ShapeType shape() { return m_shape; }
    unsigned form() { return m_form; }

    // 变形
    void transform();
    void changeShape();

    static BulkType randomType();
};

class Bulk
{
    int m_row;
    int m_col;
    BulkType m_type;
    static size_t m_rowCount;
    static size_t m_colCount;

public:
    Bulk(BulkType type, int row, int col) : m_row(row), m_col(col), m_type(type) {}

    int row() { return m_row; }
    int col() { return m_col; }
    BulkType type() { return m_type; }
    void transform();
    void changeShape();
    void down()
    {
            m_row++;
    }
    void left()
    {
            m_col--;
    }
    void right()
    {
            m_col++;
    }
    const BulkPoint& bulkPoint()
    {
        return bulkPoint(m_type);
    }
    static const BulkPoint& bulkPoint(BulkType type)
    {
        return bulkPoint(type.shape(), type.form());
    }

    static const BulkPoint& bulkPoint(ShapeType shape, unsigned form);

    static void setRowCount(size_t rowCount) { m_rowCount = rowCount; }
    static void setColCount(size_t colCount) { m_colCount = colCount; }
};

#endif // BULK_H
