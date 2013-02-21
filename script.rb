("0001".."0096").each do |num|
  `convert ./monkeySet/#{num}.bmp -resize 608x684 -depth 1 -colors 2 ./bitSet/#{num}.bmp`
end
