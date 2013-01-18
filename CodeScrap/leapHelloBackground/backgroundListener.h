#include "Leap.h"
#include "window.h"

class GLWidget;

class BackgroundListener : public Leap::Listener
{
public:

    BackgroundListener(Window* window);

    virtual void onInit(const Leap::Controller&);

    virtual void onConnect(const Leap::Controller&);

    virtual void onDisconnect(const Leap::Controller&);

    virtual void onExit(const Leap::Controller&);

    virtual void onFrame(const Leap::Controller&);

private:
    Window* window;
    QColor red;
    QColor purple;
    bool isPurple;
    bool fingerThere;
};
