#include "Challenge.h"

Challenge::Challenge(std::string name) : Scene(name) {
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Challenge::InitScene(float windowWidth, float windowHeight) {
	//Dynamically allocates register
	m_sceneReg = new entt::registry;

	//attach register
	ECS::AttachRegister(m_sceneReg);

	std::cout << "Press R to change rotation";

	//camera
	{
		//aspect ratio
		float aspectRatio = windowWidth / windowHeight;

		//create camera entity
		auto entity = ECS::CreateEntity();

		//create orthorgraphic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(windowWidth, windowHeight));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100, 100);

		//attaches cam to vertical scroll
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(15.f);
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffset(15.f);

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::VertScrollCameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Scrolling Camera");
		ECS::SetIsMainCamera(entity, true);
	}
	//background
	{
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//sets up components
		std::string fileName = "Background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 500, 224);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, 80.f, 0.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhiBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX{ 0.f };
		float shrinkY{ tempSpr.GetHeight() / 1.5f };

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(0.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhiBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()) - shrinkX, float(tempSpr.GetHeight()) - shrinkY, 
			vec2(0.f, (-tempSpr.GetHeight() / 16.f) * 8.5f), false);

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Background");
	}

	createCrate(50.f, -73.f, true);
	createCrate(-50.f, -73.f, false);
	createCrate(-30.f, -73.f, false);
	createCrate(-10.f, -73.f, false);
	createCrate(-40.f, -57.f, false);
	createCrate(-20.f, -57.f, false);
	createCrate(-30.f, -41.f, false);

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

void Challenge::SetAnim(int anim) {
	auto& animController = m_sceneReg->get<AnimationController>(EntityIdentifier::MainPlayer());
	animController.SetActiveAnim(anim);
}

int Challenge::GetAnim() {
	auto& animController = m_sceneReg->get<AnimationController>(EntityIdentifier::MainPlayer());
	return animController.GetActiveAnim();
}

unsigned int Challenge::GetAutoLink() {
	return autoLinkEnt;
}

void Challenge::createCrate(float32 posX, float32 posY, bool isMain) {
	auto entity = ECS::CreateEntity();

	//add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

	//sets up components
	std::string fileName = "Crate.png";

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 15, 15);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhiBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(float32(posX), float32(posY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhiBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()) - shrinkX, float(tempSpr.GetHeight()) - shrinkY,
		vec2(0.f, 0.f), false);

	tempPhiBody.SetFriction(0.15f);
	tempPhiBody.SetMaxVelo(60.f);
	tempPhiBody.SetApplyGravity(true);

	//set up identitier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	if (isMain) {
		ECS::SetUpIdentifier(entity, bitHolder, "Main Pyrmid Crate");
		ECS::SetIsMainPlayer(entity, true);
	} else {
		ECS::SetUpIdentifier(entity, bitHolder, "Pyrmid Crate");
	}
		

}
