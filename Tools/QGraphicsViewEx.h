#pragma once
#include <QGraphicsView>
#include <QPainter>

class QGraphicsViewEx : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QGraphicsViewEx(QWidget* lparent=0);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);
    virtual void drawItems(QPainter *painter, int numItems,
        QGraphicsItem *items[],
        const QStyleOptionGraphicsItem options[]);
    void resizeEvent(QResizeEvent *);
private:
    QColor m_theBackLienColor;
    QColor m_thePointColor;
    QColor m_theBackColor;
};

