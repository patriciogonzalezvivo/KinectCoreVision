uniform sampler2D tex;
uniform float Contrast;
uniform float Brightness;
uniform float Invert;



// dilute and erode filters
//
//void median(){
//
//	
//	vec4 center = texture2D(tex,gl_TexCoord[0].st);
//	
//	vec2 offset = vec2(1.0/640.0,0);	
//	vec4 left  = texture2D(tex,gl_TexCoord[0].st - offset);
//	vec4 right = texture2D(tex,gl_TexCoord[0].st + offset);
//
//	offset = vec2(0.0,1.0/480.0);
//	vec4 up    = texture2D(tex,gl_TexCoord[0].st - offset);
//	vec4 down  = texture2D(tex,gl_TexCoord[0].st + offset);
//
//	float color = min(center.g, left.g);
//	color = min(color,right.g);
//	color = min(color,up.g);
//	gl_FragColor = vec4(min(color,down.g));
//
//}
//
//
//void main()
//{
//
//	if(Invert >0.5 )
//		median() ;
//	else
//		gl_FragColor = texture2D(tex,gl_TexCoord[0].st);
//	return;
//}


void main()
{

	vec4 color = texture2D(tex,gl_TexCoord[0].st);

	//adjust brightness and convert to grayscale
	float p = 0.3 *color.g + 0.59*color.r + 0.11*color.b;
	p = p * Brightness;
	color = vec4(p,p,p,1.0);
	color = mix( vec4(1.0,1.0,1.0,1.0),color,Contrast);
	
	gl_FragColor =  vec4(color.r , color.g, color.b, 1.0);
}
