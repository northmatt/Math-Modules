#include "PhysicsBody.h"

unsigned int CollisionIDs::m_playerID		=0x1;
unsigned int CollisionIDs::m_environmentID	=0x10;
unsigned int CollisionIDs::m_enemyID		=0x100;

unsigned int CollisionIDs::Player() {
	return m_playerID;
}

unsigned int CollisionIDs::Environment() {
	return m_environmentID;
}

unsigned int CollisionIDs::Enemy() {
	return m_enemyID;
}

vec3 PhysicsBody::m_gravityAcceleration = vec3(0.f, 35.f, 0.f);

PhysicsBody::PhysicsBody(vec2 botLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic) {
	m_bodyType = BodyType::BOX;

	m_bottomLeft = botLeft;
	m_topLeft = vec2(botLeft.x, topRight.y);
	m_topRight = topRight;
	m_bottomRight = vec2(topRight.x, botLeft.y);

	m_width = m_bottomRight.x - m_bottomLeft.x;
	m_height = m_topLeft.y - m_bottomLeft.y;

	m_centerOffset = centerOffset;
	m_bodyID = objectSpecifier;
	m_collideID = collidesWith;
	m_dynamic = isDynamic;
}

PhysicsBody::PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic) {
	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(m_centerOffset.x - width / 2.f, m_centerOffset.y - height / 2.f);
	m_bottomRight = vec2(m_centerOffset.x + width / 2.f, m_centerOffset.y - height / 2.f);
	m_topLeft = vec2(m_centerOffset.x - width / 2.f, m_centerOffset.y + height / 2.f);
	m_topRight = vec2(m_centerOffset.x + width / 2.f, m_centerOffset.y + height / 2.f);

	m_bodyID = objectSpecifier;
	m_collideID = collidesWith;
	m_dynamic = isDynamic;
}

PhysicsBody::PhysicsBody(float radius, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic) {
	m_bodyType = BodyType::CIRCLE;

	m_radius = radius;
	m_centerOffset = centerOffset;

	m_bodyID = objectSpecifier;
	m_collideID = collidesWith;
	
	m_dynamic = isDynamic;
}

void PhysicsBody::Update(Transform* trans, float dt) {
	vec3 transPos = trans->GetPosition();

	if (m_velocity.GetMagnitude() > 0.f) {
		if (m_applyGravity) {
			m_frictionForce = vec3(-m_velocity.x, 0, 0) * m_friction;
		} else {
			m_frictionForce = -m_velocity * m_friction;
		}

		m_netForce = m_appliedForce + m_frictionForce;

		m_acceleration = m_netForce / m_mass;

		if (m_applyGravity) {
			if (m_dynamic) {
				m_acceleration = m_acceleration + (m_gravityAcceleration * m_mass);
			}
		}

		m_frictionForce = vec3(0.f, 0.f, 0.f);
		m_appliedForce = vec3(0.f, 0.f, 0.f);

		float tempX = m_velocity.x;
		float tempY = m_velocity.y;

		m_velocity = m_velocity + m_acceleration * dt;

		if (abs(m_velocity.x) > abs(m_maxVelo))
			m_velocity.x = tempX;
		if (abs(m_velocity.y) > abs(m_maxVelo))
			m_velocity.y = tempY;

		transPos = transPos + m_velocity * dt;
		trans->SetPosition(transPos);
	}
}

void PhysicsBody::ApplyForce(vec3 force) {
	m_appliedForce = m_appliedForce + force;
}
