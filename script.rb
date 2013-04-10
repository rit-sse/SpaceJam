print("do you want to replace images that have already been converted? (Y/n): ")
input = gets.chomp
images = File.join("**", "*.png")
Dir.glob(images).each do |image|
  outFile = "./bitFolder/#{image.split(".")[0]}.bmp"
  outFolder = outFile.split("/")[0..-2].join("\\")+"\""
  if !(Dir.exists?(outFolder[2..-2]))
    `mkdir #{outFolder[2..-2]}`
  end
  if !(input=="n" && File.file?(outFile))
    `convert ./#{image} -resize 608x684 -depth 1 -colors 2 #{outFile}`
  end
end
