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
//    std::cout << "Frame id: " << frame.id()
//            << ", timestamp: " << frame.timestamp()
//            << ", hands: " << frame.hands().count()
//            << ", fingers: " << frame.fingers().count()
//            << ", tools: " << frame.tools().count() << std::endl;
    if(!frame.hands().empty()){
        const Hand hand = frame.hands()[0];
        const FingerList fingers = hand.fingers();
        float pitch = hand.direction().pitch()*RAD_TO_DEG + 180;
//        float roll = hand.palmNormal().roll()*RAD_TO_DEG + 180;
//        float yaw = hand.direction().yaw()*RAD_TO_DEG + 180;
        emit window->getXSlider()->valueChanged(pitch*16);
//        emit window->getYSlider()->valueChanged(roll*16);
//        emit window->getZSlider()->valueChanged(yaw*16);
    }

}
