import Leap, sys, math, pyglet, subprocess
from pyglet.gl import *
from pyglet.gl.glu import *
from pyglet.window import key

class DrawListener(Leap.Listener):

    def on_init(self, controller):
        self.location = Leap.Vector()
        self.cursor = Leap.Vector()
        self.w = 800
        self.h = 800
        self.file = open('drawing.obj', 'w')
        self.file.write('o ' + 'Drawing\n')
        self.count = 0
        self.x_avg = self.y_avg = self.z_avg = 0
        self.verticies = []
        print "Initialized"

    def on_connect(self, controller):
        print "Connected"

    def on_disconnect(self, controller):
        print "Disconnected"

    def sum_things(self, point):
        new_vector = Leap.Vector()
        new_vector.x = point.x + self.x_avg
        new_vector.y = point.y + self.y_avg
        new_vector.z = point.z + self.z_avg
        return new_vector

    def on_exit(self, controller):
        print "Exited"
        for vertex in self.verticies:
            self.x_avg += vertex.x
            self.y_avg += vertex.y
            self.z_avg += vertex.z
        self.x_avg /= self.count
        self.y_avg /= self.count
        self.z_avg /= self.count
        self.vertices = map(self.sum_things, self.verticies)
        for vertex in self.verticies:
            self.file.write("v " +  str(vertex.x + self.w/2) + " " + str(self.h-vertex.y) + " " + str(vertex.z) + "\n")
        self.file.write('s off\n')
        for x in range(0,self.count-4):
            self.file.write("f " + str(x+1) +  " " + str((x+1)%self.count + 1) + " " + str((x+2)%self.count + 1) + " " +  str((x+3)%self.count + 1)+"\n")
        self.file.close()
        subprocess.call(['ruby', '../3dModifications/objToStl.rb', 'drawing.obj', '../STLs/'+ 'drawing.stl'])
        subprocess.call(['ruby', '../3dModifications/stlScale.rb', '../STLs/'+ 'drawing.stl', '../STLs/'+ 'drawing.stl'])

    def on_frame(self, controller):
        frame = controller.frame()
        fingers = []
        if len(frame.hands) > 0:
            fingers = frame.hands[0].fingers
        numFingers = len(fingers)
        if numFingers > 0:
            finger = fingers.frontmost
            tip = finger.tip_position
            self.location = tip
            self.location.x += self.w/2
            self.verticies.append(self.location)
            self.count += 1

def hsv_to_rgb(h, s, v):
    i = 0
    f, p, q, t = 0, 0, 0, 0
    if s == 0:
        r = g = b = v
        return
    h /= 60.0
    i = math.floor(h)
    f = h - i
    p = v * ( 1 - s )
    q = v * ( 1 - s * f )
    t = v * ( 1 - s * ( 1 - f ) )
    if i == 0:
        r = v
        g = t
        b = p
    elif i == 1:
        r = q
        g = v
        b = p
    elif i == 2:
        r = p
        g = v
        b = t
    elif i == 3:
        r = p
        g = q
        b = v
    elif i == 4:
        r = t
        g = p
        b = v
    else:
        r = v
        g = p
        b = q
    return [r, g, b]

def update(dt):
     pass

def main():
    listener = DrawListener()
    controller = Leap.Controller()
    win = pyglet.window.Window(800 , 800)
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
            new_z = vertex.z + 300
            color = math.floor(new_z/2)
            rgb = hsv_to_rgb(color, 1, 1)
            glColor3d(rgb[0], rgb[1], rgb[2])
            glVertex2d(vertex.x, vertex.y)
        glEnd()
    @win.event
    def on_key_press(symbol, modifiers):
        # Symbolic names:
        if symbol == key.RETURN:
            controller.remove_listener(listener)
            pyglet.app.exit()
            sys.exit()
    pyglet.clock.schedule_interval(update, 1/60.0)
    controller.add_listener(listener)
    pyglet.app.run()

if __name__ == '__main__':
    main()