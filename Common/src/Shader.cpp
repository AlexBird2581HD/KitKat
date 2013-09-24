#include <Shader.h>
#include <Util.h>
#include <Debug.h>
#include <cassert>

using namespace KitKat;

Shader::Shader(const std::string& vertex, const std::string& fragment, bool loadFromFile)
{
	if(!loadFromFile)
	{
		create(vertex, fragment);
		return;
	}
	std::string vertexCode = Util::ReadFile(vertex);
	std::string fragmentCode = Util::ReadFile(fragment);

	create(vertexCode, fragmentCode);
}
Shader::~Shader()
{
	destroy();
}

// Public

GLuint Shader::program()
{
	return _program;
}

void Shader::use()
{

}

// Private

void Shader::create(const std::string& vertexCode, const std::string& fragmentCode)
{
	createProgram();

	_vertexShader = createShader(GL_VERTEX_SHADER, vertexCode);
	_fragmentShader = createShader(GL_VERTEX_SHADER, fragmentCode);

	linkProgram();
}

void Shader::destroy()
{
	glDeleteShader(_vertexShader);
	checkGlError("glDeleteShader");
	glDeleteShader(_fragmentShader);
	checkGlError("glDeleteShader");
	
	glDeleteProgram(_program);
	checkGlError("glDeleteProgram");
}

void Shader::createProgram()
{
	_program = glCreateProgram();
}

void Shader::linkProgram()
{
	glLinkProgram(_program);
}

GLuint Shader::createShader(const GLenum shaderType, const std::string& code)
{
	GLuint shader = glCreateShader(shaderType);

	compileShader(shader, code.c_str());
	attachShader(shader);
	
	return shader;
}



void Shader::compileShader(const GLuint shader, const char* code)
{
	// Takes one string(second parameter)
	// and assumes strings are null terminated(last parameter)
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	checkGlError("glCompileShader");

	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(compiled == GL_FALSE)
	{
		LOGE("Shader compilation failed");
		destroy(); // Remove everything just in case
		assert(false);
	}
}

void Shader::attachShader(const GLuint shader)
{
	glAttachShader(_program, shader);
	checkGlError("glAttachShader");
}