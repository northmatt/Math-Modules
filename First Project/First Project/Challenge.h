#pragma once

#include <iostream>
#include "Scene.h"

class Challenge : public Scene {
public:
	Challenge(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void SetAnim(int anim);
	int GetAnim();

	//ImGUI Editor
	void CreateTab();
	void CreateEditor();
};