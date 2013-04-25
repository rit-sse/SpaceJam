inputObj = ARGV[0]
`blender -b volumetricHologram.blend -P renderRotate2.py #{inputObj}`
`ruby script.rb n`
