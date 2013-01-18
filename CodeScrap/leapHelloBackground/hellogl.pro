HEADERS       = glwidget.h \
                window.h \
                qtlogo.h \
                backgroundListener.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                qtlogo.cpp \
                backgroundListener.cpp
QT           += opengl widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl
INSTALLS += target


simulator: warning(This example might not fully work on Simulator platform)

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix|win32: LIBS += -lLeap
