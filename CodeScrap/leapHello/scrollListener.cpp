#include <iostream> 
#include "scrollListener.h"
#include "QPalette"
using namespace Leap;

ScrollListener::ScrollListener(Window* window) : _window(window), _fingerThere(false), Listener(){
    _qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
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
    std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", fingers: " << frame.fingers().count()
            << ", tools: " << frame.tools().count() << std::endl;
	// if(!frame.hands().empty()){
	// 	const Hand hand = frame.hands()[0];
	// 	const FingerList fingers = hand.fingers();
	// 	if(!fingers.empty()){
   //          QPalette p;
			// p.setColor(QPalette::Background, Qt::red);
			// _window->glWidget->setAutoFillBackground(true);
			// _window->glWidget->setPalette(p);
             _window->glWidget->qglClearColor(_qtGreen);
            std::cout << "change color" << std::endl;
			_fingerThere = true;
		// }
	// }
}
