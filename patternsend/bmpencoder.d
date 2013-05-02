import std.file;
import std.stdio;




// EXTERNAL DECLARATIONS
alias uint uint32_t;
alias ubyte uint8_t;

// external structs 
struct bmpfile_t;
struct rgb_pixel_t{
  uint8_t blue;
  uint8_t green;
  uint8_t red;
  uint8_t alpha;
}


// external functions
extern (C) bmpfile_t *bmp_create( uint32_t width, uint32_t height, uint32_t depth );
extern (C) bool bmp_set_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y, rgb_pixel_t pixel);
extern (C) bool bmp_save( bmpfile_t *bmp, const char *filename );

class BmpEncoder{
   

   private auto width = 648;
   private auto height = 604;

   private ubyte[] bytes;
   
   public this( ubyte[] bytes ){
	  
	  this.bytes = bytes;
	  
	  
	  rgb_pixel_t black_pixel = {1, 1, 1, 1};
	   
	  bmpfile_t *file = bmp_create(width, height, 1);
	  foreach(int px, ubyte b; bytes){
		 
		 auto row = px / width;
		 auto col = px % width;
		 if( b != 0 && px < width * height && row < 400 && col < 400){
			
			
				
			if( ! bmp_set_pixel( file, row, col, black_pixel ) ){
			   writeln("error saving\n\n");
			   writefln("at at %d, %d", row, col); 
			}else{
			   writefln("success saving at %d, %d", row, col );
			}
		 }
		  
	  }

	  const char* name = cast(const char*)"out.bmp";
	  auto saved = bmp_save( file,  name );

	  writeln("saved: ", saved );
	  

   }

   public ubyte[] getBMPEncoding(){
	    return []; 
   }

}

int main(){
   return 1;
}


unittest{
   
   
   
   auto file = File("test.bmp"); 
   ulong filesize = getSize( cast(const char[])"test.bmp" ); 
   ubyte[] inp = new ubyte[ filesize ];
   file.rawRead!ubyte( inp ); 
   auto encoder = new BmpEncoder( inp );  

}
