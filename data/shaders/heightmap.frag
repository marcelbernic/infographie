uniform sampler2D colormap;
uniform sampler2D bumpmap;
varying vec2  TexCoord;
uniform float min;
uniform vec4 col;
void main(void) {
	vec4 color = texture2D(colormap, TexCoord);

	gl_FragColor = color;
}