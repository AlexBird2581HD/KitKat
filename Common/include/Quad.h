#ifndef QUAD_H
#define QUAD_H

#include <Shader.h>
#include <Texture.h>

#include <glm/glm.hpp>

namespace KitKat
{
	class Quad
	{
	public:
		Quad(int x, int y, float w, float h);
		~Quad();

		void move(int x, int y);
		void resize(float width, float height);
		void rotate(float angle);

		int getX() { return _x; }
		int getY() { return _y; }
		int getW() { return _w; }
		int getH() { return _h; }
		
		void setTexture(Texture* texture);
		static void setProjection(glm::mat4 projection);

		void draw(Shader* shader);
	private:
		int _x, _y;
		int _w, _h;
		int _angle;

		static glm::mat4 _projection;
		glm::mat4 _translation, _rotation, _scale;

		Texture* _tex;
		GLuint _vbo;

		float *Data;
		
		void genBuffer();
	};
}
#endif