attribute vec2 vPosition;
attribute vec2 vTexCoord;

uniform mat4 mvp;

varying vec2 texCoord;

void main() 
{
	texCoord = vTexCoord;
	//gl_Position = mvp * vec4(vPosition, 1.0);
	gl_Position = vec4(vPosition, 0.0, 1.0);
}