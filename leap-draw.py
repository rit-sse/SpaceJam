import Leap, sys, math, pygame

class DrawListener(Leap.Listener):

	def on_init(self, controller):
		self.location = None
		self.window = pygame.display.set_mode((800, 800))
		self.file = open('drawing.obj', 'w')
		self.file.write('o Drawing\n')
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
			self.file.write("v " +  str(vertex.x + 400) + " " + str(800-vertex.y) + " 0\n")
		self.file.write('s off\n')
		for x in range(0,self.count-4):
			self.file.write("f " + str(x+1) +  " " + str((x+1)%self.count + 1) + " " + str((x+2)%self.count + 1) + " " +  str((x+3)%self.count + 1)+"\n")
		self.file.close()

	def on_frame(self, controller):
		frame = controller.frame()
		fingers = frame.pointables
		numFingers = len(fingers)
		if numFingers > 0:
			finger = fingers[0]
			tip = finger.tip_position
			if self.location:
			 	pygame.draw.line(self.window,(255,255,255), (self.location.x + 400, 800-self.location.y), (400 + tip.x, 800-tip.y))
			self.location = tip
			self.verticies.append(self.location)
			self.count += 1
		pygame.display.flip()

def keyPressed(inputKey):
    keysPressed = pygame.key.get_pressed()
    if keysPressed[inputKey]:
        return True
    else:
        return False

def main():
  # Create a sample listener and assign it to a controller to receive events
  pygame.init()
  listener = DrawListener()
  controller = Leap.Controller()

  controller.add_listener(listener)

  print "Press Enter to quit..."
  sys.stdin.readline()

  # The controller must be disposed of before the listener
  controller.remove_listener(listener)
  sys.exit()


if __name__ == "__main__":
  main()