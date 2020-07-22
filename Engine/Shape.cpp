#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
#include <fstream>

bool nc::Shape::Load(const std::string& filename)
{
    bool success = false;
	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> m_color;

		// read in number of points in shape
		std::string line;
		std::getline(stream, line);
		size_t size = stoi(line);

		for (size_t i = 0; i < size; i++)
		{
			Vector2 point;
			stream >> point;

			m_points.push_back(point);
		}


		stream.close();
	}

	// get radius
	for (size_t i = 0; i < m_points.size(); i++)
	{
		nc::Vector2 p1 = m_points[i];
		float length = p1.Length();
		if (length > m_radius) m_radius = length;
	}

    return success;
}


void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);

	nc::Matrix33 mxs;

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{


		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		//transform 
		//scale/rotate/translate
		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;



		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

