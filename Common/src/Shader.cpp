#include <Shader.h>
#include <Debug.h>
#include <FileReader.h>

#include <fstream>
#include <cassert>

using namespace KitKat;

Shader::Shader(const std::string& vertex, const std::string& fragment, bool loadFromFile)
{
	if(!loadFromFile)
	{
		create(vertex, fragment);
		return;
	}

	FileReader vertexFile(vertex.c_str());
	FileReader fragmentFile(fragment.c_str());

	std::string vertexCode = vertexFile.ReadFile();
	std::string fragmentCode = fragmentFile.ReadFile();
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

GLint Shader::getAttribLocation(const std::string& name)
{
	GLint location = glGetAttribLocation(_program, name.c_str());
	checkGlError("glGetAttribLocation");
	return location;
}

GLint Shader::getUniformLocation(const std::string& name)
{
	GLint location = glGetUniformLocation(_program, name.c_str());
	checkGlError("glGetUniformLocation");
	return location;
}

//void Shader::setUniform(const std::string& name, devmath::Matrix4 matrix)
void Shader::setUniform(const std::string& name, float* matrixArray)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, matrixArray);
	checkGlError("glUniformMatrix4fv");
}

void Shader::use()
{
	glUseProgram(_program);
	checkGlError("glUseProgram");
}


// Private

void Shader::create(const std::string& vertexCode, const std::string& fragmentCode)
{
	createProgram();
	checkGlError("createProgram");

	_vertexShader = createShader(GL_VERTEX_SHADER, vertexCode);
	_fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentCode);

	linkProgram();
	checkGlError("linkProgram");
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
	checkGlError("glLinkProgram");

	GLint link = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &link);
	checkGlError("glGetProgramiv_link");
	if(link == GL_FALSE)
	{
		char log[1024];
		glGetProgramInfoLog(_program, 1024, 0, log);
		checkGlError("glGetProgramInfoLog_link");
		LOGE("%s", log); // Stupid android
	}
	checkGlError("linkkaus");
}

GLuint Shader::createShader(const GLenum shaderType, const std::string& code)
{
	GLuint shader = glCreateShader(shaderType);

	compileShader(shader, code.c_str());
	checkGlError("compileShader");
	attachShader(shader);
	checkGlError("attachShader");
	
	return shader;
}

void Shader::compileShader(const GLuint shader, const char* code)
{
	// Takes one string(second parameter)
	// and assumes strings are null terminated(last parameter)
	glShaderSource(shader, 1, &code, NULL);
	checkGlError("glShaderSource");
	glCompileShader(shader);
	checkGlError("glCompileShader");

	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	checkGlError("glGetShaderiv");


	if(compiled == GL_FALSE)
	{
		LOGE("Shader compilation failed");
		char log[1024];
		glGetShaderInfoLog(shader, 1024, 0, log);
		LOGE("%s", log); // Again, stupid android
		//destroy(); // Remove everything just in case
		assert(false);
	}
}

void Shader::attachShader(const GLuint shader)
{
	glAttachShader(_program, shader);
	checkGlError("glAttachShader");
}