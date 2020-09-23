#pragma once
#include "Sprite.h"
#include "Text.h"
#include <SFML/Graphics.hpp>

namespace ssf {
	class TexturedButton : public ssf::Sprite, public ssf::Text
	{
	public:
		TexturedButton();
		TexturedButton(sf::RenderWindow* fen, std::string local, float x, float y, float posRx = -1, float posRy = -1, bool centered = false);
		TexturedButton(sf::RenderWindow* window, std::string local, float x = 0, float y = 0, bool centered = false);

		///////////////////////////////////////////////////////////////:
		// définition des rectangles de modifications lors du hover
		void setRectButton(sf::IntRect rectB, sf::IntRect rectHover);


		///////////////////////////////////////////////////////////////:
		// detection du passage de la souris sur le bouton
		// pour detecter un clic il faut le coupler à sf::event
		bool hover(float viewZoom = 1);

		///////////////////////////////////////////////////////////////:
		// détéction du clic
		bool clicked(sf::Event &e, float viewZoom = 1);


		///////////////////////////////////////////////////////////////:
		// chargement des textures
		void loadTexture();
		void loadTexture(sf::Texture &tex);

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

		///////////////////////////////////////////////////////////////
		// automatique rect Hover
		void calcAutoRectHover();

		///////////////////////////////////////////////////////////////
		// calcule pour ne pas avoir de rect Hover
		void calcNoRectHover();

	protected:
		///////////////////////////////////////////////////////////////:
		// rect de modifications lors du hover ou non 
		sf::IntRect m_rectB;
		sf::IntRect m_rectHover;

	private:
		///////////////////////////////////////////////////////////////:
		// fenetre
		sf::RenderWindow* m_fen;

		
	};

}
