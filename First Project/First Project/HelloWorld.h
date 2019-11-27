#pragma once

#include "Scene.h"

class HelloWorld : public Scene {
public:
	HelloWorld(std::string name);

	void InitScene(float widowWidth, float windowHeight) override;

	int GetLink();

	void SetAnimation(int anim);
private:
	int m_linkEntity = -1;
};