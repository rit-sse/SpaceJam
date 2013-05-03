class Vertex
	attr_accessor :x, :y, :z
	def initialize(x,y,z)
		@x = x.to_f
		@y = y.to_f
		@z = z.to_f
	end

	def absolute
		Vertex.new(@x.abs,@y.abs,@z.abs)
	end

	def scale!(scale_factor)
		@x = @x/scale_factor
		@y = @y/scale_factor
		@z = @z/scale_factor
	end

	def max
		[@x,@y,@z].max
	end

	def to_s
		"#{@x} #{@y} #{@z}"
	end
end

def scale_stl(fileIn,fileOut)
	puts(Time.new)
	vertex_arr = []
	furthest_vert = 0
	File.readlines(fileIn).each do |line|
		if line[0] == 'v'
			lineSplit = line.split()
			vertex = Vertex.new(lineSplit[1],lineSplit[2],lineSplit[3])
			vertex_arr += [vertex]
			furthest_vert = vertex.absolute.max
		end
	end
	puts(Time.new)
	scale_vertex_array!(vertex_arr, furthest_vert)
	puts(Time.new)
	#print(stl_stlStr(vertex_arr))
	File.open(fileOut, 'w') { |file| file.write("#{stl_stlStr(vertex_arr)}") }
	puts(Time.new)
end

def scale_vertex_array!(vertex_arr, scale_factor)
	vertex_arr.each do |vert|
		vert = vert.scale!(scale_factor)
	end
end

def stl_stlStr(vertex_arr)
	stlStr = "solid object\n"
	# for every 3 vertex's, make a face
	puts("#{Time.new} #{vertex_arr.length/3-1}")
	(0..(vertex_arr.length/3-1)).each do |i|
		stlStr.concat("facet normal 0 0 0\nouter loop\n")
		stlStr.concat("vertex #{vertex_arr.shift}\n")
		stlStr.concat("vertex #{vertex_arr.shift}\n")
		stlStr.concat("vertex #{vertex_arr.shift}\n")
		stlStr.concat("endloop\nendfacet\n")
	end
	puts(Time.new)
	stlStr.concat("endsolid object")
	return stlStr
end

scale_stl(ARGV[0],ARGV[1])