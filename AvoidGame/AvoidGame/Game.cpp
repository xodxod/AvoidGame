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
	this->InitSpawn();

	//Point �ʱ�ȭ
	this->Point = 0;

	//Font �ʱ�ȭ
	this->InitFont();

	//Text �ʱ�ȭ
	this->InitPointText();
	this->InitGameOverText();

	//Game Over State �ʱ�ȭ
	this->GameOverState = false;

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

	if (!this->GameOverState) {

		this->UpdatePlayer();

		this->UpdateEnemy();

		this->CollisionCheck();

		this->UpdatePointText();
	}
}

//Render
void Game::Render()
{
	//Clear
	this->Window->clear(Color(50, 50, 50, 255)); //Color::cyon
	//Draw Player
	this->Window->draw(this->Player);

	//Draw Enemy
	//this->Window->draw(this->Enemy);
	for (int i = 0; i < this->EnemyArray.size(); i++) {
		this->Window->draw(this->EnemyArray[i]);
	}

	//Draw Text
	this->Window->draw(this->PointText);
	this->Window->draw(this->GameOverText);

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

void Game::InitSpawn()
{
	this->EnemyMax = 20;
	this->IntervalMax = 20.0f;
	this->IntervalStart = 0.0f;
}

void Game::SpawnEnemy()
{
	this->Enemy.setPosition(static_cast<float>(rand()%1280), 0.0f);
	this->EnemyArray.push_back(this->Enemy);
}

void Game::UpdateEnemy()
{
	//this->SpawnEnemy();
	//Enemy Maximum
	if (this->EnemyArray.size() <= this->EnemyMax) {
		//Enemy Spawn  Interval Delay
		if (this->IntervalMax <= this->IntervalStart) {
			this->SpawnEnemy();
			this->IntervalStart = 0.0f;
		}
		else {
			this->IntervalStart += 1.0f;
		}
	}
	//this->Enemy.move(0.0f, 1.0f);
	for (int i = 0; i < this->EnemyArray.size(); i++) {
		this->EnemyArray[i].move(0.0f, 4.0f);
	}
	for (int i = 0; i < this->EnemyArray.size(); i++) {
		//������ �ٱ����� ����� Enemy ����
		if (this->EnemyArray[i].getPosition().y >= this->Window->getSize().y) {
			this->EnemyArray.erase(this->EnemyArray.begin() + i);
			//�����Ǵ� Enemy ���� => ����
			Point++;
		}
	}
}

//Collision Check
void Game::CollisionCheck()
{
	for (int i = 0; i < EnemyArray.size(); i++) {
		if (this->Player.getGlobalBounds().intersects(this->EnemyArray[i].getGlobalBounds())) {
			//�浹 ; true
			//���� ����
			this->GameOverState = true;
			this->PrintGameOverText();
		}
	}
}

//Font
void Game::InitFont()
{
	if (this->Font.loadFromFile("Font/NanumSquareR.ttf")) {
		cout << "Load Complete" << endl;
	}
	else {
		cout << "Load Fail" << endl;
	}
}

//Text
void Game::InitPointText()
{
	this->PointText.setFont(this->Font);
	this->PointText.setCharacterSize(30);
	this->PointText.setFillColor(Color::White);
	this->PointText.setPosition(
		this->Window->getSize().x-150,
		this->Window->getSize().y-50
	);
}

void Game::UpdatePointText()
{
	stringstream pt;
	pt << "Point : " << Point;
	this->PointText.setString(pt.str());
}

void Game::InitGameOverText()
{
	this->GameOverText.setFont(this->Font);
	this->GameOverText.setCharacterSize(100);
	this->GameOverText.setFillColor(Color::White);
	this->GameOverText.setPosition(
		this->Window->getSize().x/2,
		this->Window->getSize().y/2
	);
}

void Game::PrintGameOverText()
{
	stringstream pt;
	pt << "Game Over" ;
	this->GameOverText.setString(pt.str());
}