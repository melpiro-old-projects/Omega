#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
extern "C" {
#include <xdo.h>
}

class Simulator
{
public:
    Simulator();
    ~Simulator();

    void writeText(std::string text, double sleepMillisecond);

    void simulateErase();
    void simulateReturn();
    void simulateCtrl_C();
    void simulateCtrl_V();

    void setMousePosition(int x, int y);
    void simulateLeftClick();
    void simulateDoubleLeftClick();
    void simulateMiddleClick();
    void simulateRightClick();

    void simulateLeftPress();
    void simulateLeftRelease();

    sf::Vector2i getMousePosition();
    sf::Color getPixelColor(int x, int y);

private:
    xdo_t* simulator;
};

