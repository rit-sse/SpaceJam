#include <QtWidgets>
#include "hipWidget.h"


HipWidget::HipWidget( QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    background = QBrush(Qt::blue);
	hipPen = QPen(Qt::green);
	currentPen = QPen(Qt::yellow);
    aphoticPen = QPen(Qt::white);
	curFontSize = MAX_FONT;
	elapsed = 0;
    currentMode = HIP;
    setFixedSize(200, 200);
}

void HipWidget::paint(QPainter *painter, QPaintEvent *event)
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
        case APHOTIC:
            pen = aphoticPen;
            text = "So Aphotic!";
			break;
	}
    textFont.setPixelSize(MAX_FONT - elapsed);
    painter->restore();
    painter->setPen(pen);
	painter->setFont(textFont);
    painter->drawText(QRect(0, 0, 200, 200), Qt::AlignCenter, text);

}

void HipWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	paint(&painter, event);
	painter.end();
}


// this is called every second because it has been linked to the timeout
void HipWidget::animate()
{

    // qobject_cast is a safer cast
    // interval() will get the interval of the QTimer (in this case one)
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 50;
    if(elapsed == 0){
        switchMode();
    }
	repaint();
}

void HipWidget::switchMode(){
    switch(currentMode){
    case HIP:
        currentMode = CURRENT;
        break;
    case CURRENT:
        currentMode = APHOTIC;
        break;
    case APHOTIC:
        currentMode = HIP;
        break;
    }
}
