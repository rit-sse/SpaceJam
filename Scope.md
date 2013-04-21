#SpaceJam Scope
Description of software Library and implementation expected by the end of the 2012-2013 year.

##Possible Input:
* Gesutres:
    * Circle (Leap)
    * Screen Press (Leap)
    * Key Press (Leap)
    * Swipe (Leap)
* Point:
    * Key (Keyboard)
    * Vector (Leap)
    * Keynote (Cliker)

##Functional Requirements
* Must display dumb view with the buffer images on the projector
* Users should be able to send dumb input to dumb view
* Users should be able to generate 3D models using pre-made objects and/or code
* On input, the application should be able to update the display
* Can programmatically load images to the display.

##Non-Functional Requirements
* Must work with volumetric display
    * works with projector
    * works with motor
* Must integrate with OpenGL
* Must work with STL and OBJ files
* Must accept input from Keyboard and/or clicker
* Possibly Supports gestures from leap controller
* Must update images at a rate of at least 10 frames per second

##Decisions
* Written in D
* Use HDMI to realize high fps
