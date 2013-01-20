#include <QtWidgets>
#include "BoxWidget.h"


BoxWidget::BoxWidget( QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	background = QBrush(Qt::red);
	hipPen = QPen(Qt::green);
	currentPen = QPen(Qt::yellow);
	darkPen = QPen(Qt::black);
	curFontSize = MAX_FONT;
	elapsed = 0;
    currentMode = HIP;
    setFixedSize(200, 200);
}

void BoxWidget::paint(QPainter *painter, QPaintEvent *event)
{
	painter->fillRect(event->rect(), background);
    QString text;
    QPen pen;
    painter->save();
	switch(currentMode){
		case HIP:
            pen = hipPen;
			text = "So Hip!";
			break;
		case CURRENT:
            pen = currentPen;
			text = "So Current!";
			break;
		case DARK:
            pen = darkPen;
			text = "So Dark!";
			break;
	}
    textFont.setPixelSize(MAX_FONT - elapsed);
    painter->restore();
    painter->setPen(pen);
	painter->setFont(textFont);
    painter->drawText(QRect(0, 0, 200, 200), Qt::AlignCenter, text);

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
    if(elapsed == 0){
        switchMode();
    }
	repaint();
}

void BoxWidget::switchMode(){
    switch(currentMode){
    case HIP:
        currentMode = CURRENT;
        break;
    case CURRENT:
        currentMode = DARK;
        break;
    case DARK:
        currentMode = HIP;
        break;
    }
}
