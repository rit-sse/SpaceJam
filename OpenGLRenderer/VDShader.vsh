//
//  VDShader.vsh
//  Volumetric Display Distortion Driver
//  This shader will distort the image to counter the fact that the images are
//  being reflected off a mirror by posistion the points on the mirror as if
//  they were the ray intersections of that plane if the projector was behind
//  the mirror.
//
//  Created by Michael Timbrook on 4/23/13.
//  Copyright (c) 2013 MichaelTimbrook. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;

varying lowp vec4 colorVarying;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

// Distortion
uniform vec4 reflectedP; // reflected projector position P’
uniform vec4 mirrorNormal; // normal of mirror plane

// Finds the point that lays on the plan defined by the normal from the mirror.
// The mirror is at 0,0,0 and the vector VQ is coming from the relected projector
vec4 RayPlaneIntersection(vec4 rayStart,vec4 rayEnd, vec4 mirror) {
    
    // Using a ray tracing method
    // Planes are defined as:
    // nx(x-x0) + ny(y-y0) + nz(z-z0) = 0
    // Broken down:
    // nx, ny, nz defines the normal
    // x0, y0, z0 defines a point on the plane, in this case the origin 0,0,0
    //      because that's were we defined the mirror to always exist
    // Rays are defined as:
    // xs, ys, zs defines the starting point
    // xd, yd, zd degines the direction
    // The intersection will be defined as a point which will be calulated off
    // of the ray by using:
    //      n=ns+t*nd
    // pluggin each x, y and z in for n.
    // t is the scalling factor that will move the point in space, it's defined
    // with the SIGGRAPH algorythm to be:
    // t = (x0 * nx + y0 * ny + z0 * zn - nx * xs - ny * ys - nz * zs) / (xd * nx + yd * ny + zd * nz)
    // This can be simplified more to the following because the plane is at 0, 0, 0
    
    float t = ( - mirror.x * rayStart.x - mirror.y * rayStart.y - mirror.z * rayStart.z) / 
    (rayEnd.x * mirror.x + rayEnd.y * mirror.y + rayEnd.z * mirror.z);
    
    vec4 VQ;
    VQ.x = rayStart.x + t * rayEnd.x;
    VQ.y = rayStart.y + t * rayEnd.y;
    VQ.z = rayStart.z + t * rayEnd.z;
    
    return VQ;
}


void main()
{
    // The rotation matrix as defined in the openGL code
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 0.0, 1.0);
    vec4 diffuseColor = vec4(255/255, 153/255, 153/255, 1.0);
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
    colorVarying = diffuseColor * nDotVP;
    
    // new Position points from the rotation that the distortion need appied to
    vec4 pos = modelViewProjectionMatrix * position;
    
    // Distortion for mirror
    // Get the ray from the relected projector to the point in space
    vec4 PQ = pos - reflectedP;
    PQ = normalize(PQ);
    
    // "Move" that point to the point that lays on the mirror
    vec4 M = RayPlaneIntersection(reflectedP, pos, mirrorNormal);
    
    gl_Position = modelViewProjectionMatrix * M;
}



