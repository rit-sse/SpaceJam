#include <QtWidgets>
#include "BoxWidget.h"


BoxWidget::BoxWidget( QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	background = QBrush(Qt::blue);
	hipPen = QPen(Qt::white);
	elapsed = 0;
    setFixedSize(200, 200);
}

void BoxWidget::paint(QPainter *painter, QPaintEvent *event)
{
	painter->fillRect(event->rect(), background);
    QPen pen;
    painter->save();
	painter->restore();
    painter->setPen(pen);
	painter->drawRoundedRect(QRect(50, 50, 100, 100), 0, 0);

}

void BoxWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	paint(&painter, event);
	painter.end();
}

void BoxWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 50;
    repaint();
}

void BoxWidget::switchMode(){
}
