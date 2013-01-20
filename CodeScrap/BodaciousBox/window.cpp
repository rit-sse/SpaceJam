#include <QtWidgets>
#include "BoxWidget.h"
#include "window.h"

Window::Window() : QWidget()
{
    BoxWidget *widget = new BoxWidget(this);
    setWindowTitle(tr("So Boxy"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widget, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), widget, SLOT(animate()));
    timer->start(1);
}
