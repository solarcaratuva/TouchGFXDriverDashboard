#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>

#ifndef SIMULATOR
#include "data_queues.h"
#endif

Screen1View::Screen1View()
{
    line1.setPainter(line1Painter);
    line1_1.setPainter(line1_1Painter);
    shape1_2.setPainter(shape1_2Painter);
    shape1_2_1.setPainter(shape1_2_1Painter);
}

void Screen1View::setupScreen() {
    Screen1ViewBase::setupScreen();
    solarCurr.setWildcard(solarCurrBuffer);
    solarTemp.setWildcard(solarTempBuffer);
    solarVolt.setWildcard(solarVoltBuffer);
    solarPhoto.setWildcard(solarPhotoBuffer);
    cellVolt.setWildcard(cellVoltBuffer);
    cellTemp.setWildcard(cellTempBuffer);
    powerAux.setWildcard(powerAuxBuffer);
    bpsError.setWildcard(bpsErrorBuffer);
    speed.setWildcard(speedBuffer);
    session.setWildcard(sessionBuffer);
    total.setWildcard(totalBuffer);
    cruiseSpeed.setWildcard(cruiseSpeedBuffer);
    regenBreaking.setWildcard(regenBreakingBuffer);
    throttlePedal.setWildcard(throttlePedalBuffer);

    BPS_Warning.setAlpha(0);
    BPS_Warning.setVisible(false);
}

void Screen1View::handleKeyEvent(uint8_t key)
{
    // Use simple ASCII keys in the simulator window:
    if (key == 'A' || key == 'a')
    {
        presenter->toggleLeftTurnSignal();
    }
    else if (key == 'D' || key == 'd')
    {
        presenter->toggleRightTurnSignal();
    }
    // force a redraw of your indicators:
    invalidate();
}


void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::triggerBpsWarning() {
    bpsWarningState = 1;
    bpsWarningTickCounter = 0;
    BPS_Warning.setVisible(true);
}

void Screen1View::function2() {
    if (bpsWarningState == 1) {
        BPS_Warning.startFadeAnimation(255, 15); // Fade in
        bpsWarningState = 2;
        bpsWarningTickCounter = 0;
    }
    else if (bpsWarningState == 2) {
        bpsWarningTickCounter++;
        if (bpsWarningTickCounter >= 30) { // Hold for ~500ms
            bpsWarningState = 3;
            bpsWarningTickCounter = 0;
        }
    }
    else if (bpsWarningState == 3) {
        BPS_Warning.startFadeAnimation(0, 15); // Fade out
        bpsWarningState = 4;
        bpsWarningTickCounter = 0;
    }
    else if (bpsWarningState == 4) {
        bpsWarningTickCounter++;
        if (bpsWarningTickCounter >= 30) { // Wait before next flash
            bpsWarningState = 1; // Restart flashing loop
            bpsWarningTickCounter = 0;
        }
    }
}



// Variables used in both simulator and hardware
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
int count = 0;

bool previousBpsErrorState = false;
bool currentBpsErrorState = false;

void Screen1View::function1()
{
#ifndef SIMULATOR
    ReceivedCanData_t receivedCanData;
    if (xQueueReceive(canReceivedQueue, &receivedCanData, (TickType_t)0 ) == pdTRUE) {
        count     = receivedCanData.motor_controller_power_status.battery_voltage;
        packVolt  = receivedCanData.bps_pack_information.pack_voltage;
        packCurr  = receivedCanData.bps_pack_information.pack_current;
        rpm       = receivedCanData.motor_controller_power_status.motor_rpm;
        braking   = receivedCanData.motor_commands.braking;
        regen     = receivedCanData.motor_commands.regen_braking;
        manual    = receivedCanData.motor_commands.manual_drive;
        cruise    = receivedCanData.motor_commands.cruise_drive;
        brakeP    = receivedCanData.motor_commands.brake_pedal;
        throttle  = receivedCanData.motor_commands.throttle;
        cruiseS   = receivedCanData.motor_commands.cruise_speed;
        regenD    = receivedCanData.motor_commands.regen_drive;
        throttleP = receivedCanData.motor_commands.throttle_pedal;
        
        currentBpsErrorState = (receivedCanData.bps_error.always_on_supply_fault || receivedCanData.bps_error.canbus_communications_fault ||
            receivedCanData.bps_error.charge_limit_enforcement_fault || receivedCanData.bps_error.charger_safety_relay_fault || receivedCanData.bps_error.current_sensor_fault ||
            receivedCanData.bps_error.discharge_limit_enforcement_fault || receivedCanData.bps_error.fan_monitor_fault || receivedCanData.bps_error.high_voltage_isolation_fault ||
            receivedCanData.bps_error.internal_communications_fault || receivedCanData.bps_error.internal_conversion_fault || receivedCanData.bps_error.internal_logic_fault || 
            receivedCanData.bps_error.internal_memory_fault || receivedCanData.bps_error.internal_thermistor_fault || receivedCanData.bps_error.low_cell_voltage_fault ||
            receivedCanData.bps_error.open_wiring_fault || receivedCanData.bps_error.pack_voltage_sensor_fault || receivedCanData.bps_error.power_supply_12v_fault ||
            receivedCanData.bps_error.thermistor_fault || receivedCanData.bps_error.voltage_redundancy_fault || receivedCanData.bps_error.weak_cell_fault || receivedCanData.bps_error.weak_pack_fault != 0);
    }
#else
    // Dummy test values for simulator
    count++;
    packVolt  = 42;
    packCurr  = 5;
    rpm       = 1234;
    braking   = 1;
    regen     = 0;
    manual    = 1;
    cruise    = 1;
    brakeP    = 50;
    throttle  = 70;
    cruiseS   = 30;
    regenD    = 1;
    throttleP = 60;
    currentBpsErrorState = 1;
#endif

    // Get logic from presenter
    bool isRight     = presenter->getRightTurnSignal(); 
    bool isLeft      = presenter->getLeftTurnSignal();
    bool isHaz       = presenter->getHazards();
    bool isRegen     = presenter->getRegenEn();
    bool isCruise    = presenter->getCruiseEn();
    bool isCruiseInc = presenter->getCruiseInc();
    bool isCruiseDec = presenter->getCruiseDec();
    bool isLowPower  = presenter->getLowPowerMode();

    // Set turn signal visuals
    if (isHaz) {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    } else if (isLeft) {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    } else if (isRight) {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
    } else if (isCruise || isRegen || isCruiseInc || isCruiseDec || isLowPower) {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(71, 201, 4));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    } else {
        line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
        shape1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }

    
    if (currentBpsErrorState && !previousBpsErrorState) {
        triggerBpsWarning(); // Trigger only on rising edge
    }

    previousBpsErrorState = currentBpsErrorState; // Save for next tick

    // Update displayed values
    Unicode::snprintfFloat(solarCurrBuffer, SOLARCURR_SIZE, "%.2f", manual);
    Unicode::snprintfFloat(solarTempBuffer, SOLARTEMP_SIZE, "%.2f", cruise);
    Unicode::snprintfFloat(solarVoltBuffer, SOLARVOLT_SIZE, "%.2f", brakeP);
    Unicode::snprintfFloat(solarPhotoBuffer, SOLARPHOTO_SIZE, "%.2f", throttle);
    Unicode::snprintfFloat(cellVoltBuffer, CELLVOLT_SIZE, "%.2f", packVolt);
    Unicode::snprintfFloat(cellTempBuffer, CELLTEMP_SIZE, "%.2f", packCurr);
    Unicode::snprintfFloat(powerAuxBuffer, POWERAUX_SIZE, "%.2f", count);
    Unicode::snprintfFloat(bpsErrorBuffer, BPSERROR_SIZE, "%.2f", count);
    Unicode::snprintfFloat(speedBuffer, SPEED_SIZE, "%.2f", rpm);
    Unicode::snprintfFloat(sessionBuffer, SESSION_SIZE, "%.2f", regenD);
    Unicode::snprintfFloat(cruiseSpeedBuffer, CRUISESPEED_SIZE, "%.2f", cruiseS);
    Unicode::snprintfFloat(regenBreakingBuffer, REGENBREAKING_SIZE, "%.2f", regen);
    Unicode::snprintfFloat(throttlePedalBuffer, THROTTLEPEDAL_SIZE, "%.2f", throttleP);
    Unicode::snprintfFloat(totalBuffer, TOTAL_SIZE, "%.2f", braking);

    // Refresh the display elements
    solarCurr.invalidate();
    solarTemp.invalidate();
    solarVolt.invalidate();
    solarPhoto.invalidate();
    cellVolt.invalidate();
    cellTemp.invalidate();
    powerAux.invalidate();
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
