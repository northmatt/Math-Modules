#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string name) : Scene(name)
{
}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates register
	m_sceneReg = new entt::registry;

	//attach register
	ECS::AttachRegister(m_sceneReg);

	//aspect ratio
	float aspectRatio = windowWidth / windowHeight;
	//camera
	{
		//create camera entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		//create orthorgraphic camera
		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(windowWidth, windowHeight));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100, 100);

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}
	//healthbar
	{
		//create HealthBar entity
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Healthbar Entity");
	}
	//helloWorld sign
	{
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 50);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -25.f, 0.f));

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Hello World Sign");
	}
	//link Sprite
	{
		auto attacks = File::LoadJSON("LinkAttacks.json");

		auto entity = ECS::CreateEntity();
		m_linkEntity = entity;

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "spritesheets/LinkAttacks.png";
		auto &animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		
		//Add anims
		animController.AddAnimation(attacks["left"]);
		animController.AddAnimation(attacks["right"]);
		
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 100, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "link");
	}
	//sprite 2
	/*
	{
		auto attacks = File::LoadJSON("LinkAttacks.json");

		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "spritesheets/LinkAttacks.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//Add first anim
		animController.AddAnimation(Animation());
		//get first anim
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(1.f, 65.f), vec2(65.f, 1.f));
		anim.AddFrame(vec2(67.f, 65.f), vec2(131.f, 1.f));
		anim.AddFrame(vec2(133.f, 65.f), vec2(197.f, 1.f));
		anim.AddFrame(vec2(199.f, 65.f), vec2(263.f, 1.f));
		anim.AddFrame(vec2(265.f, 65.f), vec2(329.f, 1.f));
		anim.AddFrame(vec2(331.f, 65.f), vec2(395.f, 1.f));

		anim.SetRepeating(true);
		anim.SetSecPerFrame(0.08333f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 100, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "link");
	}
	*/
}

int HelloWorld::GetLink() {
	return m_linkEntity;
}

void HelloWorld::SetAnimation(int anim) {
	auto entity = m_linkEntity;
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.SetActiveAnim(anim);
}
