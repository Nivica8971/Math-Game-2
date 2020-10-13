#pragma once

#include "Scene.h"

class FirstCreation : public Scene
{
public:
	FirstCreation(std::string name);

	void Unload();

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

private:
	int mainPlayer = 0;
};