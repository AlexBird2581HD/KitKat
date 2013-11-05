attribute vec3 vPosition;
attribute vec2 vTexCoord;

uniform mat4 Translation;
uniform mat4 Rotation;
uniform mat4 Scale;
uniform mat4 Projection;

varying vec2 texCoord;

void main() 
{
	texCoord = vTexCoord;
	
	vec4 pos;
	pos = vec4(vPosition, 1.0);
	pos *= Scale;
	pos *= Rotation;
	pos *= Translation;
	pos *= Projection;
	gl_Position = pos;
}