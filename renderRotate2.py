import bpy
import math
import sys





filepath = sys.argv[-1]


print("reading from " + filepath)


# prompt for image
bpy.ops.import_scene.obj( filepath=filepath )


print("loaded the custom.obj")

bpy.data.scenes["Scene"].render.filepath = "blenderOutput//" + filepath + "//"


print("loaded the file path yo")

bpy.ops.render.render(animation=True)


print("done")
