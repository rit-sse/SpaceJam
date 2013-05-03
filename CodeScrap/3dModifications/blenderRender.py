import bpy
import math
import sys
filepath = sys.argv[-1]
print("reading from " + filepath)
# prompt for image
if (filepath.split(".")[1] == "stl"):
	bpy.ops.import_mesh.stl( filepath=filepath )
elif (filepath.split(".")[1] == "obj"):
	bpy.ops.import_scene.obj( filepath=filepath )
bpy.data.scenes["Scene"].render.filepath = "blenderOutput//" + filepath.split(".")[0] + "//"
bpy.ops.render.render(animation=True)