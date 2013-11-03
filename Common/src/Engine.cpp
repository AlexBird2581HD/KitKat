#include <Engine.h> 
#include <stdlib.h> 
#include <FileReader.h>
#include <cmath>
#include <Quad.h>
#include <Shader.h>

#undef isnan
Engine::Engine() 
{ 
  Scale = blackBarH = blackBarV = 0;
  x = y = 0;

  velx = -5;
  vely = 5;
} 
  
Engine::~Engine() 
{ 
  
} 
  
void Engine::Update() 
{ 
	sine+=0.01f;
	Quad1->rotate(sine);
	Quad1->move(std::sin(-sine*3.5f)*320+512,std::cos(-sine*3.5f)*320+(-384));
	Quad1->resize(128+std::sin(sine)*128,128+std::sin(sine)*128);

	Quad3->move(Quad3->getX() + velx, Quad3->getY() + vely);

	if (Quad3->getY() > height/2 - 200)
		vely = -vely;
	if (Quad3->getY() < -height)
		vely = -vely;

	if (Quad3->getX() > width)
		velx = -velx;
	if (Quad3->getX() < -width/2 + 200)
		velx = -velx;


}

void Engine::fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height)
{
	this->width = width;
	this->height = height;

	//Calculate desired Aspect Ratio
	float dAR =  desiredWidth/ desiredHeight;

	//Calculate real Aspect Ratio
	float rAR = width/height;
	float w,h;
	//Check Aspect Ratio's
	if(dAR==rAR)
	{
		//Same aspect, no letterboxing needed!
		Scale = width/desiredWidth;
	}
	else if(dAR<rAR)
	{
		//Horizontal letterboxing needed!
		Scale = height/desiredHeight;
		blackBarH = (width-Scale*desiredWidth)/2;
		
	}
	else
	{
		//Vertical letterboxing needed!
		Scale = width/desiredWidth;
		blackBarV = (height-(Scale*desiredHeight))/2;
	}
	 w = desiredWidth*Scale;
	 h = desiredHeight*Scale;

	glViewport((int)blackBarH, (int)blackBarV,(int)w,(int)h); // Sets up the OpenGL viewport

	GLubyte* pixels;
	
	KitKat::FileReader *FR = new KitKat::FileReader("testi.tga");
	
	unsigned char*buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);

	FR->FileSeek(12,0);
	FR->ReadBytes(4,buffer);
	int sizex= buffer[0]+buffer[1]*256;
	int sizey= buffer[2]+buffer[3]*256;
	free(buffer);
	
	buffer = (unsigned char*)malloc(sizeof(unsigned char)*1);
	FR->FileSeek(16,0);
	FR->ReadBytes(1,buffer);
	int bpp = buffer[0];
	free(buffer);
	
	int datasize = sizex*sizey*bpp/8;
	pixels = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	unsigned char *Buffer = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	
	FR->FileSeek(18,0);
	FR->ReadBytes(datasize,Buffer);	
	for(int i = 0;i<datasize;i+=4)
	{
		pixels[i+0] = Buffer[i+2];
		pixels[i+1] = Buffer[i+1];
		pixels[i+2] = Buffer[i+0];
		pixels[i+3] = Buffer[i+3];
	}
	delete FR;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&Texture);
	glActiveTexture(GL_TEXTURE0);


    glBindTexture(GL_TEXTURE_2D, Texture);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	
	GLfloat Projection[16] ={
	 1.0f/1024.0f, 0,	0,	-0.5f
	,0,	1.0f/768.0f,	0,0.5f
	,0,	0,	1,	0
	,0,	0,	0,	1};

	
	Quad::Projection = (float*)calloc(16,sizeof(float));
	Quad::Projection[0] = Projection[0];
	Quad::Projection[1] = Projection[1];
	Quad::Projection[2] = Projection[2];
	Quad::Projection[3] = Projection[3];
	Quad::Projection[4] = Projection[4];
	Quad::Projection[5] = Projection[5];
	Quad::Projection[6] = Projection[6];
	Quad::Projection[7] = Projection[7];
	Quad::Projection[8] = Projection[8];
	Quad::Projection[9] = Projection[9];
	Quad::Projection[10] = Projection[10];
	Quad::Projection[11] = Projection[11];
	Quad::Projection[12] = Projection[12];
	Quad::Projection[13] = Projection[13];
	Quad::Projection[14] = Projection[14];
	Quad::Projection[15] = Projection[15];

	Shader* S = new Shader();

	Quad1 = new Quad(128,128,512,-384);
	Quad1->setShader(S);
	Quad1->setTexture(Texture);

	Quad2 = new Quad(300,300,250,-250);
	Quad2->setShader(S);
	Quad2->setTexture(Texture);

	Quad3 = new Quad(100, 100, 0, 0);
	Quad3->setShader(S);
	Quad3->setTexture(Texture);

	sine = 0;
 }


void Engine::Draw() 
{ 
    //Draw 
    glClearColor((std::sin(-sine*3)+1)/2,(std::sin(sine*4)+1) / 2,(std::sin(sine*5)+1)/2,1); 
    #ifndef ANDROID_FRAMEWORK 
    glClearDepth(1); 
    #else 
    glClearDepthf(1); 
    #endif 

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

	Quad2->Draw(0.6f);
	Quad1->Draw(0.3f);
	Quad3->Draw(0.45f);
	
}
