#version 120
#extension GL_EXT_geometry_shader4 : enable

vec4 RotateVector(vec4 vector, float angle)
{
	vec4 result = vector;
	result.x = vector.x * cos(angle) - vector.y * sin(angle);
	result.y = vector.x * sin(angle) + vector.y * cos(angle);

	return result;
}

vec4 ApplyModelViewProjectionMatrix(vec4 vertex)
{
	return vertex * gl_ModelViewProjectionMatrix;
}

void main()
{
	vec4 start = gl_PositionIn[0];
	vec4 end = gl_PositionIn[1];

	// Initial line
	gl_Position = ApplyModelViewProjectionMatrix(start);
	EmitVertex();

	gl_Position = ApplyModelViewProjectionMatrix(end);
	EmitVertex();

	EndPrimitive();

	// Arrow endings
	vec4 invertedArrowVector = start - end;
	float endingLength = length(invertedArrowVector) * 0.1;

	vec4 leftEndingVector = normalize(RotateVector(invertedArrowVector, radians(-15.0))) * endingLength;
	vec4 rightEndingVector = normalize(RotateVector(invertedArrowVector, radians(15.0))) * endingLength;

	gl_Position = ApplyModelViewProjectionMatrix(end + leftEndingVector);
	EmitVertex();

	gl_Position = ApplyModelViewProjectionMatrix(end);
	EmitVertex();

	gl_Position = ApplyModelViewProjectionMatrix(end + rightEndingVector);
	EmitVertex();

	EndPrimitive();
}
