#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    textArea1.setWildcard(textArea1Buffer);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::function1()
{
    count += 0.01;
    Unicode::snprintfFloat(textArea1Buffer, TEXTAREA1_SIZE, "%.2f", count);
    textArea1.invalidate();
}
