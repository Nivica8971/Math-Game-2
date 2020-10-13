#pragma once

#include "Scene.h"

class PhysicsPlayground : public Scene
{
public:
	PhysicsPlayground(std::string name);
	
	int m_finishLine = 1940;
	float speed = 0.f;

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;


	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:

};
