directory = ARGV[0]
images = File.join("#{directory}", "*.png")
Dir.glob(images).each do |image|
  outFile = "../../bitFolder/#{image.split(".")[0]}.bmp"
  outFolder = outFile.split("/")[0..-2].join("\\")+"\""
  if !(Dir.exists?(outFolder[2..-2]))
    `mkdir #{outFolder[2..-2]}`
  end
  `convert ./#{image} -resize 684x608 -depth 1 -colors 2 #{outFile}`
end
