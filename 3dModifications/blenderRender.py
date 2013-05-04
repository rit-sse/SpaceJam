import bpy
import math
import sys
dirpath = sys.argv[-1]
print("reading from " + dirpath)
# prompt for image
print("file type = " + dirpath.split(".")[-1])
if (dirpath.split(".")[-1] == "stl"):
	print("STL")
	bpy.ops.import_mesh.stl( filepath=dirpath )
if (dirpath.split(".")[-1] == "obj"):
	print("OBJ")
	bpy.ops.import_scene.obj( filepath=dirpath )
print("1."+dirpath)
print("2."+dirpath.split(".")[-2])
bpy.data.scenes["Scene.001"].render.filepath = "blenderOutput//" + dirpath.split(".")[-2] + "//"
bpy.ops.render.render(animation=True)
#print("DONE")