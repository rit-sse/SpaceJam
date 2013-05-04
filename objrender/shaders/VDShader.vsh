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

// Distortion
uniform vec4 reflectedP; // reflected projector position P’
uniform vec4 mirrorNormal; // normal of mirror plane

// Finds the point that lays on the plan defined by the normal from the mirror.
// The mirror is at 0,0,0 and the vector VQ is coming from the relected projector
vec4 RayPlaneIntersection(vec4 rayStart,vec4 rayEnd, vec4 mirror) {
    float t = - dot(mirror, rayStart) / dot(mirror, rayEnd);
    vec4 PM;
    PM = rayStart + (t * rayEnd);
    return PM;
}


void main()
{
    // The matrix as defined in the openGL code
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 2.0, 1.0);
    vec4 diffuseColor = vec4(255/255, 153/255, 153/255, 1.0);
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
    colorVarying = diffuseColor * nDotVP;
    
    // Distortion for mirror reflection
    // Get the ray from the relected projector to the point in space
    vec4 pointRay = position - reflectedP;
    // Normalize the ray
    vec4 PQ = normalize(pointRay);
    
    // Map that point to the point that's on the mirror
    vec4 PM = RayPlaneIntersection(reflectedP, PQ, mirrorNormal);

    gl_Position = modelViewProjectionMatrix * PM;
}



