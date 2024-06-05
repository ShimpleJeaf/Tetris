#include "mainwindow.h"
#include "headfile.h"
#include "graphicssquareitem.h"
#include "tetris.h"

class Column
{
    std::vector<bool> m_data;
    size_t m_frontIndex;
    size_t m_backIndex;
    size_t m_size;
    bool m_isFull;

public:
    Column(size_t size) :
        m_frontIndex(0),
        m_backIndex(0),
        m_size(size)
    {
        m_data.resize(size, false);
    }

    ~Column()
    {
    }

    void pop()
    {
        if (m_frontIndex == m_backIndex)
            return;
        m_data[m_frontIndex] = false;
        m_frontIndex = ++m_frontIndex % m_size;
        m_isFull = false;
    }

    bool push(bool data)
    {
        if (m_isFull)
            return false;
        m_data[m_backIndex] = data;
        m_backIndex = ++m_backIndex % m_size;
        if (m_backIndex == m_frontIndex)
            m_isFull = true;
        return true;
    }

    bool front()
    {
        return m_data[m_frontIndex];
    }

    bool operator[](size_t index)
    {
        return m_data[(m_frontIndex + index) % m_size];
    }
};

#define ASSERT(expresion, value, describe) \
        { \
            if (expresion == value) \
                std::cout << describe << " succeed" << std::endl; \
            else { \
                std::cout << describe << " [[failed]]" << std::endl; \
                return false; \
            } \
        }

class TestColumn
{
public:
    static bool test()
    {
        Column col(5);
        col.push(true);
        col.push(false);
        col.push(true);
        if (col.front() != true)
            return false;
        col.pop();
        if (col.front() != false)
            return false;
        col.pop();
        if (col.front() != true)
            return false;
        col.pop();

        ASSERT(col.push(true), true, "push")
        ASSERT(col.push(true), true, "push")
        ASSERT(col.push(true), true, "push")
        ASSERT(col.push(true), true, "push")
        ASSERT(col.push(true), true, "push")
        ASSERT(col.push(true), false, "push")
        return true;
    }
};

int main(int argc, char *argv[])
{
    if (TestColumn::test())
        std::cout << "TestColumn succeed" << std::endl;
    else
        std::cout << "TestColumn failed" << std::endl;

    QApplication a(argc, argv);

    Tetris tetri;
    tetri.show();
    return a.exec();

    std::map<int, int> k;
    decltype (k)::key_type c;
    c = 3;
}
