uniform sampler2D colormap;
uniform sampler2D bumpmap;
varying vec2  TexCoord;
uniform float min;
uniform int selected;
void main(void) {
	vec4 color = texture2D(colormap, TexCoord);
	if(selected == 1) color = vec4(1,1,1,1);
	gl_FragColor = color;
}