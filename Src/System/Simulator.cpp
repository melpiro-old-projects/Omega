#include "Simulator.h"


Simulator::Simulator()
{
    simulator = xdo_new(NULL);
}

Simulator::~Simulator()
{
    xdo_free(simulator);
}


void Simulator::writeText(std::string text, double sleepMillisecond)
{
    xdo_enter_text_window(simulator, CURRENTWINDOW, text.c_str(), sleepMillisecond * 1000);
}

void Simulator::simulateErase()
{
    xdo_send_keysequence_window(simulator, CURRENTWINDOW, "BackSpace", 0);
}
void Simulator::simulateReturn()
{
    xdo_send_keysequence_window(simulator, CURRENTWINDOW, "Return", 0);
}

void Simulator::simulateCtrl_C()
{
    xdo_send_keysequence_window(simulator, CURRENTWINDOW, "ctrl+c", 0);
}
void Simulator::simulateCtrl_V()
{
    xdo_send_keysequence_window(simulator, CURRENTWINDOW, "ctrl+v", 0);
}

void Simulator::setMousePosition(int x, int y)
{
    xdo_move_mouse(simulator, x, y, 0);
}
void Simulator::simulateLeftClick()
{
    xdo_click_window(simulator, CURRENTWINDOW, 1);
}
void Simulator::simulateDoubleLeftClick()
{
    xdo_click_window(simulator, CURRENTWINDOW, 1);
    usleep(15);
    xdo_click_window(simulator, CURRENTWINDOW, 1);
}
void Simulator::simulateMiddleClick()
{
    xdo_click_window(simulator, CURRENTWINDOW, 2);
}
void Simulator::simulateRightClick()
{
    xdo_click_window(simulator, CURRENTWINDOW, 3);
}

void Simulator::simulateLeftPress()
{
    xdo_mouse_down(simulator, CURRENTWINDOW, 1);
}
void Simulator::simulateLeftRelease()
{
    xdo_mouse_up(simulator, CURRENTWINDOW, 1);
}

sf::Vector2i Simulator::getMousePosition()
{
    int x = 0;
    int y = 0;
    xdo_get_mouse_location2(simulator, &x, &y, NULL, NULL);
    return sf::Vector2i(x,y);
}

sf::Color Simulator::getPixelColor(int x, int y)
{

    XColor c;
    Display *d = XOpenDisplay((char *) NULL);

    XImage *image;
    image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
    c.pixel = XGetPixel (image, 0, 0);
    XFree (image);
    XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);

    return sf::Color(c.red/256, c.green/256, c.blue/256);;
}