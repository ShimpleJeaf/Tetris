#ifndef TETRIS_H
#define TETRIS_H

#include "bulk.h"
#include "tetrisgrid.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

class GraphicsSquareItem;
class Tetris : public QGraphicsView
{
    Q_OBJECT
    TetrisGrid m_grid;
    Bulk m_bulk;
    Bulk m_nextBulk;
    QGraphicsScene m_scene;
    std::vector<std::vector<GraphicsSquareItem*> > m_items;
    std::vector<std::vector<GraphicsSquareItem*> > m_nextItems;
    int m_score;
    QGraphicsTextItem* m_scoreItem;
    const unsigned m_squareSize = 15;
    int m_timerId;
    int m_level;

public:
    Tetris();

protected:
    virtual void timerEvent(QTimerEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    void draw();
};

#endif // TETRIS_H
