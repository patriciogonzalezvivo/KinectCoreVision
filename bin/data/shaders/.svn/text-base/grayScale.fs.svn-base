uniform sampler2D tex;

void main(void)
{
    vec4 textureColor = texture2D(tex, gl_TexCoord[0].st);
    float luminance = dot(vec3 (0.2125, 0.7154, 0.0721), vec3(textureColor));

gl_FragColor = vec4(luminance, luminance, luminance, 1.0);
}