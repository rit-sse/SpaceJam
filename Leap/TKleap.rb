require 'tk'
root = TkRoot.new { title "Run Leap" }
TkButton.new(root)  do
  text  'Run Leap!'
  command proc { path_to_script = File.dirname(__FILE__); `python2 #{path_to_script}/leap-draw.py` }
  pack("side" => "right",  "padx"=> "50", "pady"=> "10")
end
Tk.mainloop

