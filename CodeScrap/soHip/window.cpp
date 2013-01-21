#include <QtWidgets>
#include "hipWidget.h"
#include "window.h"

Window::Window() : QWidget()
{
    HipWidget *widget = new HipWidget(this);
    setWindowTitle(tr("So Hip"));

    // similar to java grid layout, adding at
    // 0, 0 will cause the widget to take up the whole screen
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widget, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);


    // every time the timer time's out, the widget's animate
    // method will be called
    connect(timer, SIGNAL(timeout()), widget, SLOT(animate()));

    // the timer will timeout (emit the timeout signal every 1 millisecond)
    timer->start(1);
}
