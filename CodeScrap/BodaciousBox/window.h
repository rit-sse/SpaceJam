#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "BoxWidget.h"

QT_BEGIN_NAMESPACE
// class QLabel;
class QWidget;
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
};

#endif
