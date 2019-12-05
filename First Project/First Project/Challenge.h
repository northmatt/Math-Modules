#pragma once

#include <iostream>
#include "Scene.h"

class Challenge : public Scene {
public:
	Challenge(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void SetAnim(int anim);
	int GetAnim();
	unsigned int GetAutoLink();

	void createCrate(float32 posX, float32 posY, bool isMain);

	//ImGUI Editor
	void CreateTab();
	void CreateEditor();
private:
	unsigned int autoLinkEnt;
};