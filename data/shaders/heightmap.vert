uniform sampler2D colormap;
uniform sampler2D bumpmap;
uniform float min;
varying vec2  TexCoord;
uniform int maxHeight;

void main(void) {	
	TexCoord = gl_MultiTexCoord0.st;
	float realMin = min;

	vec4 bumpColor = texture2D(bumpmap, TexCoord);
	float df = 0.30*bumpColor.x + 0.59*bumpColor.y + 0.11*bumpColor.z;
	if(df - min < 0.03) realMin=df;
	df -= realMin;
	vec4 newVertexPos = vec4(gl_Normal * df * float(maxHeight), 0.0) + gl_Vertex;

	gl_Position = gl_ModelViewProjectionMatrix * newVertexPos;
} 