inputObj = ARGV[0]
`blender -b objRender.blend -P blenderRender.py #{inputObj}`
`ruby folderToBmps.rb ..\\..\\`
