class Vertex
	attr_accessor :x, :y, :z
  attr_reader :x, :y, :z
	def initialize(x,y,z)
		@x = x.to_f
		@y = y.to_f
		@z = z.to_f
	end
	
	def to_s
		"#{@x} #{@y} #{@z}"
	end
end

def objToStl(fileIn,fileOut)
	vertex_arr = []
	faces_arr = []
	File.readlines(fileIn).each do |line|
		lineSplit = line.split()
		if line[0] == 'v'
			if lineSplit.length == 4
				vertex_arr += [Vertex.new(lineSplit[1],lineSplit[2],lineSplit[3])]
			end
			if lineSplit.length == 5
				vertex_arr += [Vertex.new(lineSplit[1],lineSplit[2],lineSplit[3])]
				vertex_arr += [Vertex.new(lineSplit[2],lineSplit[3],lineSplit[4])]
			end
		end
		if line[0] == 'f'
			faces_arr += [lineSplit.drop(1)]
		end
	end
	File.open(fileOut, 'w') { |file| file.write("#{stl_stlStr(faces_arr, vertex_arr)}") }
end

def stl_stlStr(faces_arr, vertex_arr)
	stlStr = "solid object\n"
	faces_arr.each do |face|
		if face.length == 3	
			stlStr.concat("facet normal 0 0 0\nouter loop\n")
			stlStr.concat("vertex #{vertex_arr[face[0].to_i-1]}\n") # indexing for objs start at 1
			stlStr.concat("vertex #{vertex_arr[face[1].to_i-1]}\n")
			stlStr.concat("vertex #{vertex_arr[face[2].to_i-1]}\n")
			stlStr.concat("endloop\nendfacet\n")
		elsif face.length == 4
		stlStr.concat("facet normal 0 0 0\nouter loop\n")
			stlStr.concat("vertex #{vertex_arr[face[0].to_i-1]}\n") # indexing for objs start at 1
			stlStr.concat("vertex #{vertex_arr[face[1].to_i-1]}\n")
			stlStr.concat("vertex #{vertex_arr[face[2].to_i-1]}\n")
			stlStr.concat("endloop\nendfacet\n")
			stlStr.concat("facet normal 0 0 0\nouter loop\n")
			stlStr.concat("vertex #{vertex_arr[face[0].to_i-1]}\n") # indexing for objs start at 1
			stlStr.concat("vertex #{vertex_arr[face[2].to_i-1]}\n")
			stlStr.concat("vertex #{vertex_arr[face[3].to_i-1]}\n")
			stlStr.concat("endloop\nendfacet\n")
		end
	end
	stlStr.concat("endsolid object")
	return stlStr
end

objToStl(ARGV[0],ARGV[1])