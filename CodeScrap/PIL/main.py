# smport Image, ImageDraw
 
import Image, ImageDraw
 
 
def pil_image():
   size = (100, 50)
   im = Image.new( "RGB", size )
   draw = ImageDraw.Draw( im )
   red = ( 255, 0, 0 )
   text_pos = (10, 10)
   text = "Hello World!"


   draw.text( text_pos, text, fill=red )
   im.save( "hello.png", "PNG" )
	 
	  
	   


pil_image()
