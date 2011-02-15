uniform sampler2D	tex;
uniform float direction;
uniform float kernel_size;
uniform float size_cx;
uniform float size_cy;

void main (void) {

    float rho = 20.0;


    vec2 dir = direction < 0.5 ? vec2(1.0,0.0) : vec2(0.0,1.0);

	float dx = 1.0 / size_cx;

	float dy = 1.0 / size_cy;
	vec2  st = gl_TexCoord [0].st;
	
	vec4	color = vec4 (0.0, 0.0, 0.0, 0.0);
	float	weight = 0.0;
	for (float i = -1.0*kernel_size ; i <= kernel_size ; i+=1.0) {
		float fac = exp (-(i * i) / (2.0 * rho * rho));
		weight += fac;
		color += texture2D (tex, st + vec2 (dx*i, dy*i) * dir) * fac;
	}
	
	gl_FragColor =  color / weight;
}
