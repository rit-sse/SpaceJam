import Leap, sys, math, pyglet, subprocess
from pyglet.gl import *
from pyglet.gl.glu import *
from pyglet.window import key

class DrawListener(Leap.Listener):

    def on_init(self, controller):
        self.location = Leap.Vector()
        self.w = 800
        self.h = 800
        self.file = open('drawing.obj', 'w')
        self.faces = []
        self.thickness = 10
        self.file.write('o ' + 'Drawing\n')
        self.count = 0
        self.count_better = 0
        self.count_normals = 0
        self.x_avg = self.y_avg = self.z_avg = 0
        self.verticies = []
        self.vector_normals = []
        self.drawn = False
        print "Initialized"

    def on_connect(self, controller):
        print "Connected"

    def on_disconnect(self, controller):
        print "Disconnected"

    def sum_things(self, point):
        new_vector = Leap.Vector()
        new_vector.x = point.x - self.x_avg
        new_vector.y = point.y - self.y_avg
        new_vector.z = point.z - self.z_avg
        return new_vector

    def math_stuff(self, vertex1, vertex2, do_faces):
        x1, y1, z1 = vertex1.x, vertex1.y, vertex1.z
        x2, y2, z2 = vertex2.x, vertex2.y, vertex2.z
        self.count_better += 3
        self.count_normals += 6

        theta36 = math.atan((z2 - z1)/(x2-x1))
        theta47 = math.atan((x2 - x1)/(y2-y1))
        theta58 = math.atan((y2 - y1)/(z2-z1))

        vertex3 = Leap.Vector()
        vertex4 = Leap.Vector()
        vertex5 = Leap.Vector()

        vertex3.x = self.thickness*math.sin(theta36) + x1
        vertex4.x = x2
        vertex5.x = self.thickness*math.cos(theta58) + x1

        vertex3.y = self.thickness*math.cos(theta36) + y1
        vertex4.y = self.thickness*math.sin(theta47) + y1
        vertex5.y = y2

        vertex3.z = z2
        vertex4.z = self.thickness*math.cos(theta47) + z1
        vertex5.z = self.thickness*math.sin(theta58) + z1

        self.file.write("v " +  str(vertex3.x) + " " + str(vertex3.y) + " " + str(vertex3.z) + "\n")
        self.file.write("v " +  str(vertex4.x) + " " + str(vertex4.y) + " " + str(vertex4.z) + "\n")
        self.file.write("v " +  str(vertex5.x) + " " + str(vertex5.y) + " " + str(vertex5.z) + "\n")

        v3 = self.count_better - 2
        v4 = self.count_better - 1
        v5 = self.count_better
        v6 = self.count_better + 1
        v7 = self.count_better + 2
        v8 = self.count_better + 3

        n3 = self.count_better - 5
        n4 = self.count_better - 4
        n5 = self.count_better - 3
        n6 = self.count_better - 2
        n7 = self.count_better - 1
        n8 = self.count_better

        if(do_faces):
            normal3 = vertex1 - vertex3
            normal4 = vertex1 - vertex4
            normal5 = vertex1 - vertex5

            self.vector_normals.append("vn " + str(normal4.x) + " "+ str(normal4.y) + " " + str(normal4.z) + "\n" )
            self.vector_normals.append("vn " + str(normal4.x) + " "+ str(normal4.y) + " " + str(normal4.z) + "\n" )
            self.vector_normals.append("vn " + str(normal3.x) + " "+ str(normal3.y) + " " + str(normal3.z) + "\n" )
            self.vector_normals.append("vn " + str(normal3.x) + " "+ str(normal3.y) + " " + str(normal3.z) + "\n" )
            self.vector_normals.append("vn " + str(normal5.x) + " "+ str(normal5.y) + " " + str(normal5.z) + "\n" )
            self.vector_normals.append("vn " + str(normal5.x) + " "+ str(normal5.y) + " " + str(normal5.z) + "\n" )


            self.faces.append("f " + str(v3) + "//" + str(n3) +  " " + str(v6)  + "//" + str(n3) + " " + str(v5) + "//" + str(n3) + "\n")
            self.faces.append("f " + str(v6) + "//" + str(n4) +  " " + str(v5)  + "//" + str(n4) + " " + str(v8) + "//" + str(n4) + "\n")
            self.faces.append("f " + str(v5) + "//" + str(n5) +  " " + str(v8)  + "//" + str(n5) + " " + str(v4) + "//" + str(n5) + "\n")
            self.faces.append("f " + str(v8) + "//" + str(n6) +  " " + str(v4)  + "//" + str(n6) + " " + str(v7) + "//" + str(n6) + "\n")
            self.faces.append("f " + str(v4) + "//" + str(n7) +  " " + str(v7)  + "//" + str(n7) + " " + str(v3) + "//" + str(n7) + "\n")
            self.faces.append("f " + str(v7) + "//" + str(n8) +  " " + str(v3)  + "//" + str(n8) + " " + str(v6) + "//" + str(n8) + "\n")


    def on_exit(self, controller):
        print "Exited"
        pyglet.image.get_buffer_manager().get_color_buffer().save('../Preview/drawing.png')
        for vertex in self.verticies:
            self.x_avg += vertex.x
            self.y_avg += vertex.y
            self.z_avg += vertex.z
        self.x_avg /= self.count
        self.y_avg /= self.count
        self.z_avg /= self.count
        self.verticies = map(self.sum_things, self.verticies)
        it = self.count
        for i in range(0, self.count-1):
            if i == self.count-2:
                self.math_stuff(self.verticies[i], self.verticies[i+1], False)
            else:
                self.math_stuff(self.verticies[i], self.verticies[i+1], True)
        self.file.write('s off\n')
        for normal in self.vector_normals:
            self.file.write(normal)
        for face in self.faces:
            self.file.write(face)
        print str(self.verticies[0].x) + " " + str(self.verticies[0].y) + " " + str(self.verticies[0].z)
        print str(self.verticies[1].x) + " " + str(self.verticies[1].y) + " " + str(self.verticies[1].z)
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
            self.drawn = True


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
            # new_z = vertex.z + 300
            # color = math.floor(new_z/2)
            # rgb = hsv_to_rgb(color, 1, 1)
            # glColor3d(rgb[0], rgb[1], rgb[2])
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