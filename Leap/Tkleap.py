import Tkinter, subprocess, os

#Set up Tk window
win = Tkinter.Tk()

#Get the size that we'll use for Listbox
s = len(os.listdir("../OBJs"))

#Listbox with various OBJs
stlBox = Tkinter.Listbox(win, selectmode="SINGLE", height=s)
stlBox.grid(row=0, column=0)

for i in os.listdir("../OBJs"):
	stlBox.insert(stlBox.size(), i)
stlBox.selection_set(0)

#Button to run Leap Code
btn = Tkinter.Button(win, text="Draw using the Leap")
btn.grid(row=1, column=0)

#Imageloading frame
imgLabel = Tkinter.Label(win)
imgLabel.grid(row=0, column=1)

#Upload button
uploadButton = Tkinter.Button(win, text="Upload to Projector")
uploadButton.grid(row=1, column=1)

def leapCall():
	# Call Kristen's super awesome leap code
	#subprocess.call(['python', 'leap-draw.py'])

	pass
	
btn.config(command=leapCall)

def loadImage(event=None):
	preview = stlBox.get(stlBox.curselection())
	preview = "../Preview/"+preview[:-4]
	preview += ".gif"
	print(preview)
	photo = Tkinter.PhotoImage(file=preview)
	
	imgLabel.configure(image=photo)
	imgLabel.image = photo #need to keep a reference
	print(stlBox.get(stlBox.curselection()))
	
stlBox.bind("<ButtonRelease>", loadImage)
loadImage()

def uploadImage(event=None):
	#the currently selected STL
	currentSelection = stlBox.get(stlBox.curselection())

	# Call Seans's super awesome obj render code
	#   (temp) just use a ship obj to test
	subprocess.call(['./objrender', "../OBJs/" + currentSelection])

	# Call the conversion script to create 1 bit images
	subprocess.call(['ruby', "folderToBmps.rb", "output"])

	#Call Sean and Lee's super awesome D code
	# os.exists?
	#subprocess.call(['./patternsend', '../'])
	
uploadButton.config(command=uploadImage)
	
if __name__ == '__main__':
	win.mainloop()
