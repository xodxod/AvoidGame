#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow* Window;
	Event Event;

	//Player
	CircleShape Player;

	//Enemy
	RectangleShape Enemy;
	vector<RectangleShape> EnemyArray;

public:
	//Startup
	Game();
	void InitWindowPointer();
	void InitWindow();
	
	//Update
	const bool Running() const;
	void EventHandler();
	void Update();

	//Render
	void Render();

	//Shout Down
	~Game();
	void DeletWindow();
	/*
		Element
	*/
	//Player
	void InitPlayer();
	void UpdatePlayer();

	//Enemy
	void InitEnemy();
	void SpawnEnemy();
	void UpdateEnemy();
};

