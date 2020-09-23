#pragma once
#include "Rectangle.h"
#include "Text.h"
#include <SFML/Graphics.hpp>

namespace ssf {
	class Button : public ssf::Rectangle, public ssf::Text
	{
	public:
		Button();
		Button(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = false);
		Button(sf::RenderWindow* window, std::string font, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = false);
		Button(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered = false);

		
		///////////////////////////////////////////////////////////////:
		// detection du passage de la souris sur le bouton
		// pour detecter un clic il faut le coupler � sf::event
		bool hover(float viewZoom = 1);

		///////////////////////////////////////////////////////////////:
		// d�t�ction du clic
		bool clicked(sf::Event& e, float viewZoom = 1);

		///////////////////////////////////////////////////////////////:
		// contour size
		void setOutlineThickness(float v);


		///////////////////////////////////////////////////////////////:
		// updates
		void update();
		void update(float viewZoom);

		///////////////////////////////////////////////////////////////:
		// affichage
		void draw();

		///////////////////////////////////////////////////////////////:
		// set position button
		void setPosition(float x, float y);
		void move(float x, float y);

		///////////////////////////////////////////////////////////////:
		// changer le point de redientionement
		void setPointRedi(float x, float y);

		///////////////////////////////////////////////////////////////:
		// origine as center
		void setOrigineAsCenter();

		///////////////////////////////////////////////////////////////
		// update de la position du texte par apport a celle du rectangle
		void updatePosText();

		///////////////////////////////////////////////////////////////
		// couleur du text
		void setTextColor(sf::Color c);

	protected:
		///////////////////////////////////////////////////////////////:
		// rect de modifications lors du hover ou non 
		sf::IntRect m_rectB;
		sf::IntRect m_rectHover;

		///////////////////////////////////////////////////////////////:
		// fenetre
		sf::RenderWindow* m_fen;

	private:
		

		///////////////////////////////////////////////////////////////:
		// retiens la position
		sf::Vector2i m_positionSet;


	};

}
