#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GlobalsVariables.h";

namespace ssf{

	class Text
	{
	public:
		Text();
		Text(sf::RenderWindow* window, float x = 0, float y = 0, float posRx = -1, float posRy = -1, bool centered = false);
		Text(sf::RenderWindow* window,std::string fontName, float x = 0, float y = 0, float posRx = -1, float posRy = -1, bool centered = false);
		Text(sf::RenderWindow* window, float x = 0, float y = 0, bool centered = false);
		Text(sf::RenderWindow* window, float x = 0, float y = 0);

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

		///////////////////////////////////////////////////////////////:
		//gS = get sprit
		// permet de modifier le sprite depuis l'exterieur
		// ex: sf::sprite.gS().setPosition(.., ..);
		sf::Text& gT();


		///////////////////////////////////////////////////////////////:
		// setPosition qui prend en compte les facteurs de redimention
		void setPosition(float x, float y);
		void setPosition(float x, float y, bool update);
		void move(float x, float y);
		sf::Vector2f getPosition();


		///////////////////////////////////////////////////////////////:
		//changer le texte 
		void setString(sf::String text);
		void setString(sf::String text, double maxWidth);
		sf::String getString();
		void setCharacterSize(unsigned int value);

		///////////////////////////////////////////////////////////////:
		// pour faire des bouttons
		bool hover(float viewZoom = 1);

		void setScale(float x, float y);

		///////////////////////////////////////////////////////////////
		// check du click sur le text
		bool clicked(sf::Event& e, float viewZoom = 1);

		///////////////////////////////////////////////////////////////:
		// changer le point de redientionement
		void setPointRedi(float x, float y);


		///////////////////////////////////////////////////////////////:
		// origine as center
		void setOrigineAsCenter();

		static sf::String ready_text(sf::String text, int width,const int& font_size, const sf::Font &font);

	protected:

		///////////////////////////////////////////////////////////////
		// fenetre li�e � l'objet
		sf::RenderWindow* m_fen;

		///////////////////////////////////////////////////////////////:
		//texte
		sf::Text m_text;


		///////////////////////////////////////////////////////////////:
		//position en x et y sans modification
		float m_x;
		float m_y;

		///////////////////////////////////////////////////////////////:
		//position de d�calage de redimentions
		float m_posRx;
		float m_posRy;

		///////////////////////////////////////////////////////////////:
		// origine as center
		bool m_isOrigineAsCenter;
	};
}


