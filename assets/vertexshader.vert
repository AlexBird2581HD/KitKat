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
	
	gl_Position = vec4(vPosition, 1.0);
	gl_Position *= Scale;
	gl_Position *= Rotation;
	gl_Position *= Translation;
	gl_Position *= Projection;
}