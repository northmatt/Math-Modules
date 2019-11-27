#include "Challenge.h"

Challenge::Challenge(std::string name) {
}

void Challenge::InitScene(float windowWidth, float windowHeight) {
	//Dynamically allocates register
	m_sceneReg = new entt::registry;

	//attach register
	ECS::AttachRegister(m_sceneReg);

	//camera
	{
		//aspect ratio
		float aspectRatio = windowWidth / windowHeight;

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
	//Controller sign
	{
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//sets up components
		std::string fileName = "Controller.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 50);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(35.f, 15.f, 0.5f));

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Controller Sign");
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
		m_entityLink = entity;

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "spritesheets/LinkAttacks.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
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
	//WASD sign
	{
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "spritesheets/WASD Text.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//Add first anim
		animController.AddAnimation(Animation());
		//get first anim
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(1.f, 46.f), vec2(108.f, 1.f));
		anim.AddFrame(vec2(1.f, 93.f), vec2(108.f, 48.f));
		anim.AddFrame(vec2(1.f, 140.f), vec2(108.f, 95.f));
		anim.AddFrame(vec2(1.f, 187.f), vec2(108.f, 142.f));
		anim.AddFrame(vec2(1.f, 234.f), vec2(108.f, 189.f));
		anim.AddFrame(vec2(1.f, 281.f), vec2(108.f, 236.f));
		anim.AddFrame(vec2(1.f, 328.f), vec2(108.f, 283.f));
		anim.AddFrame(vec2(1.f, 375.f), vec2(108.f, 330.f));
		anim.AddFrame(vec2(1.f, 422.f), vec2(108.f, 377.f));
		anim.AddFrame(vec2(1.f, 469.f), vec2(108.f, 424.f));
		anim.AddFrame(vec2(1.f, 516.f), vec2(108.f, 471.f));
		anim.AddFrame(vec2(1.f, 563.f), vec2(108.f, 518.f));

		anim.SetRepeating(true);
		anim.SetSecPerFrame(0.08f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 107, 45, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-15.f, 60.f, 1.f));

		//set up identitier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "WASD Sign");
	}
}

int Challenge::GetLink() {
	return m_entityLink;
}

void Challenge::SetAnim(int anim) {
	auto entity = m_entityLink;
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.SetActiveAnim(anim);
}
