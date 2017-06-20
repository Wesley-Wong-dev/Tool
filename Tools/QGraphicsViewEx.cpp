#include "QGraphicsViewEx.h"


QGraphicsViewEx::QGraphicsViewEx(QWidget* lparent/*=0*/):QGraphicsView(lparent)
{

}

void QGraphicsViewEx::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen thePen(Qt::darkYellow, 0);
    thePen.setStyle(Qt::DotLine);
    painter->setPen(thePen);
    
    
    for (int i = 1; i < this->width(); i++)
    {
        painter->drawLine(0, i, this->width(), i);
    }
    
    for (int i = 1; i < this->width(); i++)
    {
        painter->drawLine(i, 0, i, this->width());
    }
    
}

void QGraphicsViewEx::drawForeground(QPainter *painter, const QRectF &rect)
{

}

void QGraphicsViewEx::drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[])
{

}

void QGraphicsViewEx::resizeEvent(QResizeEvent *)
{
    
}
