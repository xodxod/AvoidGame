#include "Game.h"
//Start Up
Game::Game()
{
	//������ �ʱ�ȭ �� ����
	this->InitWindowPointer();
	this->InitWindow();

	//Player �ʱ�ȭ
	this->InitPlayer();

	//Enemy �ʱ�ȭ
	this->InitEnemy();
}

void Game::InitWindowPointer()
{
	//������ ���� �ʱ�ȭ
	this->Window = nullptr;
}

void Game::InitWindow()
{
	//������ ��������
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close); //�������� ǥ��� ����

	//�����ϰ� �ݺ� ����
	this->Window->setFramerateLimit(60);
}


//Update
const bool Game::Running() const
{
	return this->Window->isOpen();
}

void Game::EventHandler()
{
	//�̺�Ʈ �߻� ����
	while (this->Window->pollEvent(Event)) {
		//�̺�Ʈ ���� �Ǵ�
		switch (Event.type) {
		case Event::Closed:
			//����
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
	//������ �޸𸮿��� ����
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