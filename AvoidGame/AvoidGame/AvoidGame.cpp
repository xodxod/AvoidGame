#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.h"

int main()
{
	//������ ��� ���� : �ʱⰪ ����
	//time�� ��� : ������ �� ���� �ʱⰪ�� �ٸ������� ���
	srand(time(NULL));
	//Startup
	Game Avoid;
	
	//Game Loop
	while (Avoid.Running()) {
		//Update
		Avoid.Update();
		//Render
		Avoid.Render();
	}
}

