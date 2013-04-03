("0000".."0095").each do |num|
  `convert ./blenderOutput/#{num}.png -resize 608x684 -depth 1 -colors 2 ./bitSet/#{num}.bmp`
end
