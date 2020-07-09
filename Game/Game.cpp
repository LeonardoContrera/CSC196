// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Shape.h"
#include "Colors.h"
#include "Math/Transform.h"
#include <iostream>
#include <string>

float speed = 300.0f;
//nc::Vector2 position{ 400, 300 };
std::vector<nc::Vector2> points{ { 0, -3 }, { 3, 0 }, { 3, 2 }, { 2, 2 }, { -2, 2 }, { -3, 2 }, { -3, 0 }, { 0, -3} }
;

nc::Shape ship;

nc::Color color{ 0, 1, 1 };
nc::Transform transform{ {400, 300}, 4, 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	frametime = dt;
	roundTime += dt;
	
	if (roundTime >= 5.0f) gameOver = true;


	if (gameOver) dt = 0;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;

	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();

	nc::Vector2 force{ 0, 0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + direction;


	//rotate
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { transform.angle = transform.angle - (dt * 3.0f); }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { transform.angle = transform.angle + (dt * 3.0f); }

	//position = position + direction * 7.0f;
	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2::left * speed * dt; }
	//If you want to use letters if (Core::Input::IsPressed('A')) { position += nc::Vector2{ -1.0f, 0.0f }; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2::right * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2::down * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2::up * speed; }

	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	//
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime/1000.0f).c_str());


	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	ship.Draw(graphics, transform);
	
}

int main()
{
	DWORD ticks =  GetTickCount();
	std::cout << ticks/1000/60/60 << std::endl;

	ship.Load("ship.txt");
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


