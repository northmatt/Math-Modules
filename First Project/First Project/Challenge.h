#pragma once

#include "Scene.h"

class Challenge : public Scene {
public:
	Challenge(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	int GetLink();

	void SetAnim(int anim);
private:
	int m_entityLink{ -1 };
};