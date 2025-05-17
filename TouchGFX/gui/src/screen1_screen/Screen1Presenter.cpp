#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::function1()
{
    
}

bool Screen1Presenter::getRightTurnSignal() {
    return model->isRightTurnSignal();
}

bool Screen1Presenter::getLeftTurnSignal() {
    return model->isLeftTurnSignal();  // Or whatever model function you're using
}

bool Screen1Presenter::getHazards() {
    return model->isHazards();
}

bool Screen1Presenter::getRegenEn() {
    return model->isRegenEn();
}

bool Screen1Presenter::getCruiseEn() {
    return model->isCruiseEn();
}

bool Screen1Presenter::getCruiseInc() {
    return model->isCruiseInc();
}

bool Screen1Presenter::getCruiseDec() {
    return model->isCruiseDec();
}

bool Screen1Presenter::getLowPowerMode() {
    return model->isLowPowerMode();
}

