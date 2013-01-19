#include <QtWidgets>
#include "hipWidget.h"


HipWidget::HipWidget( QWidget *parent)
{
	background = QBrush(Qt::red);
	hipPen = QPen(Qt::green);
	currentPen = QPen(Qt::yellow);
	darkPen = QPen(Qt::black);
	curFontSize = MAX_FONT;
	elapsed = 0;
    currentMode = HIP;
}

void HipWidget::paint(QPainter *painter, QPaintEvent *event)
{
	painter->fillRect(event->rect(), background);
	painter->save();
	switch(currentMode){
		case HIP:
			painter->setPen(hipPen);
			text = "So Hip!";
			break;
		case CURRENT:
			painter->setPen(currentPen);
			text = "So Current!";
			break;
		case DARK:
			painter->setPen(darkPen);
			text = "So Dark!";
			break;
	}
    textFont.setPixelSize(MAX_FONT - elapsed*2.5);
    painter->restore();
	painter->setFont(textFont);
	painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, text);

}

void HipWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	paint(&painter, event);
	painter.end();
}

void HipWidget::animate()
{
	elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 50;
	repaint();
}
