import bpy
import math
import sys







# prompt for image
bpy.ops.import_scene.obj( filepath=sys.argv[-1] )





layers = bpy.context.scene.layers
layers[19] = True
for i in range( 9, 10 ):
   for n in range( 0, len(layers) ):
      # changes visbility of layer
      layers[n] = False
   layers[i] = True
   bpy.data.scenes["Scene.001"].render.filepath = "//blenderOutput\\layer_"+str(i)+"\\"
   bpy.ops.render.render(animation=True)
