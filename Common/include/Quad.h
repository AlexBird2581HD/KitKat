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
		Quad();
		Quad(float x, float y, float w, float h);
		~Quad();

		void move(float x, float y);
		void resize(float width, float height);
		void rotate(float angle);

		int getX() { return pos.x; }
		int getY() { return pos.y; }
		int getW() { return size.x; }
		int getH() { return size.y; }
		
		void setTexture(Texture* texture);
		static void setProjection(glm::mat4 projection);

		void draw(Shader* shader);
	protected:
		glm::vec2 pos;
		glm::vec2 size;
		float _angle;

		static glm::mat4 _projection;
		glm::mat4 _translation, _rotation, _scale;

		Texture* _tex;
		GLuint _vbo;

		float *Data;
		
		void genBuffer();
	};
}
#endif