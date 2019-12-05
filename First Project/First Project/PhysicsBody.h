#pragma once

#include <GL/glew.h>
#include <Box2D/Box2D.h>
#include "JSON.h"
#include "Vector.h"
#include "VertexManager.h"
#include "EntityIdentifier.h"
#include "Transform.h"

enum class BodyType {
	BOX,
	CIRCLE,

	NUM_TYPES
};

struct CollisionIDs {
public:
	static unsigned int Player();
	static unsigned int Environment();
	static unsigned int Enemy();
private:
	static unsigned int m_playerID;
	static unsigned int m_environmentID;
	static unsigned int m_enemyID;
};

class PhysicsBody {
public:
	PhysicsBody() {}

	PhysicsBody(b2Body* body, float radius, vec2 centerOffset, bool isDynamic);
	PhysicsBody(b2Body* body, float width, float height, vec2 centerOffset, bool isDynamic);

	void Update(Transform* trans);

	//The bottom/top corner of the physics body, relative to the sprite
	//object specifier is the collision ID object that the physics body is attached to
	//collidesWith is the ID(s) of the object(s) that this physics body will actually collide with (use | to combine 2+)
	//isDynamic = is object moving {only objects that move actually need to check collisions with the other objects}
	/*PhysicsBody(vec2 botLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float radius, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);

	void Update(Transform* trans, float dt);*/

	void ApplyForce(vec3 force);

	void InitBody();
	void DrawBody();


	vec3 GetAppliedForce() const { return m_appliedForce; }
	vec3 GetFrictionForce() const { return m_frictionForce; }
	vec3 GetNetForce() const { return m_netForce; }
	vec3 GetAcceleration() const { return m_acceleration; }
	//max vel per axis
	float GetMaxVelo() const { return m_maxVelo; }
	vec3 GetVelocity() const { return m_velocity; }

	float GetFriction() const { return m_friction; }
	static vec3 GetGravityAcceleration() { return m_gravityAcceleration; }
	bool GetApplyGravity() const { return m_applyGravity; }

	float GetMass() const { return m_mass; }

	BodyType GetBodyType() const { return m_bodyType; }
	vec2 GetCenterOffset() const { return m_centerOffset; }
	vec2 GetBottomLeft() const { return m_bottomLeft; }
	vec2 GetBottomRight() const { return m_bottomRight; }
	vec2 GetTopLeft() const { return m_topLeft; }
	vec2 GetTopRight() const { return m_topRight; }
	float GetWidth() const { return m_width; }
	float GetHeight() const { return m_height; }

	float GetRadius() const { return m_radius; }

	//type of this physics body
	unsigned int GetBodyID() const { return m_bodyID; }
	//types of bodies this body collides with
	unsigned int GetCollideID() const { return m_collideID; }

	//is object moving
	bool GetDynamic() const { return m_dynamic; }

	static bool GetDraw() { return m_drawBodies; }

	b2Body* GetBody() { return m_body; }
	b2Vec2 GetPosition() const { return m_position; }



	void SetAppliedForce(vec3 _appForce) { m_appliedForce = _appForce; }
	void SetFrictionForce(vec3 _fricForce) { m_frictionForce = _fricForce; }
	void SetNetForce(vec3 _netForce) { m_netForce = _netForce; }
	void SetAcceleration(vec3 _accel) { m_acceleration = _accel; }
	//max vel per axis
	void SetMaxVelo(float _maxVelo) { m_maxVelo = _maxVelo; }
	void SetVelocity(vec3 _vel) { m_velocity = _vel; }

	void SetFriction(float _fric) { m_friction = _fric; }
	static void SetGravityAcceleration(vec3 _grav) { m_gravityAcceleration = _grav; }
	void SetApplyGravity(bool _appGrav) { m_applyGravity = _appGrav; }

	void SetMass(float _mass) { m_mass = _mass; }

	void SetBodyType(BodyType _bodTyp) { m_bodyType = _bodTyp; }
	void SetCenterOffset(vec2 _cenOff) { m_centerOffset = _cenOff; }
	void SetBottomLeft(vec2 _botLef) { m_bottomLeft = _botLef; }
	void SetBottomRight(vec2 _botRig) { m_bottomRight = _botRig; }
	void SetTopLeft(vec2 _topLef) { m_topLeft = _topLef; }
	void SetTopRight(vec2 _topRig) { m_topRight = _topRig; }
	void SetWidth(float _width) { m_width = _width; }
	void SetHeight(float _height) { m_height = _height; }

	void SetRadius(float _rad) { m_radius = _rad; }

	//type of this physics body
	void SetBodyID(unsigned int _bodyID) { m_bodyID = _bodyID; }
	//types of bodies this body collides with
	void SetCollideID(unsigned int _collideID) { m_collideID = _collideID; }

	//is object moving
	void SetDynamic(bool _dynamic) { m_dynamic = _dynamic; }

	static void SetDraw(bool drawBodies) { m_drawBodies = drawBodies; }

	void SetBody(b2Body* body) { m_body = body; }
	void SetPosition(b2Vec2 bodyPos) { m_position = bodyPos; }
private:
	b2Body* m_body = nullptr;
	b2Vec2 m_position = b2Vec2(0.f, 0.f);

	vec3 m_appliedForce = vec3(0.f, 0.f, 0.f);
	vec3 m_frictionForce = vec3(0.f, 0.f, 0.f);
	vec3 m_netForce = vec3(0.f, 0.f, 0.f);
	vec3 m_acceleration = vec3(0.f, 0.f, 0.f);
	//max vel per axis
	float m_maxVelo = 20.f;
	vec3 m_velocity = vec3(0.f, 0.f, 0.f);

	float m_friction = 0.35f;
	static vec3 m_gravityAcceleration;
	bool m_applyGravity = false;

	float m_mass = 1.f;

	BodyType m_bodyType = BodyType::CIRCLE;
	vec2 m_centerOffset = vec2();
	vec2 m_bottomLeft = vec2();
	vec2 m_bottomRight = vec2();
	vec2 m_topLeft = vec2();
	vec2 m_topRight = vec2();
	float m_width = 0.f;
	float m_height = 0.f;

	float m_radius = 0.f;

	//type of this physics body
	unsigned int m_bodyID;
	//types of bodies this body collides with
	unsigned int m_collideID;

	//is object moving
	bool m_dynamic = false;

	static bool m_drawBodies;
	GLuint m_vao = GL_NONE;
	GLuint m_vboPos = GL_NONE;
};

inline void to_json(nlohmann::json& j, const PhysicsBody& phys) {
	j["BodyPos"] = { phys.GetPosition().x, phys.GetPosition().y };
	j["BodyType"] = phys.GetBodyType();

	j["MaxVelo"] = phys.GetMaxVelo();
	
	j["Friction"] = phys.GetFriction();
	j["Gravity"] = { phys.GetGravityAcceleration().x, phys.GetGravityAcceleration().y, phys.GetGravityAcceleration().z };
	j["ApplyGravity"] = phys.GetApplyGravity();
	
	j["Mass"] = phys.GetMass();
	
	j["BodyType"] = phys.GetBodyType();
	j["CenterOffset"] = { phys.GetCenterOffset().x, phys.GetCenterOffset().y };
	j["BottomLeft"] = { phys.GetBottomLeft().x, phys.GetCenterOffset().y };
	j["BottomRight"] = { phys.GetBottomRight().x, phys.GetBottomRight().y };
	j["TopLeft"] = { phys.GetTopLeft().x, phys.GetTopLeft().y };
	j["TopRight"] = { phys.GetTopRight().x, phys.GetTopRight().y };
	j["Width"] = phys.GetWidth();
	j["Height"] = phys.GetHeight();
	
	j["Radius"] = phys.GetRadius();
	

	j["BodyID"] = phys.GetBodyID();
	j["CollideID"] = phys.GetCollideID();
	

	j["Dynamic"] = phys.GetDynamic();
}

inline void from_json(const nlohmann::json& j, PhysicsBody& phys) {
	phys.SetPosition(b2Vec2(float32(j["BodyPos"][0]), float32(j["BodyPos"][1])));
	phys.SetBodyType(j["BodyType"]);

	phys.SetMaxVelo(j["MaxVelo"]);

	phys.SetFriction(j["Friction"]);
	phys.SetGravityAcceleration(vec3(j["Gravity"][0], j["Gravity"][1], j["Gravity"][2]));
	phys.SetApplyGravity(j["ApplyGravity"]);

	phys.SetMass(j["Mass"]);

	phys.SetBodyType(j["BodyType"]);
	phys.SetCenterOffset(vec2(j["CenterOffset"][0], j["CenterOffset"][1]));
	phys.SetBottomLeft(vec2(j["BottomLeft"][0], j["BottomLeft"][1]));
	phys.SetBottomRight(vec2(j["BottomRight"][0], j["BottomRight"][1]));
	phys.SetTopLeft(vec2(j["TopLeft"][0], j["TopLeft"][1]));
	phys.SetTopRight(vec2(j["TopRight"][0], j["TopRight"][1]));
	phys.SetWidth(j["Width"]);
	phys.SetHeight(j["Height"]);

	phys.SetRadius(j["Radius"]);


	phys.SetBodyID(j["BodyID"]);
	phys.SetCollideID(j["CollideID"]);


	phys.SetDynamic(j["Dynamic"]);
}