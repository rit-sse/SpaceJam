import Leap, sys, math, pygame
import pyglet
from pyglet.gl import *
from pyglet.window import key



class DrawListener(Leap.Listener):

    def on_init(self, controller):
        self.location = Leap.Vector()
        self.drawn = False
        self.w = 1680
        self.h = 1050
        filename = raw_input('What would you like to call this?')
        self.file = open(filename+'.obj', 'w')
        self.file.write('o ' + filename + '\n')
        # self.window = pygame.display.set_mode((self.w, self.h))
        self.count = 0
        self.verticies = []
        print "Initialized"

    def on_connect(self, controller):
        print "Connected"

    def on_disconnect(self, controller):
        print "Disconnected"

    def on_exit(self, controller):
        print "Exited"
        for vertex in self.verticies:
            self.file.write("v " +  str(vertex.x + self.w/2) + " " + str(self.h-vertex.y) + " " + str(vertex.z) + "\n")
        self.file.write('s off\n')
        for x in range(0,self.count-4):
            self.file.write("f " + str(x+1) +  " " + str((x+1)%self.count + 1) + " " + str((x+2)%self.count + 1) + " " +  str((x+3)%self.count + 1)+"\n")
        self.file.close()

    def on_frame(self, controller):
        frame = controller.frame()
        fingers = []
        if len(frame.hands) > 0:
            fingers = frame.hands[0].fingers
        numFingers = len(fingers)
        if numFingers > 0:
            finger = fingers.rightmost
            tip = finger.tip_position
            print str(abs(self.location.x - tip.x - self.w/2)) + " " + str(abs(self.location.y - tip.y))
            if not self.drawn or (abs(self.location.x - tip.x - self.w/2) < 25 and abs(self.location.y - tip.y) < 25):
                self.location = tip
                self.location.x += self.w/2
                self.verticies.append(self.location)
                self.count += 1
                self.drawn = True
        # pygame.display.flip()

listener = DrawListener()
controller = Leap.Controller()
win = pyglet.window.Window(1680, 1050)

@win.event
def on_draw():
    # Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)         # enable depth testing
    # reset modelview matrix
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glLineWidth(5)
    # Draw some stuff
    glBegin(GL_LINE_STRIP)
    for vertex in listener.verticies:
        glVertex2d(vertex.x, vertex.y)
    glEnd()

@win.event
def on_key_press(symbol, modifiers):
    # Symbolic names:
    if symbol == key.RETURN:
        controller.remove_listener(listener)
        pyglet.app.exit()
        sys.exit()

def update(dt):
     pass

pyglet.clock.schedule_interval(update, 1/60.0)


def main():
    # Create a sample listener and assign it to a controller to receive events
    # pygame.init()

    controller.add_listener(listener)
    pyglet.app.run()


if __name__ == "__main__":
  main()