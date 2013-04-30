import bpy
import math
import sys
filepath = sys.argv[-1]
print("reading from " + filepath)
# prompt for image
bpy.ops.import_scene.obj( filepath=filepath )
# fixing the center of the object
bpy.ops.object.origin_set(type='GEOMETRY_ORIGIN', center='MEDIAN')
bpy.ops.view3d.snap_selected_to_cursor()
# scaling the object
name = bpy.context.selected_objects[0].name
dim = bpy.data.objects[name].dimensions
arr = reversed(sorted(list(dim)))
scaleValue = (arr[0]**2+arr[1]**2)**0.5
bpy.data.cameras['Camera.001'].ortho_scale = scaleValue
#rendering the object
bpy.data.scenes["Scene"].render.filepath = "blenderOutput//" + filepath.split(".")[0] + "//"
bpy.ops.render.render(animation=True)