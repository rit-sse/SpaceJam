import std.file;
import std.stdio;
import std.conv;



extern (C){  
    void writebits( char* bytes);
}


class BmpEncoder{
   

   private auto width = 648;
   private auto height = 604;

   private ubyte[] bytes;
   
   public this( ubyte[] bytes ){
	  
	  this.bytes = bytes;
	  	  
	   
	   
	  

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
