uniform sampler2D tex;
uniform float Threshold;
uniform float enabled;

void main()
{
    vec4 color = texture2D(tex,gl_TexCoord[0].st);
    float c = color.g;
    c = c - Threshold;
    c = max(c,0.0);
    c = c/c;
    gl_FragColor = enabled > 0.0 ? vec4(c,c,c,1.0) : color;
}
