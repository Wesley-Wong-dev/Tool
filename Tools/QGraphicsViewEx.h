#pragma once
#include <QGraphicsView>
#include <QPainter>
#include "QDRuler.h"

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
	//void setViewportMargins(int left, int top, int right, int bottom);
private:
	QDRuler* m_lpHorzRuler;
	QDRuler* m_lpVertRuler;
};

