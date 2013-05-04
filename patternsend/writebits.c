#include <FreeImage.h>
#include <stdio.h>
#include <stdlib.h>


#define FALSE 0


void writebits( ){
   
   FILE *fp;

   fp = fopen("test.bmp", "rb");

   if( ! fp ){
	  printf("could not open the file\n");
   }
   
   // get the size of the file
   fseek( fp, 0L, SEEK_END );
   int size  = ftell( fp );
   fseek( fp, 0L, SEEK_SET ); 


   unsigned char buffer[ size ];
   fread( buffer, sizeof(unsigned char), size, fp ); 
   
   printf("the size of the image is: %d", size);
   
   BYTE bytes[ size ];   
   
   
   
   int i = 0;
   for(; i < size; i++ ){
	  bytes[i] = buffer[i]; 
   }
    
   
   FIBITMAP* image = FreeImage_ConvertFromRawBits(
	  bytes,
	  648,
	  604,
	  604,
	  1,
	  0x0000FF,
	  0xFF0000,
	  0x00FF00,
	  FALSE 
   );

   
   // 
   FreeImage_Save(FIF_BMP, image, "out.bmp", 0);
   
   // Free resources
   FreeImage_Unload(image);



//   FIBITMAP* image = FreeImage_ConvertFromRawBits(
//	  pixels, 
//	  width, 
//	  height, 
//	  3 * width, 
//	  24, 
//	  0x0000FF, 
//	  0xFF0000, 
//	  0x00FF00, false);

   fclose( fp );

}


//    PI FIBITMAP *DLL_CALLCONV FreeImage_ConvertFromRawBits(
// 	  BYTE *bits, 
// 	  int width, 
// 	  int height, 
// 	  int pitch, 
// 	  unsigned bpp, 
// 	  unsigned red_mask, 
// 	  unsigned green_mask, 
// 	  unsigned blue_mask, 
// 	  BOOL topdown FI_DEFAULT(FALSE));


int main(){
   writebits( );
   return 1;
}
