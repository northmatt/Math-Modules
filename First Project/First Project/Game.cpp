#include "Game.h"

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//creates hello world scene
	m_scenes.push_back(new HelloWorld(m_name));
	m_scenes.push_back(new HelloWorld("Scene of Two"));
	m_scenes.push_back(new Challenge("Chellenging Scene"));

	//sets active scene reference to Hello World scene
	m_activeScene = m_scenes[2];

	//Init the scene
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//*m_activeScene = File::LoadJSON("Scene of Two.json");

	m_register = m_activeScene->GetScene();

	sceneChallenge = (Challenge*)m_activeScene;
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput() {
	XInputController* tempCon;
	//looks through all controller slots and checks the input of any connected controller slots
	for (int i = 0; i < 3; i++)
		if (XInputManager::ControllerConnected(i)) {
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

//			GamepadStroke(tempCon);
//			GamepadUp(tempCon);
//			GamepadDown(tempCon);
			GamepadStick(tempCon);
//			GamepadTrigger(tempCon);
		}
}

void Game::GamepadStroke(XInputController* con) {
	if (con->IsButtonStroked(Buttons::A))
		printf("A Stroked\n");
}

void Game::GamepadUp(XInputController* con) {
	if (con->IsButtonReleased(Buttons::RB))
		printf("RB Released\n");
}

void Game::GamepadDown(XInputController* con) {
	if (con->IsButtonPressed(Buttons::THUMB_LEFT))
		printf("Left Thumbstick Clicked In.\n");
}

void Game::GamepadStick(XInputController* con) {
	Stick sticks[2];
	con->GetSticks(sticks);

	float speed = 50;
	auto& tran = m_register->get<Transform>(sceneChallenge->GetLink());
	vec3 simpleVec{ sticks[0].x, sticks[0].y, 0 };

	if (simpleVec.x != 0 && simpleVec.y != 0) {
		simpleVec = simpleVec.operator*(speed * Timer::deltaTime);

		tran.SetPosition(tran.GetPosition() + simpleVec);

		if (simpleVec.x < 0)
			sceneChallenge->SetAnim(0);
		else if (simpleVec.x > 0)
			sceneChallenge->SetAnim(1);
	}

}

void Game::GamepadTrigger(XInputController* con) {
	Triggers triggers;
	con->GetTriggers(triggers);

	if (0.4f <= triggers.RT && triggers.RT <= 0.8f)
		printf("Half Pressed\n");

	if (triggers.RT > 0.8f)
		printf("Full Pressed\n");
}

void Game::KeyboardHold()
{
	//Keyboard button held
	if (Input::GetKey(Key::A) || Input::GetKey(Key::S) || Input::GetKey(Key::D) || Input::GetKey(Key::W)) {
		float speed = 50;
		auto& tran = m_register->get<Transform>(sceneChallenge->GetLink());
		vec3 simpleVec{ 0, 0, 0 };

		if (Input::GetKey(Key::A))
			simpleVec.x -= 1;
		if (Input::GetKey(Key::D))
			simpleVec.x += 1;

		if (Input::GetKey(Key::W))
			simpleVec.y += 1;
		if (Input::GetKey(Key::S))
			simpleVec.y -= 1;

		float simMag = simpleVec.GetMagnitude();
		if (simMag != 0) {
			simpleVec = simpleVec.operator/(simMag);
			simpleVec = simpleVec.operator*(speed * Timer::deltaTime);

			tran.SetPosition(tran.GetPosition() + simpleVec);
		}
	}
}

void Game::KeyboardDown()
{
	if (Input::GetKeyDown(Key::A))
		sceneChallenge->SetAnim(0);
	else if (Input::GetKeyDown(Key::D))
		sceneChallenge->SetAnim(1);
}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
//	printf("Mouse moved (%f, %f)\n", float(evnt.x), float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	/*
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		printf("Left mouse at (%f, %f)\n", float(evnt.x), float(evnt.y));

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		printf("Right mouse at (%f, %f)\n", float(evnt.x), float(evnt.y));

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		printf("Middle mouse at (%f, %f)\n", float(evnt.x), float(evnt.y));
	*/
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
//	printf("Mouse scroll %f\n", float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
