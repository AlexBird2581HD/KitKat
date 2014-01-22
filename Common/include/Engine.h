#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <Shader.h>
#include <GameObject.h>

namespace KitKat
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		bool Init(int width, int height);
		void Update(float dt);
		void Draw();		
	private:
		int screenWidth, screenHeight;

		Shader* shader;

		std::vector<GameObject*> enemies;
		std::vector<GameObject*> bullets;
		GameObject* player;

		bool setupGraphics(int width, int height);

		Texture* enemyText;
		Texture* bulletText;

		void collisionCheck();
	};
}
#endif