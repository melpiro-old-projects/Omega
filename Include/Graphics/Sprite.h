#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StaticValues.h"

namespace ssf
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(sf::RenderWindow* window, std::string local, float x = 0, float y = 0, float posRx = -1, float posRy = -1, bool centered = false);
		Sprite(sf::RenderWindow* window, std::string local, float x = 0, float y = 0, bool centered = false);
		Sprite(sf::RenderWindow* window, std::string local, float x = 0, float y = 0);

		void loadTexture();
		void loadTexture(sf::Texture& tex);

		///////////////////////////////////////////////////////////////:
		// update: dplace la texture en fonction du redimentionnement
		// de la fenetre
		// attention il faut appeler update apr�s les modification 
		// sur le sprite obligatoirement !
		void update();
		void update(float viewZoom);


		///////////////////////////////////////////////////////////////:
		//affichage dans le fenetre
		void draw();
		void draw(sf::IntRect bound);


		///////////////////////////////////////////////////////////////:
		//gS = get sprit
		// permet de modifier le sprite depuis l'exterieur
		// ex: sf::sprite.gS().setPosition(.., ..);
		sf::Sprite& gS();


		///////////////////////////////////////////////////////////////:
		// setPosition qui prend en compte les facteurs de redimention
		void setPosition(float x, float y);
		void setPosition(float x, float y, bool update);
		void move(float x, float y);
		void setScale(float x, float y);
		sf::Vector2f getPosition();


		///////////////////////////////////////////////////////////////:
		// pour faire des bouttons
		bool hover(float viewZoom = 1);
		bool clicked(sf::Event& e, float viewZoom = 1);


		///////////////////////////////////////////////////////////////:
		// changer le point de redientionement
		void setPointRedi(float x, float y);


		///////////////////////////////////////////////////////////////:
		// origine as center
		void setOrigineAsCenter();

		///////////////////////////////////////////////////////////////:
		// color
		void setColor(sf::Color c);

	protected:

		///////////////////////////////////////////////////////////////
		// fenetre li�e � l'objet
		sf::RenderWindow* m_fen;

		///////////////////////////////////////////////////////////////:
		//chemin vers la texture locale
		std::string m_local;


		///////////////////////////////////////////////////////////////:
		//sprite
		sf::Sprite m_sprite;
		///////////////////////////////////////////////////////////////:
		// texture du sprite
		sf::Texture m_texture;


		///////////////////////////////////////////////////////////////:
		//position en x et y sans modification
		float m_x;
		float m_y;

		///////////////////////////////////////////////////////////////:
		// point de redimention
		float m_posRx;
		float m_posRy;

		///////////////////////////////////////////////////////////////:
		// origine as center
		bool m_isOrigineAsCenter;
	};
}

