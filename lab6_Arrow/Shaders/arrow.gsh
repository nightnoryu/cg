#version 120
#extension GL_EXT_geometry_shader4 : enable

vec4 RotateVector(vec4 vector, float angle)
{
	vec4 result = vector;
	result.x = vector.x * cos(angle) - vector.y * sin(angle);
	result.y = vector.x * sin(angle) + vector.y * cos(angle);

	return result;
}

vec4 TruncateVector(vec4 vector, float length)
{
	return normalize(vector) * length;
}

void main()
{
	vec4 start = gl_PositionIn[0];
	vec4 end = gl_PositionIn[1];

	// Initial line
	gl_Position = start;
	EmitVertex();

	gl_Position = end;
	EmitVertex();

	EndPrimitive();

	// Arrow ending
	vec4 invertedArrowVector = start - end;
	float endingsLength = length(invertedArrowVector) * 0.1;

	vec4 leftEndingVector = normalize(RotateVector(start - end, radians(-15.0))) * 0.2;
	vec4 rightEndingVector = normalize(RotateVector(start - end, radians(15.0))) * 0.2;
	
	gl_Position = end + leftEndingVector;
	EmitVertex();

	gl_Position = end;
	EmitVertex();

	gl_Position = end + rightEndingVector;
	EmitVertex();

	EndPrimitive();
}
