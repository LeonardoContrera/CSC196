#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
    bool success = false;

    std::ifstream stream(filename);
    if (stream.is_open())
    {
        success = true;

        // load the base actor members
        Actor::Load(stream);

        // stream into thrust
        stream >> m_thrust;

        stream.close();
    }

    return success;

}

void Enemy::Update(float dt)
{
    nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
    m_transform.angle = std::atan2(direction.y, direction.x) + nc::math::DegreesToRadians(90.0f);
    nc::Vector2 enemyVelocity = direction.Normalized() * 0;
    GetTransform().position = GetTransform().position + enemyVelocity * dt;


    m_transform.Update();


}

void Enemy::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PROJECTILE)
    {
        m_destroy = true;

        nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
        nc::Color color = colors[rand() % 3];
        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
    }
}

