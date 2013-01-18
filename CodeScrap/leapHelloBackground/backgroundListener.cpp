#include <iostream>
#include "backgroundListener.h"
#include "QPalette"
using namespace Leap;

BackgroundListener::BackgroundListener(Window* window) : window(window), fingerThere(false), isPurple(true), Listener(){
    purple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    red = Qt::red;
}

void BackgroundListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void BackgroundListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void BackgroundListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void BackgroundListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

//Changes the color of the background if the leap detects fingers
void BackgroundListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", fingers: " << frame.fingers().count()
            << ", tools: " << frame.tools().count() << std::endl;
    if(!frame.hands().empty()){
        const Hand hand = frame.hands()[0];
        const FingerList fingers = hand.fingers();
        if(!fingers.empty()){
            if(isPurple){
                emit window->backgroundColorChanged(red);
                isPurple = false;
            }else{
                emit window->backgroundColorChanged(purple);
                isPurple = true;
            }
        }
    }
}
