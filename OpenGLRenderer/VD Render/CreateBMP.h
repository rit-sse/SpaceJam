//
//  CreateBMP.h
//  VD Render
//
//  Created by Michael Timbrook on 4/28/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CreateBMP : NSObject

+ (void)createWithPixelData:(GLbyte[])pixels size:(int)size;

@end
