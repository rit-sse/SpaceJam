("0001".."0096").each do |num|
  `convert ./monkey/#{num}.bmp -colors 1 ./bit/#{num}.bmp`
end
