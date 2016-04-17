uniform samplerCube EnvMap;
uniform int selected;
varying vec3  texcoord;

void main (void)
{
   
    vec3 envColor = vec3 (textureCube(EnvMap, texcoord));
	//vec3 envColor = vec3 (textureCube(EnvMap, gl_TexCoord[0]));
	if(selected == 1) envColor = vec3(1,1,1);

    gl_FragColor = vec4 (envColor, 1.0);
}