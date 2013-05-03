//
//  CreateBMP.m
//  VD Render
//
//  Created by Michael Timbrook on 4/28/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

#import <OpenGL/OpenGL.h>
#import "CreateBMP.h"

@implementation CreateBMP

+ (void)createWithPixelData:(GLbyte[])pixels size:(int)size {
    // Open The blank file.
    FILE *bmp;
    bmp = fopen("/Users/michael/Projects/VD Render/VD Render/BMP Render/test.bmp", "w+");
    
//    // Write header data
//    Byte *header;
//    header = (Byte *)calloc(1, sizeof(Byte) * 14);
//    // BMP Type OS/2
//    header[0] = 0x42;
//    header[1] = 0x4d;
//    // Size of the BMP 0x5F916
//    header[2] = 0x16;
//    header[3] = 0xF9;
//    header[4] = 0x05;
//    // Unused 6 - 9
//    // Pixel offset, offset to start
//    header[10] = 28;
//    // Write
//    for (int i = 0; i < 14; i++) {
//        fputc(header[i], bmp);
//    }
//    // Write DIB Header
//    Byte *dib;
//    dib = (Byte *)calloc(1, sizeof(Byte) * 14);
//    // Size fo DIB
//    dib[0] = 0x14;
//    // size
//    dib[4] = 0x5C;
//    dib[5] = 0x02;
//    dib[8] = 0x88;
//    dib[9] = 0x02;
//    // Planes
//    dib[12] = 0x01;
//    // Bit Depth
//    dib[14] = 24;
//    // Write
//    for (int i = 0; i < 40; i++) {
//        fputc(dib[i], bmp);
//    }
//    
//    // Write Data to File
    for (int i = 0; i < size; i++) {
        fputc(pixels[i], bmp);
    }
//    fclose(bmp);
//    free(header);
//    free(dib);
}


@end
