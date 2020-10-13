#include "FirstCreation.h"
#include "Utilities.h"

FirstCreation::FirstCreation(std::string name)
	: Scene(name)
{
	//no gravity this is a top down scene
	m_gravity = b2Vec2(0.f, 0.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void FirstCreation::Unload()
{
	Scene::Unload();
}

void FirstCreation::InitScene(float windowWidth, float windowHeight)
{
	if (m_sceneReg == nullptr)
	{
		//Allocates registers
		m_sceneReg = new entt::registry;
	}

	//Attach the reg
	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Setup main camera
	{
		//Creates Camera Entity
		auto entity = ECS::CreateEntity();
		//ECS::SetIsMainCamera(entity, true);

		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
	
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	
	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up components
		std::string fileName = "LinkStandby.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.9f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}
	
	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add componentrs
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Transform>(entity).SetPositionZ(-1.f);
	}

	//TODO: Create a new entity

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

}

void FirstCreation::Update()
{
	Scene::AdjustScrollOffset();
}

void FirstCreation::KeyboardHold()
{
	auto& player = ECS::GetComponent<Transform>(MainEntities::MainPlayer());
	float speed = 15.f;


	//Velocity Equation
	//Displacement2 = Displacement1 + (Displacement / time)
	if (Input::GetKey(Key::Space))
	{
		player.SetPositionY(player.GetPositionY() + (speed * Timer::deltaTime));
	}
	if (Input::GetKey(Key::S))
	{
		player.SetPositionY(player.GetPositionY() - (speed * Timer::deltaTime));
	}

	if (Input::GetKey(Key::A))
	{
		player.SetPositionX(player.GetPositionX() - (speed * Timer::deltaTime));
	}
	if (Input::GetKey(Key::D))
	{
		player.SetPositionX(player.GetPositionX() + (speed * Timer::deltaTime));
	}
}

void FirstCreation::KeyboardDown()
{
	if (Input::GetKeyDown(Key::W))
	{
		printf("Key down\n");
	}
}

void FirstCreation::KeyboardUp()
{
	if (Input::GetKeyUp(Key::W))
	{
		printf("Key up\n");
	}
}
