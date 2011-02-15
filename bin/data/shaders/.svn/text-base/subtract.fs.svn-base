uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	vec4 color = texture2D(tex,gl_TexCoord[0].st);
	vec4 color2 = texture2D(tex2,gl_TexCoord[0].st);
	gl_FragColor = color - color2;
}
