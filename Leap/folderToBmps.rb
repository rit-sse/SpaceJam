directory = ARGV[0]
images = File.join("#{directory}", "*.bmp")
Dir.glob(images).each do |image|
  outFile = "fullOutput/#{File.basename(image, ".bmp")}.bmp"
  `convert ./#{image} -depth 1 -colors 2 #{outFile}`
end
