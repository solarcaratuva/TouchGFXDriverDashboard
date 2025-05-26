#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void function2() override;
    virtual void function1();
    void triggerBpsWarning();
    double count = 0;
protected:

private:
    uint8_t bpsWarningState = 0; // 0=idle, 1=fadeIn, 2=hold, 3=fadeOut
    uint16_t bpsWarningTickCounter = 0;
};

#endif // SCREEN1VIEW_HPP
