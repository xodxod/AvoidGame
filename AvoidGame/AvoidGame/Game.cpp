#include "Game.h"
//Start Up
Game::Game()
{
	//윈도우 초기화 및 생성
	this->InitWindowPointer();
	this->InitWindow();

	//Player 초기화
	this->InitPlayer();

	//Enemy 초기화
	this->InitEnemy();
}

void Game::InitWindowPointer()
{
	//포인터 변수 초기화
	this->Window = nullptr;
}

void Game::InitWindow()
{
	//윈도우 동적생성
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close); //동적생성 표기법 주의

	//일정하게 반복 실행
	this->Window->setFramerateLimit(60);
}


//Update
const bool Game::Running() const
{
	return this->Window->isOpen();
}

void Game::EventHandler()
{
	//이벤트 발생 감지
	while (this->Window->pollEvent(Event)) {
		//이벤트 종류 판단
		switch (Event.type) {
		case Event::Closed:
			//동작
			this->Window->close();
			break;
		case Event::KeyPressed:
			if (Event.key.code == Keyboard::Escape) this->Window->close();
			break;
		}
	}
}

void Game::Update()
{
	this->EventHandler();

	this->UpdatePlayer();

	this->UpdateEnemy();
}

//Render
void Game::Render()
{
	//Clear
	this->Window->clear(Color(50, 50, 50, 255)); //Color::cyon
	//Draw Player
	this->Window->draw(this->Player);
	//Draw Enemy
	this->Window->draw(this->Enemy);
	//Display
	this->Window->display();
}
//Shout Down
Game::~Game()
{
	this->DeletWindow();
}

void Game::DeletWindow()
{
	//윈도우 메모리에서 제거
	delete this->Window;
}
//Player
void Game::InitPlayer()
{
	this->Player.setRadius(30.0f);
	this->Player.setFillColor(Color(107, 140, 140, 255));
	this->Player.setPosition(
		float(this->Window->getSize().x / 2) - 30.0f, 
		float(this->Window->getSize().y / 2) - 30.0f);
}

void Game::UpdatePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->Player.move(-3.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->Player.move(3.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->Player.move(0.0f, -3.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->Player.move(0.0f, 3.0f);
	}
}

//Enemy
void Game::InitEnemy()
{
	this->Enemy.setSize(Vector2f(60.0f,60.0f));
	this->Enemy.setFillColor(Color::Green);
	this->Enemy.setPosition(100, 100);
}

void Game::SpawnEnemy()
{
	this->Enemy.setPosition(static_cast<float>(rand()%1280), 0.0f);
	this->EnemyArray.push_back(this->Enemy);
}

void Game::UpdateEnemy()
{
	this->SpawnEnemy();
	//this->Enemy.move(0.0f, 1.0f);
}