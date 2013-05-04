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

def stlToObj(fileIn,fileOut)
	vertex_arr = []
	File.readlines(fileIn).each do |line|
		lineSplit = line.split()
		if line[0] == 'v'
			if lineSplit.length == 4
				vertex_arr += [Vertex.new(lineSplit[1],lineSplit[2],lineSplit[3])]
			end
		end
	end
	File.open(fileOut, 'w') { |file| file.write("#{obj_objStr(vertex_arr)}") }
end

def obj_objStr(vertex_arr)
	objStr = "o object\n"
	vertex_arr.each do |vertex|
		objStr.concat("v #{vertex}\n")
	end
	objStr.concat("s off\n")
	(0..(vertex_arr.length/3-1)).each do |i|
		objStr.concat("f #{3*i+1} #{3*i+2} #{3*i+3}\n")
	end
	return objStr
end

stlToObj(ARGV[0],ARGV[1])