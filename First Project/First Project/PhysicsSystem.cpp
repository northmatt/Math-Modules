#include "PhysicsSystem.h"

void PhysicsSystem::Init() {
	phyDrawShader.Load("./assets/shader/PhysicsDraw.vert", "./assets/shader/PhysicsDraw.frag");
}

/*void PhysicsSystem::Update(entt::registry* reg) {
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view) {
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		physBod.Update(&trans, Timer::deltaTime);
	}

	Run(reg);
}*/

void PhysicsSystem::Update(entt::registry* reg, b2World& world) {
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view) {
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		physBod.Update(&trans);
	}

	Run(world);
}

void PhysicsSystem::Draw(entt::registry* reg) {
	auto view = reg->view<PhysicsBody, Transform>();
	auto& cam = reg->get<Camera>(EntityIdentifier::MainCamera());

	if (PhysicsBody::GetDraw())
		for (auto entity : view) {
			auto& physBody = view.get<PhysicsBody>(entity);
			auto& trans = view.get<Transform>(entity);

			Transform temp = trans;
			temp.SetScale(vec3(physBody.GetWidth(), physBody.GetHeight(), 1.f));
			temp.SetPosition(temp.GetPosition() + vec3(physBody.GetCenterOffset().x, physBody.GetCenterOffset().y, 0.f));
			temp.SetPositionZ(100.f);

			temp.Update();

			std::string fileName = "Masks/";
			if (physBody.GetBodyType() == BodyType::BOX) {
				fileName += "SquareMask.png";
			} else if (physBody.GetBodyType() == BodyType::CIRCLE) {
				fileName += "CircleMask.png";
			}

			Texture* mask = TextureManager::FindTexture(fileName);

			phyDrawShader.Bind();

			phyDrawShader.SendUniform("uView", cam.GetView());
			phyDrawShader.SendUniform("uProj", cam.GetProjection());
			phyDrawShader.SendUniform("uModel", temp.GetLocalToWorldMatrix());
			phyDrawShader.SendUniform("uColor", vec4(1.f, 0.f, 0.f, 0.3f));

			mask->Bind();

			physBody.DrawBody();

			mask->Unbind(0);
			phyDrawShader.Unbind();
		}
}

void PhysicsSystem::Run(b2World& world) {
	float32 timeStep = 1.f / 60.f;

	int32 velInt = 8;
	int32 posInt = 3;

	world.Step(timeStep, velInt, posInt);
}

/*void PhysicsSystem::Run(entt::registry* reg) {
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view) {
		auto& trans1 = view.get<Transform>(entity);
		auto& body1 = view.get<PhysicsBody>(entity);

		Circle worldPosC1;
		Box worldPosB1;

		switch (body1.GetBodyType()) {
		case BodyType::BOX:
			worldPosB1.m_center = trans1.GetPosition() + vec3(body1.GetCenterOffset().x, body1.GetCenterOffset().y, 0.f);
			worldPosB1.m_bottomLeft = trans1.GetPosition() + vec3(body1.GetBottomLeft().x, body1.GetBottomLeft().y, 0.f);
			worldPosB1.m_bottomRight = trans1.GetPosition() + vec3(body1.GetBottomRight().x, body1.GetBottomRight().y, 0.f);
			worldPosB1.m_topLeft = trans1.GetPosition() + vec3(body1.GetTopLeft().x, body1.GetTopLeft().y, 0.f);
			worldPosB1.m_topRight = trans1.GetPosition() + vec3(body1.GetTopRight().x, body1.GetTopRight().y, 0.f);
			break;
		case BodyType::CIRCLE:
			worldPosC1.m_center = trans1.GetPosition() + vec3(body1.GetCenterOffset().x, body1.GetCenterOffset().y, 0.f);
			worldPosC1.m_radius = body1.GetRadius();
			break;
		default:
			break;
		}

		if (body1.GetDynamic()) {
			for (auto entity2 : view) {
				if (entity != entity2) {
					auto& trans2 = view.get<Transform>(entity2);
					auto& body2 = view.get<PhysicsBody>(entity2);

					Circle worldPosC2;
					Box worldPosB2;

					switch (body2.GetBodyType()) {
					case BodyType::BOX:
						worldPosB2.m_center = trans2.GetPosition() + vec3(body2.GetCenterOffset().x, body2.GetCenterOffset().y, 0.f);
						worldPosB2.m_bottomLeft = trans2.GetPosition() + vec3(body2.GetBottomLeft().x, body2.GetBottomLeft().y, 0.f);
						worldPosB2.m_bottomRight = trans2.GetPosition() + vec3(body2.GetBottomRight().x, body2.GetBottomRight().y, 0.f);
						worldPosB2.m_topLeft = trans2.GetPosition() + vec3(body2.GetTopLeft().x, body2.GetTopLeft().y, 0.f);
						worldPosB2.m_topRight = trans2.GetPosition() + vec3(body2.GetTopRight().x, body2.GetTopRight().y, 0.f);
						break;
					case BodyType::CIRCLE:
						worldPosC2.m_center = trans2.GetPosition() + vec3(body2.GetCenterOffset().x, body2.GetCenterOffset().y, 0.f);
						worldPosC2.m_radius = body2.GetRadius();
						break;
					default:
						break;
					}

					if (BoxBoxCollision(std::pair<PhysicsBody&, Box>(body1, worldPosB1), std::pair<PhysicsBody&, Box>(body2, worldPosB2))) {
						trans1.SetPosition(trans1.GetPosition() - body1.GetVelocity() * Timer::deltaTime);

						body1.SetAcceleration(vec3(0.f, 0.f, 0.f));
						body1.SetVelocity(vec3(0.f, 0.f, 0.f));
					}
				}
			}
		}
	}
}*/

bool PhysicsSystem::BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2) {
	if (group1.first.GetCollideID() & group2.first.GetBodyID()) {
		bool axisXCollide = group1.second.m_bottomRight.x >= group2.second.m_bottomLeft.x && group2.second.m_bottomRight.x >= group1.second.m_bottomLeft.x;
		bool axisYCollide = group1.second.m_topLeft.y >= group2.second.m_bottomLeft.y && group2.second.m_topLeft.y >= group1.second.m_bottomLeft.y;

		return axisXCollide && axisYCollide;
	} else
		return false;
}
