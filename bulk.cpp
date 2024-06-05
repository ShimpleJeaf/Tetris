#include "bulk.h"
#include "headfile.h"

const BulkPoint L0 {{ 0, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 1, 0, 0} };

const BulkPoint L1 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 1, 1, 0},
                   { 1, 0, 0, 0} };

const BulkPoint L2 {{ 0, 0, 0, 0},
                   { 1, 1, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 0, 0} };

const BulkPoint L3 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 0, 1, 0},
                   { 1, 1, 1, 0} };

const BulkPoint L4 {{ 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 0, 1, 0, 0},
                   { 1, 1, 0, 0} };

const BulkPoint L5 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 1, 1, 0} };

const BulkPoint L6 {{ 0, 0, 0, 0},
                   { 1, 1, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 0, 0, 0} };

const BulkPoint L7 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 1, 1, 0},
                   { 0, 0, 1, 0} };

const BulkPoint Z0 {{ 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 1, 1, 0, 0},
                   { 1, 0, 0, 0} };

const BulkPoint Z1 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 1, 0, 0},
                   { 0, 1, 1, 0} };

const BulkPoint Z2 {{ 0, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 1, 0, 0},
                   { 0, 1, 0, 0} };

const BulkPoint Z3 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 1, 1, 0},
                   { 1, 1, 0, 0} };

const BulkPoint T0 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 1, 1, 1, 0} };

const BulkPoint T1 {{ 0, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 1, 0, 0},
                   { 1, 0, 0, 0} };

const BulkPoint T2 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 1, 1, 0},
                   { 0, 1, 0, 0} };

const BulkPoint T3 {{ 0, 0, 0, 0},
                   { 0, 1, 0, 0},
                   { 1, 1, 0, 0},
                   { 0, 1, 0, 0} };

const BulkPoint I0 {{ 1, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 0, 0, 0},
                   { 1, 0, 0, 0} };

const BulkPoint I1 {{ 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 0, 0, 0, 0},
                   { 1, 1, 1, 1} };

const BulkPoint O {{ 0, 0, 0, 0},
                  { 0, 0, 0, 0},
                  { 1, 1, 0, 0},
                  { 1, 1, 0, 0} };


BulkType::BulkType(ShapeType type, unsigned form) : m_shape(type)
{
    switch (m_shape) {
    case L_Type:
        m_form = form % 8;
        break;
    case T_Type:
    case Z_Type:
        m_form = form % 4;
        break;
    case I_Type:
        m_form = form % 2;
        break;
    case O_Type:
        m_form = 0;
        break;
    }
}

void BulkType::transform()
{
    switch (m_shape) {
    case L_Type:
        if (m_form < 4)
            m_form = ++m_form % 4;
        else
            m_form = 4 + (++m_form % 4);
        break;
    case T_Type:
        m_form = ++m_form % 4;
        break;
    case Z_Type:
        if (m_form < 2)
            m_form = ++m_form % 2;
        else
            m_form = 2 + (++m_form % 2);
        break;
    case I_Type:
        m_form = ++m_form % 2;
        break;
    case O_Type:
        break;
    }
}

void BulkType::changeShape()
{
    m_shape = ShapeType((int(m_shape) + 1)%5);
}

BulkType BulkType::randomType()
{
    std::srand(std::time(NULL));
    ShapeType shape = ShapeType(rand() % 5);
    std::srand(std::time(NULL)/2);
    unsigned formf = rand() % 2;
    unsigned form = 0;
    switch (shape) {
    case L_Type:
        form = formf * 4;
        break;
    case T_Type:
        break;
    case Z_Type:
        form = formf * 2;
        break;
    case I_Type:
        break;
    case O_Type:
        break;
    }
    return BulkType(ShapeType(rand() % 5), form);
}

size_t Bulk::m_rowCount(0);
size_t Bulk::m_colCount(0);

void Bulk::transform()
{
    m_type.transform();
}

void Bulk::changeShape()
{
    m_type.changeShape();
}

const BulkPoint &Bulk::bulkPoint(ShapeType shape, unsigned form)
{
    switch (shape) {
    case L_Type:
    {
        switch (form) {
        case 0:
            return L0;
        case 1:
            return L1;
        case 2:
            return L2;
        case 3:
            return L3;
        case 4:
            return L4;
        case 5:
            return L5;
        case 6:
            return L6;
        case 7:
        default:
            return L7;
        }
    }
    case T_Type:
    {
        switch (form) {
        case 0:
            return T0;
        case 1:
            return T1;
        case 2:
            return T2;
        case 3:
        default:
            return T3;
        }
    }
    case Z_Type:
    {
        switch (form) {
        case 0:
            return Z0;
        case 1:
            return Z1;
        case 2:
            return Z2;
        case 3:
        default:
            return Z3;
        }
    }
    case I_Type:
    {
        switch (form) {
        case 0:
            return I0;
        case 1:
        default:
            return I1;
        }
    }
    case O_Type:
        return O;
    }
}
