#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

#include <deque>
#include <string>
class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleKeyEvent(uint8_t key) override;
    virtual void function2() override;
    virtual void function1();
    void triggerBpsWarning();
    void triggerPowerAuxWarning();
    void triggerMtrCommWarning();
    double count = 0;
protected:

private:
    uint8_t bpsWarningState = 0; // 0=idle, 1=fadeIn, 2=hold, 3=fadeOut
    uint16_t bpsWarningTickCounter = 0;
    uint8_t powerAuxWarningState = 0;
    uint16_t powerAuxWarningTickCounter = 0;
    uint8_t mtrCommWarningState = 0;
    uint16_t mtrCommWarningTickCounter = 0;
    int cruiseIncState = 0; // 0 = idle, 1 = fade in, 2 = hold, 3 = fade out
    int cruiseIncTickCounter = 0;

    // For Cruise DEC text popup
    int cruiseDecState = 0;
    int cruiseDecTickCounter = 0;

    // For improved CAN error logging
    static constexpr int MAX_RECENT_ERRORS = 3;
    // rolling buffer of the last‐N fault names:
    std::deque<const char*> recentErrors;
        
    // previous‐state arrays for rising‐edge detection
    static constexpr int NUM_BPS_ERRORS = 15;
    bool prevBpsErrorStates[NUM_BPS_ERRORS];

    static constexpr int NUM_MTR_ERRORS = 18;
    bool prevMtrErrorStates[NUM_MTR_ERRORS];
};

#endif // SCREEN1VIEW_HPP
