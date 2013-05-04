
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;


attribute vec3 vPosition;
attribute vec3 vNormal;
attribute vec2 vTexCoord;


varying vec3 L;
varying vec3 H;
varying vec3 N;

varying vec2 texCoord;


void main()
{
   	vec4 position = view * model * vec4(vPosition, 1.0); 
   	vec3 pos = position.xyz; 

   	vec4 light = view * vec4(lightPosition, 1.0); 
   	//vec4 light = projection * view * vec4(lightPosition, 1.0); 

	L = normalize(light.xyz - pos);	
	H = normalize(L + normalize(-pos));
	N = normalize(view * model * vec4(vNormal, 0.0)).xyz;

	// Apply model, view, and projection transforms and set the position
    gl_Position = projection * position;

    texCoord = vTexCoord;
}
