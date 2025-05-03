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
    cruiseSpeed.setWildcard(cruiseSpeedBuffer);
    regenBreaking.setWildcard(regenBreakingBuffer);
    throttlePedal.setWildcard(throttlePedalBuffer);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

ReceivedCanData_t receivedCanData;
bool switchPressed = false;
int packVolt = 0;
int packCurr = 0;
int rpm = 0;
int braking = 0;
int regen = 0;
int manual = 0;
int cruise = 0;
int brakeP = 0;
int throttle = 0;
int cruiseS = 0;
int regenD = 0;
int throttleP = 0;
int mController = 0;

void Screen1View::function1()
{
    if( xQueueReceive(canReceivedQueue, &receivedCanData, (TickType_t)0 ) == pdTRUE ) {
        count = receivedCanData.motor_controller_power_status.battery_voltage;
        packVolt = receivedCanData.bps_pack_information.pack_voltage;
        packCurr = receivedCanData.bps_pack_information.pack_current;
        rpm = receivedCanData.motor_controller_power_status.motor_rpm;
        braking = receivedCanData.motor_commands.braking;
        regen = receivedCanData.motor_commands.regen_braking;
        manual = receivedCanData.motor_commands.manual_drive;
        cruise = receivedCanData.motor_commands.cruise_drive;
        brakeP = receivedCanData.motor_commands.brake_pedal;
        throttle = receivedCanData.motor_commands.throttle;
        cruiseS = receivedCanData.motor_commands.cruise_speed;
        regenD = receivedCanData.motor_commands.regen_drive;
        throttleP = receivedCanData.motor_commands.throttle_pedal;
    }
    // count += .01;
    bool isRight = presenter->getRightTurnSignal(); 
    bool isLeft = presenter->getLeftTurnSignal();
    bool isHaz = presenter->getHazards();
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
    if(isHaz == true)
    {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    }
    else
    {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }

    Unicode::snprintfFloat(solarCurrBuffer, SOLARCURR_SIZE, "%.2f", manual);
    //Example of changing text color: solarCurr.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    Unicode::snprintfFloat(solarTempBuffer, SOLARTEMP_SIZE, "%.2f", cruise);
    Unicode::snprintfFloat(solarVoltBuffer, SOLARVOLT_SIZE, "%.2f", brakeP);
    Unicode::snprintfFloat(solarPhotoBuffer, SOLARPHOTO_SIZE, "%.2f", throttle);
    Unicode::snprintfFloat(cellVoltBuffer, CELLVOLT_SIZE, "%.2f", packVolt);
    Unicode::snprintfFloat(cellTempBuffer, CELLTEMP_SIZE, "%.2f", packCurr);
    Unicode::snprintfFloat(powerAuxBuffer, POWERAUX_SIZE, "%.2f", count);
    Unicode::snprintfFloat(motorBuffer, MOTOR_SIZE, "%.2f", count);
    Unicode::snprintfFloat(bpsErrorBuffer, BPSERROR_SIZE, "%.2f", count);
    Unicode::snprintfFloat(speedBuffer, SPEED_SIZE, "%.2f", rpm);
    Unicode::snprintfFloat(sessionBuffer, SESSION_SIZE, "%.2f", regenD);
    Unicode::snprintfFloat(cruiseSpeedBuffer, CRUISESPEED_SIZE, "%.2f", cruiseS);
    Unicode::snprintfFloat(regenBreakingBuffer, REGENBREAKING_SIZE, "%.2f", regen);
    Unicode::snprintfFloat(throttlePedalBuffer, THROTTLEPEDAL_SIZE, "%.2f", throttleP);
    Unicode::snprintfFloat(totalBuffer, TOTAL_SIZE, "%.2f", braking);
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
    cruiseSpeed.invalidate();
    regenBreaking.invalidate();
    throttlePedal.invalidate();
}
