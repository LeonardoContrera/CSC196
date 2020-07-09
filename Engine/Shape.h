#pragma once

#include "core.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Colors.h"
#include "../Engine/Math/Transform.h"
#include <vector>
#include <string>
namespace nc
{
	class Shape
	{
	public:
		Shape() = default;
		
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_points{ points }, m_color{ color }{}
		
		bool Load(const std::string& filename);

		void Draw(Core::Graphics& graphics);
	
		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);
		void Draw(Core::Graphics& graphics, const Transform& transform);
		void SetColor(Color color) { m_color = color; }
			
		const Color& GetColor() const { return m_color; }

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;

	};

}