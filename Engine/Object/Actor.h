#pragma once
#include "core.h"
#include "Math/Transform.h"
#include "Shape.h"
#include <string>

namespace nc 
{
	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape }{} // make sure to initialize m_transform and m_shape
		virtual	~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void Load(std::istream& stream);

		virtual void OnCollision(Actor* actor){}

		float GetRadius();

		void SetScene(class Scene* scene) { m_scene = scene; }

		Transform& GetTransform()	// return the transform
		{
			return m_transform;
		}
		Shape& GetShape() // return the shape
		{
			return m_shape;
		}
		void SetDestroy(bool destory = true) { m_destroy = destory; }
		bool IsDestroy() { return m_destroy; }

	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}

