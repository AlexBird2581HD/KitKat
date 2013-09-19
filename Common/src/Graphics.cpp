#include <Graphics.h>
#include <Debug.h>
#include <stdlib.h> // malloc and free

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

// Public
bool Graphics::Init(int width, int height)
{
	if(!setupGraphics(width, height))
		return false;
	bindVertices();
	return true;
}

void Graphics::Draw()
{
	clear();
	// Draw the stuff from the VBO(Position, Size, Type, Normal, Size of one point(x+y), pointer to array(comes from VBO)
	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), NULL);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}

// Private

// Place holder shaders for now
// TODO: Implement shader loading from file
static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

bool Graphics::setupGraphics(int width, int height)
{
	printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

	LOGI("setupGraphics(%d, %d)", width, height);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

	glViewport(0, 0, width, height);
    checkGlError("glViewport");

	glUseProgram(gProgram);
    checkGlError("glUseProgram");

	glGenBuffers(1, &VBO); // Create the VBO
	checkGlError("glGenBuffers");

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	checkGlError("glClearColor");
    return true;
}

void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkGlError("glClear");
}

void Graphics::bindVertices()
{
	static const GLfloat gTriangleVertices[] =
						{ 0.0f, 0.5f,
						-0.5f, -0.5f,
						0.5f, -0.5f };

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Make VBO active
    checkGlError("glBindBuffer");
	glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_DYNAMIC_DRAW);
    checkGlError("glBufferData");
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Data has changed
    checkGlError("glBindBuffer");
}

// Load different shaders
GLuint Graphics::loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

// Create shader program form vertex and framgen shaders
GLuint Graphics::createProgram(const char* pVertexSource, const char* pFragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}