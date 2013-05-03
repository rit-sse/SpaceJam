import Tkinter, subprocess

def callback():
	subprocess.call(['python2', 'leap-draw.py'])

def runKristenCode():
	#load and exit code
	btn = Tkinter.Button(win, command=callback, text="Run Leap")
	btn.pack()

if __name__ == '__main__':
	win = Tkinter.Tk()
	runKristenCode()
	win.mainloop()