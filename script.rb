("0001".."0096").each do |num|
  `convert ./monkey/#{num}.bmp -colors 2 ./bit/#{num}.bmp`
end
