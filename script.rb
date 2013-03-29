("0000".."0095").each do |num|
  `convert ./monkeySet2/#{num}.bmp -resize 608x684 -depth 1 -colors 2 ./bitSet/#{num}.bmp`
end
