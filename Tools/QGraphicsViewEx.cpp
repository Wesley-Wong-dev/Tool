#include "QGraphicsViewEx.h"
#include <QGridLayout>

QGraphicsViewEx::QGraphicsViewEx(QWidget* lparent/*=0*/):QGraphicsView(lparent)
{
	setViewportMargins(RULER_BREADTH, RULER_BREADTH, 0, 0);

	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->setSpacing(0);
	gridLayout->setMargin(0);

	m_lpHorzRuler = new QDRuler(QDRuler::Horizontal, this);
	m_lpVertRuler = new QDRuler(QDRuler::Vertical, this);

	QWidget* fake = new QWidget();
	fake->setBackgroundRole(QPalette::Window);
	fake->setFixedSize(RULER_BREADTH, RULER_BREADTH);
	gridLayout->addWidget(fake, 0, 0);
	gridLayout->addWidget(m_lpHorzRuler, 0, 1);
	gridLayout->addWidget(m_lpVertRuler, 1, 0);
	gridLayout->addWidget(this->viewport(), 1, 1);

	this->setLayout(gridLayout);
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
