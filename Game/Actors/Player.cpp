#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Math/Random.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);

		// stream into thrust
		stream >> thrust;
		// stream into rotation rate
		stream >> rotationRate;

		stream.close();
	}

	return success;

}

void Player::Update(float dt)
{
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	nc::Vector2 force{ 0, 0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);
	force = force + nc::Vector2{ 0, 100 };

	velocity = velocity + (force * dt);
	velocity = velocity * 0.99f;

	m_transform.position = m_transform.position + velocity * dt;


	//rotate
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { m_transform.angle = m_transform.angle - (dt * nc::math::DegreesToRadians(360.f)); }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { m_transform.angle = m_transform.angle + (dt * nc::math::DegreesToRadians(360.0f)); }

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;
	
	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::math::PI, 20, 1, nc::Color::yellow, 1, 100, 200);
	}

	m_transform.Update();
}


