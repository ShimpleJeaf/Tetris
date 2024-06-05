#include "tetris.h"
#include "graphicssquareitem.h"
#include "headfile.h"

Tetris::Tetris() :
    m_bulk(BulkType::randomType(), -1, 5),
    m_nextBulk(BulkType::randomType(), -1, 5),
    m_score(0),
    m_level(0)
{
    m_nextBulk.changeShape();
    setScene(&m_scene);
    // 网格虚线
    QPen p;
    p.setColor(Qt::gray);
    p.setStyle(Qt::PenStyle::DotLine);
    for (size_t i = 0; i < TetrisGrid::rowCount(); i++) {
        for (size_t j = 0; j < TetrisGrid::colCount(); j++) {
            GraphicsSquareItem* item = new GraphicsSquareItem(m_squareSize);
            item->setX(j * m_squareSize);
            item->setY(i * m_squareSize);
            item->setPen(p);
            item->show();
            m_scene.addItem(item);
        }
    }
    // 棋盘格
    std::vector<GraphicsSquareItem*> tmpColItem;
    tmpColItem.resize(TetrisGrid::colCount(), nullptr);
    m_items.resize(TetrisGrid::rowCount(), tmpColItem);
    for (size_t i = 0; i < TetrisGrid::rowCount(); i++) {
        for (size_t j = 0; j < TetrisGrid::colCount(); j++) {
            GraphicsSquareItem* item = new GraphicsSquareItem(m_squareSize);
            item->setX(j * m_squareSize);
            item->setY(i * m_squareSize);
            item->setPen(QPen(Qt::black));
            item->setBrush(QBrush(Qt::yellow));
            item->hide();
            m_scene.addItem(item);
            m_items[i][j] = item;
        }
    }
    // 外框
    m_scene.addItem(new QGraphicsRectItem(0, 0, TetrisGrid::colCount()*m_squareSize, TetrisGrid::rowCount()*m_squareSize));
    // 分数
    m_scoreItem = new QGraphicsTextItem(QString::number(m_score));
    m_scoreItem->setPos((TetrisGrid::colCount()+1)*m_squareSize, 0);
    QFont font = m_scoreItem->font();
    font.setPixelSize(m_squareSize);
    font.setBold(true);
    m_scoreItem->setFont(font);
    m_scene.addItem(m_scoreItem);
    // 下一个方块
    tmpColItem.resize(4, nullptr);
    m_nextItems.resize(4, tmpColItem);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            GraphicsSquareItem* item = new GraphicsSquareItem(m_squareSize);
            item->setX((TetrisGrid::colCount()+1)*m_squareSize + j * m_squareSize);
            item->setY((i+2) * m_squareSize);
            item->setPen(QPen(Qt::black));
            item->setBrush(QBrush(Qt::yellow));
            item->hide();
            m_scene.addItem(item);
            m_nextItems[i][j] = item;
        }
    }
    m_timerId = startTimer(1000);
}

void Tetris::timerEvent(QTimerEvent *event)
{
    if (m_grid.isDownBlock(m_bulk)) {
        if (!m_grid.add(m_bulk)) {
            QMessageBox::information(this, "提示", "结束");
        }
        else {
            // 计分
            int disrow = 0;
            disrow += m_grid.down();
            m_score += 10*disrow*disrow;
            m_bulk = m_nextBulk;
            m_nextBulk = Bulk(BulkType::randomType(), -1, 5);

            if (m_score > 100 * (m_level + 1)) {
                m_level++;
                int timerInterval = 1000 - m_level * 100;
                killTimer(m_timerId);
                m_timerId = startTimer(timerInterval);
            }
        }
    }
    else {
        m_bulk.down();
    }
    draw();
}

void Tetris::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    {
        if (!m_grid.isLeftBlock(m_bulk))
            m_bulk.left();
        break;
    }
    case Qt::Key_Right:
    {
        if (!m_grid.isRightBlock(m_bulk))
            m_bulk.right();
        break;
    }
    case Qt::Key_Down:
    {
        if (!m_grid.isDownBlock(m_bulk))
            m_bulk.down();
        else {
            if (!m_grid.add(m_bulk)) {
                QMessageBox::information(this, "提示", "结束");
            }
            else {
                // 计分
                int disrow = 0;
                disrow += m_grid.down();
                m_score += 10*disrow*disrow;
                m_bulk = m_nextBulk;
                m_nextBulk = Bulk(BulkType::randomType(), -1, 5);

                if (m_score > 100 * (m_level + 1)) {
                    m_level++;
                    int timerInterval = 1000 - m_level * 100;
                    killTimer(m_timerId);
                    m_timerId = startTimer(timerInterval);
                }
            }
        }
        break;
    }
    case Qt::Key_Space:
    {
        m_bulk.transform();
        if (m_bulk.col() > m_grid.colCount()/2) {
            while (m_grid.isBlock(m_bulk))
                m_bulk.left();
        }
        else {
            while (m_grid.isBlock(m_bulk)) {
                m_bulk.right();
            }
        }
    }
    default:
        break;
    }
    draw();
}

void Tetris::draw()
{
    // 画堆叠好的
    for (size_t row = 0; row < TetrisGrid::rowCount(); row++) {
        for (size_t col = 0; col < m_grid.colCount(); col++) {

            if (m_grid.isDot(row, col)) {
                m_items[row][col]->setBrush(QBrush(Qt::gray));
                m_items[row][col]->show();
            }
            else
                m_items[row][col]->hide();
        }
    }
    // 画下落的
    const BulkPoint& bulkPoint = Bulk::bulkPoint(m_bulk.type());
    for (int i = 0; i < 4; i++) {
        int row = m_bulk.row() - 3 + i;
        if (row < 0)
            continue;
        for (int j = 0; j < 4; j++) {
            int col = m_bulk.col();
            if (bulkPoint[i][j]) {
                m_items[row][col + j]->setBrush(QBrush(Qt::yellow));
                m_items[row][col + j]->show();
            }
        }
    }
    // 画下一个方块
    const BulkPoint& nextBulkPoint = Bulk::bulkPoint(m_nextBulk.type());
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (nextBulkPoint[i][j])
                m_nextItems[i][j]->show();
            else
                m_nextItems[i][j]->hide();
        }
    }
    // 分数
    m_scoreItem->setPlainText(QString::number(m_score));
}

