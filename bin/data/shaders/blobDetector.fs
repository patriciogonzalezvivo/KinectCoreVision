uniform sampler2D tex;

void main()
{
	vec2 offset = vec2(1.0/512.0, 1.0/512.0);

	float weight = 1.0;
	vec2 positionSum = gl_TexCoord[0].xy;
	float numPixelsL = 1.0;
	float numPixelsR = 1.0;
	float numPixelsU = 1.0;
	float numPixelsD = 1.0;
 
	int maxSize = 200;
	for (int i=1; i<maxSize && weight > 0.0; i++){
		vec2 currentOffset = float(i)*vec2(1.0, 0.0)* offset;
		weight = (texture2D(tex, gl_TexCoord[0].xy + currentOffset).r > 0.5 ? 1.0 : 0.0) * weight ; 
		numPixelsR = numPixelsR +  1.0* weight;
	}
	if(weight > 0.0){
		numPixelsR = 0.0;
		weight = 0.0;
	}else{
		weight = 1.0;
	}

	for (int i=1; i<maxSize && weight > 0.0; i++){
		vec2 currentOffset = float(i)*vec2(0.0, 1.0)* offset;
		weight = (texture2D(tex, gl_TexCoord[0].xy + currentOffset).r > 0.5 ? 1.0 : 0.0) * weight ; 
		numPixelsU = numPixelsU +  1.0* weight;
	}
	if(weight > 0.0){
		numPixelsU = 0.0;
		weight = 0.0;
	}else{
		weight = 1.0;
	}

	weight = 1.0;
	for (int i=1; i<maxSize && weight > 0.0; i++){
		vec2 currentOffset = float(i)*vec2(0.0, -1.0)* offset;
		weight = (texture2D(tex, gl_TexCoord[0].xy + currentOffset).r > 0.5 ? 1.0 : 0.0) * weight ; 
		numPixelsD = numPixelsD +  1.0* weight;
	}
	if(weight > 0.0){
		numPixelsD = 0.0;
		weight = 0.0;
	}else{
		weight = 1.0;
	}
	
	weight = 1.0;
	for (int i=1; i<maxSize && weight > 0.0; i++){
		vec2 currentOffset = float(i)*vec2(-1.0, 0.0)* offset;
		weight = (texture2D(tex, gl_TexCoord[0].xy + currentOffset).r > 0.5 ? 1.0 : 0.0) * weight ; 
		numPixelsL = numPixelsL +  1.0* weight;
	}
	if(weight > 0.0){
		numPixelsL = 0.0;
		weight = 0.0;
	}else{
		weight = 1.0;
	}





	if(numPixelsL > 5.0){
		float centerL = abs(numPixelsU - numPixelsD) < 2.0 ? 1.0 : 0.0;
		float centerR =  abs(numPixelsL - numPixelsR) < 2.0 ? 1.0 : 0.0;
		gl_FragColor = vec4(centerR, centerL , 0.0, 1.0);
	}
	else
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
}
