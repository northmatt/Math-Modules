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

vec3 PhysicsBody::m_gravityAcceleration = vec3(0.f, -35.f, 0.f);
bool PhysicsBody::m_drawBodies = false;

/*PhysicsBody::PhysicsBody(vec2 botLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic) {
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

	InitBody();
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

	InitBody();
}*/

/*PhysicsBody::PhysicsBody(float radius, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic) {
	m_bodyType = BodyType::CIRCLE;

	m_radius = radius;
	m_centerOffset = centerOffset;

	m_bodyID = objectSpecifier;
	m_collideID = collidesWith;
	
	m_dynamic = isDynamic;

	InitBody();
}

void PhysicsBody::Update(Transform* trans, float dt) {
	vec3 transPos = trans->GetPosition();

	if (m_velocity.GetMagnitude() > 0.f) {
		if (m_applyGravity) {
			m_frictionForce = vec3(-m_velocity.x, 0, 0) * m_friction;
		} else {
			m_frictionForce = -m_velocity * m_friction;
		}
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
}*/

PhysicsBody::PhysicsBody(b2Body* body, float radius, vec2 centerOffset, bool isDynamic) {
	b2CircleShape tempShape;
	tempShape.m_p = b2Vec2(float32(centerOffset.x), float32(centerOffset.y));
	tempShape.m_radius = radius;

	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = 1.f;
	tempFixture.friction = 0.3f;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body = body;
	m_bodyType = BodyType::CIRCLE;

	m_position = m_body->GetPosition();

	m_width = radius * 2.f;
	m_height = radius * 2.f;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(m_centerOffset.x - radius, m_centerOffset.y - radius);
	m_bottomRight = vec2(m_centerOffset.x + radius, m_centerOffset.y - radius);
	m_topLeft = vec2(m_centerOffset.x - radius, m_centerOffset.y + radius);
	m_topRight = vec2(m_centerOffset.x + radius, m_centerOffset.y + radius);
	
	m_dynamic = isDynamic;

	InitBody();
}

PhysicsBody::PhysicsBody(b2Body* body, float width, float height, vec2 centerOffset, bool isDynamic) {
	b2PolygonShape tempShape;
	tempShape.SetAsBox(float32(width / 2.f), float32(height / 2.f), b2Vec2(float32(centerOffset.x), float32(centerOffset.y)), float32(0.f));

	b2FixtureDef tempFixture;
	tempFixture.shape = &tempShape;
	tempFixture.density = 1.f;
	tempFixture.friction = 0.3f;

	m_body = body;
	m_body->CreateFixture(&tempFixture);

	m_body = body;
	m_bodyType = BodyType::CIRCLE;

	m_position = m_body->GetPosition();

	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(m_centerOffset.x - width / 2.f, m_centerOffset.y - height / 2.f);
	m_bottomRight = vec2(m_centerOffset.x + width / 2.f, m_centerOffset.y - height / 2.f);
	m_topLeft = vec2(m_centerOffset.x - width / 2.f, m_centerOffset.y + height / 2.f);
	m_topRight = vec2(m_centerOffset.x + width / 2.f, m_centerOffset.y + height / 2.f);

	m_dynamic = isDynamic;

	InitBody();
}

void PhysicsBody::Update(Transform* trans) {
	m_position = m_body->GetPosition();

	trans->SetPosition(vec3(m_body->GetPosition().x, m_body->GetPosition().y, trans->GetPosition().z));
	trans->SetRotationAngleZ(Degrees(m_body->GetAngle()));
}

void PhysicsBody::ApplyForce(vec3 force) {
	//m_appliedForce = m_appliedForce + force;
	m_body->ApplyForce(b2Vec2(float32(force.x), float32(force.y)), b2Vec2(float32(m_body->GetPosition().x), float32(m_body->GetPosition().y)), true);
}

void PhysicsBody::InitBody() {
	m_vao = VertexManager::CreateVAO();
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);

	m_vboPos = VertexManager::GetPlaneVertVBO();

#pragma warning(push)
#pragma warning(disable : 4312)
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void PhysicsBody::DrawBody() {
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(GL_NONE);
}
