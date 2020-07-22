#include "pch.h"
#include "Actor.h"
#include <fstream>
namespace nc
{


    bool nc::Actor::Load(const std::string& filename)
    {
        bool success = false;

        // open stream
        std::ifstream stream(filename);
     // check if stream is open
        if (stream.is_open())
        {
            success = true;

            Load(stream);

            stream.close();
        }

        return success;

    }

    void nc::Actor::Update(float dt)
    {
    }

    void nc::Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, GetTransform());
    }

    void Actor::Load(std::istream& stream)
    {
        stream >> m_transform;

        std::string shapename;
        stream >> shapename;
        m_shape.Load(shapename);
    }

    float Actor::GetRadius()
    {
        return m_shape.GetRadius() * m_transform.scale;
    }

}