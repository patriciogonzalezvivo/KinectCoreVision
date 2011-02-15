	void main(void)
	{
	
		//increment variable
		int i;

		//Pass-thru!
		for(i=0; i< gl_VerticesIn; i++){
			
			gl_Position = gl_PositionIn[i];
			EmitVertex();
		}
		EndPrimitive();																						
	}
