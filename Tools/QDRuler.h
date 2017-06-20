#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

#define  RULER_BREADTH 10

class QDRuler : public QWidget
{
	Q_OBJECT
		Q_ENUMS(RulerType)
		Q_PROPERTY(qreal origin READ origin WRITE setOrigin)
		Q_PROPERTY(qreal rulerUnit READ rulerUnit WRITE setRulerUnit)
		Q_PROPERTY(qreal rulerZoom READ rulerZoom WRITE setRulerZoom)
public:
	enum RulerType { Horizontal, Vertical };
	QDRuler(QDRuler::RulerType rulerType, QWidget* parent)
		: QWidget(parent), mRulerType(rulerType), mOrigin(0.), mRulerUnit(1.),
		mRulerZoom(1.), mMouseTracking(false), mDrawText(false)
	{
		setMouseTracking(true);
		QFont txtFont("Goudy Old Style", 5, 20);
		txtFont.setStyleHint(QFont::TypeWriter, QFont::PreferOutline);
		setFont(txtFont);
	}
	
	QSize minimumSizeHint() const
	{
		return QSize(RULER_BREADTH, RULER_BREADTH);
	}

	QDRuler::RulerType rulerType() const
	{
		return mRulerType;
	}

	qreal origin() const
	{
		return mOrigin;
	}

	qreal rulerUnit() const
	{
		return mRulerUnit;
	}

	qreal rulerZoom() const
	{
		return mRulerZoom;
	}

	public slots:

	void setOrigin(const qreal origin)
	{
		if (mOrigin != origin)
		{
			mOrigin = origin;
			update();
		}
	}

	void setRulerUnit(const qreal rulerUnit)
	{
		if (mRulerUnit != rulerUnit)
		{
			mRulerUnit = rulerUnit;
			update();
		}
	}

	void setRulerZoom(const qreal rulerZoom)
	{
		if (mRulerZoom != rulerZoom)
		{
			mRulerZoom = rulerZoom;
			update();
		}
	}


	void setCursorPos(const QPoint cursorPos)
	{
		mCursorPos = this->mapFromGlobal(cursorPos);
		mCursorPos += QPoint(RULER_BREADTH, RULER_BREADTH);
		update();
	}

	void setMouseTrack(const bool track)
	{
		if (mMouseTracking != track)
		{
			mMouseTracking = track;
			update();
		}
	}

protected:
	void mouseMoveEvent(QMouseEvent* event);

	void paintEvent(QPaintEvent* event);

private:
	void drawAScaleMeter(QPainter* painter, QRectF rulerRect, qreal scaleMeter, qreal startPositoin);

	void drawFromOriginTo(QPainter* painter, QRectF rulerRect, qreal startMark, qreal endMark, int startTickNo, qreal step, qreal startPosition);

	void drawMousePosTick(QPainter* painter);

private:
	RulerType mRulerType;
	qreal mOrigin;
	qreal mRulerUnit;
	qreal mRulerZoom;
	QPoint mCursorPos;
	bool mMouseTracking;
	bool mDrawText;
};
