#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>

Screen1View::Screen1View()
{
    line1.setPainter(line1Painter);
    line1_1.setPainter(line1_1Painter);
    shape1_2.setPainter(shape1_2Painter);
    shape1_2_1.setPainter(shape1_2_1Painter);
    //R: 240, G:212, B: 0
 
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    solarCurr.setWildcard(solarCurrBuffer);
    solarTemp.setWildcard(solarTempBuffer);
    solarVolt.setWildcard(solarVoltBuffer);
    solarPhoto.setWildcard(solarPhotoBuffer);
    cellVolt.setWildcard(cellVoltBuffer);
    cellTemp.setWildcard(cellTempBuffer);
    powerAux.setWildcard(powerAuxBuffer);
    motor.setWildcard(motorBuffer);
    bpsError.setWildcard(bpsErrorBuffer);
    speed.setWildcard(speedBuffer);
    session.setWildcard(sessionBuffer);
    total.setWildcard(totalBuffer);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::function1()
{
    count += .01;
    //Need to make if(**can message saying left-blinker is active**)
    // {
    //     line1Painter.setColor(touchgfx::Color::getColorFromRGB(240, 212, 0));
    //     shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(240, 212, 0));
    // }
    //Need to make if(**can message saying right-blinker is active**)
    // {
    //     line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(240, 212, 0));
    //     shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(240, 212, 0));
    // }

    Unicode::snprintfFloat(solarCurrBuffer, SOLARCURR_SIZE, "%.2f", count);
    //Example of changing text color: solarCurr.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
    Unicode::snprintfFloat(solarTempBuffer, SOLARTEMP_SIZE, "%.2f", count);
    Unicode::snprintfFloat(solarVoltBuffer, SOLARVOLT_SIZE, "%.2f", count);
    Unicode::snprintfFloat(solarPhotoBuffer, SOLARPHOTO_SIZE, "%.2f", count);
    Unicode::snprintfFloat(cellVoltBuffer, CELLVOLT_SIZE, "%.2f", count);
    Unicode::snprintfFloat(cellTempBuffer, CELLTEMP_SIZE, "%.2f", count);
    Unicode::snprintfFloat(powerAuxBuffer, POWERAUX_SIZE, "%.2f", count);
    Unicode::snprintfFloat(motorBuffer, MOTOR_SIZE, "%.2f", count);
    Unicode::snprintfFloat(bpsErrorBuffer, BPSERROR_SIZE, "%.2f", count);
    Unicode::snprintfFloat(speedBuffer, SPEED_SIZE, "%.2f", count);
    Unicode::snprintfFloat(sessionBuffer, SESSION_SIZE, "%.2f", count);
    Unicode::snprintfFloat(totalBuffer, TOTAL_SIZE, "%.2f", count);
    solarCurr.invalidate();
    solarTemp.invalidate();
    solarVolt.invalidate();
    solarPhoto.invalidate();
    cellVolt.invalidate();
    cellTemp.invalidate();
    powerAux.invalidate();
    motor.invalidate();
    bpsError.invalidate();
    speed.invalidate();
    session.invalidate();
    total.invalidate();
}
