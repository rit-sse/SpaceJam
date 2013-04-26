//
//  Shader.fsh
//  Volumetric Display Driver
//
//  Created by Michael Timbrook on 4/23/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

varying vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
