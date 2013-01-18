#include <iostream>
#include "scrollListener.h"
#include "QPalette"
using namespace Leap;

ScrollListener::ScrollListener(Window* window) : window(window), Listener(){
}

void ScrollListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void ScrollListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void ScrollListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void ScrollListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void ScrollListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    if(!frame.hands().empty()){
        const Hand hand = frame.hands()[0];
        float pitch = hand.direction().pitch()*RAD_TO_DEG;
//        float roll = hand.palmNormal().roll()*RAD_TO_DEG;
//        float yaw = hand.palmNormal().yaw()*RAD_TO_DEG + 180;
        emit window->getXSlider()->valueChanged(pitch*52);
//        emit window->getYSlider()->valueChanged(roll*52);
//        emit window->getZSlider()->valueChanged(yaw*16);
    }

}
