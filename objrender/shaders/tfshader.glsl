uniform vec4 ambient, diffuse, specular;
uniform float hardness;
uniform sampler2D texture;

varying vec3 L;
varying vec3 H;
varying vec3 N;

varying vec2 texCoord;


void main()
{
	float Kd = max(dot(L, N), 0.0);
	vec4 diffuseTotal = Kd * diffuse;
	float Ks = pow(max(dot(N, H), 0.0), hardness);
	vec4 specularTotal = Ks * specular;	
	if (dot(L, N) < 0.0)		
		specularTotal = vec4(0.0, 0.0, 0.0, 1.0);

	vec4 color = ambient + diffuseTotal + specularTotal;
	color.a = 1.0;

    gl_FragColor = color * texture2D(texture, texCoord);
}
