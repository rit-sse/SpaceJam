#include <QtWidgets>
#include "hipWidget.h"
#include "window.h"

Window::Window() : QWidget()
{
    HipWidget *widget = new HipWidget(this);
    setWindowTitle(tr("So Hip"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widget, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), widget, SLOT(animate()));
    timer->start(1);
}
