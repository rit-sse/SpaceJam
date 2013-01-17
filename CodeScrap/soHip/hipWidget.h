#ifndef HIP_WIDGET_H
#define HIP_WIDGET_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QGLWidget>


QT_BEGIN_NAMESPACE
class QPainter;
class QPaintEvent;
class QWidget;
QT_END_NAMESPACE

class HipWidget : QGLWidget
{
	Q_OBJECT
public: 
	HipWidget( QWidget *parent);
    void paint(QPainter *painter, QPaintEvent *event);

protected:
	void paintEvent(QPaintEvent *event);

private: 
	QBrush background;
	QFont textFont;
	QPen hipPen;
	QPen darkPen;
	QPen currentPen;
	int elapsed;
};

#endif
