//
//  VDShader.vsh
//  Volumetric Display Distortion Driver
//  This shader will distort the image to counter the fact that the images are
//  being reflected off a mirror by posistion the points on the mirror as if
//  they were the ray intersections of that plane if the projector was behind
//  the mirror.
//
//  Created by Michael Timbrook on 4/23/13.
//  Copyright (c) 2013 Michael Timbrook. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;

varying vec4 colorVarying; // low precision for ES rendering on mobile
                                // Remove lowp for desktop rendering
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    // The matrix as defined in the openGL code
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 1.0, 0.0);
    vec4 diffuseColor = vec4(255/255, 153/255, 153/255, 1.0);
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
    colorVarying = diffuseColor * nDotVP;
    
    gl_Position = modelViewProjectionMatrix * position;
}



