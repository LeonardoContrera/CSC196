// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Shape.h"
#include "Colors.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

//Player player;
//Enemy enemy;
nc::Scene scene;

std::list<nc::Actor*> actors;
float frametime;
float spawntimer{ 0 };



bool Update(float dt)
{
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);


	spawntimer += dt;
	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;

		//add enemy to scene
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(scene.GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		scene.AddActor(enemy);
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{ x, y }, 0, 180, 30, color, 1, 100, 200);

	}

	g_particleSystem.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	scene.Startup();
	g_particleSystem.Startup();

	Player* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);
	
	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		actors.push_back(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	g_particleSystem.ShutDown();
}


