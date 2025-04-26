#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include "data_queues.h"

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

ReceivedCanData_t receivedCanData;
bool switchPressed = false;

void Screen1View::function1()
{
    if( xQueueReceive(canReceivedQueue, &receivedCanData, (TickType_t)0 ) == pdTRUE ) {
        // got data, process it
        count = receivedCanData.test;
        // ++count;
    } else {
        // queue empty, do other work immediately
        // count = 10000;
    }
    // count += .01;
    bool isRight = presenter->getRightTurnSignal();
    bool isLeft = presenter->getLeftTurnSignal();
    if(isLeft == true)
    {
         line1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
         shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    }
    else
    {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }
    if(isRight == true)
    {
         line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
         shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    }
    else
    {
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }

    Unicode::snprintfFloat(solarCurrBuffer, SOLARCURR_SIZE, "%.2f", count);
    //Example of changing text color: solarCurr.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
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
    line1.invalidate();
    line1_1.invalidate();
    shape1_2_1.invalidate();
    shape1_2.invalidate();
}
