#pragma once

#include "ECS.h"
#include "PhysicsBody.h"
#include "Timer.h"
#include "Shader.h"

struct Box {
public:
	vec3 m_bottomLeft;
	vec3 m_bottomRight;
	vec3 m_topLeft;
	vec3 m_topRight;
	vec3 m_center;
};

struct Circle {
public:
	vec3 m_center;
	float m_radius;
};

namespace PhysicsSystem {
	static Shader phyDrawShader;

	void Init();

	//void Update(entt::registry* reg);
	void Update(entt::registry* reg, b2World& world);

	void Draw(entt::registry* reg);

	void Run(b2World& world);

	//run our collision detection
	//includes:
	//Box-circle
	//box-box
	//void Run(entt::registry* reg);

	bool BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2);
}