import bpy
import math
import sys
filepath = sys.argv[-1]
print("reading from " + filepath)
# prompt for image
bpy.ops.import_scene.obj( filepath=filepath )
bpy.data.scenes["Scene"].render.filepath = "blenderOutput//" + filepath.split(".")[0] + "//"
bpy.ops.render.render(animation=True)