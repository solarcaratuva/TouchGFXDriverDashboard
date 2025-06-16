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
    BPS_SOC.setWildcard(BPS_SOCBuffer);
    DTCStatus.setWildcard(DTCStatusBuffer);
    DischargeRelayStatus.setWildcard(DischargeRelayStatusBuffer);
    ChargeRelay.setWildcard(ChargeRelayBuffer);
    leftTurnText.setWildcard(leftTurnTextBuffer);

    BPS_Warning.setAlpha(0);
    BPS_Warning.setVisible(false);

    PowerAux_Warning.setAlpha(0);
    PowerAux_Warning.setVisible(false);

    MtrComm_Warning.setAlpha(0);
    MtrComm_Warning.setVisible(false);

    CruiseINC.setAlpha(0);
    CruiseINC.setVisible(false);

    CruiseDEC.setAlpha(0);
    CruiseDEC.setVisible(false);
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
    } else if (key == 'R' || key == 'r') {
        presenter->toggleRegenEn();
    } else if (key == 'L' || key == 'l') {
        presenter->toggleLowPowerEn();
    } else if (key == '+') {
        CruiseINC.setAlpha(0);
        CruiseINC.setVisible(true);
        CruiseINC.startFadeAnimation(255, 15);  // fade in
        cruiseIncState = 1;
        cruiseIncTickCounter = 0;
        CruiseINC.invalidate();
    } else if (key == '-') {
        CruiseDEC.setAlpha(0);
        CruiseDEC.setVisible(true);
        CruiseDEC.startFadeAnimation(255, 15);  // fade in
        cruiseDecState = 1;
        cruiseDecTickCounter = 0;
        CruiseDEC.invalidate();
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

void Screen1View::triggerPowerAuxWarning() { 
    powerAuxWarningState = 1;
    powerAuxWarningTickCounter = 0;
    PowerAux_Warning.setVisible(true);
}

void Screen1View::triggerMtrCommWarning() {
    mtrCommWarningState = 1;
    mtrCommWarningTickCounter = 0;
    MtrComm_Warning.setVisible(true);
}

void Screen1View::function2() {
    if (bpsWarningState == 1) {
        BPS_Warning.startFadeAnimation(255, 30); // Fade in
        bpsWarningState = 2;
        bpsWarningTickCounter = 0;
    }
    else if (bpsWarningState == 2) {
        bpsWarningTickCounter++;
        if (bpsWarningTickCounter >= 4) { // Hold for ~500ms
            bpsWarningState = 3;
            bpsWarningTickCounter = 0;
        }
    }
    else if (bpsWarningState == 3) {
        BPS_Warning.startFadeAnimation(0, 30); // Fade out
        bpsWarningState = 4;
        bpsWarningTickCounter = 0;
    }
    else if (bpsWarningState == 4) {
        bpsWarningTickCounter++;
        if (bpsWarningTickCounter >= 4) { // Wait before next flash
            bpsWarningState = 1; // Restart flashing loop
            bpsWarningTickCounter = 0;
        }
    }

    if (powerAuxWarningState == 1) {
        PowerAux_Warning.startFadeAnimation(255, 30); // Fade in
        powerAuxWarningState = 2;
        powerAuxWarningTickCounter = 0;
    }
    else if (powerAuxWarningState == 2) {
        powerAuxWarningTickCounter++;
        if (powerAuxWarningTickCounter >= 4) { // Hold for ~500ms
            powerAuxWarningState = 3;
            powerAuxWarningTickCounter = 0;
        }
    }
    else if (powerAuxWarningState == 3) {
        PowerAux_Warning.startFadeAnimation(0, 30); // Fade out
        powerAuxWarningState = 4;
        powerAuxWarningTickCounter = 0;
    }
    else if (powerAuxWarningState == 4) {
        powerAuxWarningTickCounter++;
        if (powerAuxWarningTickCounter >= 4) { // Wait before next flash
            powerAuxWarningState = 1; // Restart flashing loop
            powerAuxWarningTickCounter = 0;
        }
    }

    if (mtrCommWarningState == 1) {
        MtrComm_Warning.startFadeAnimation(255, 30); // Fade in
        mtrCommWarningState = 2;
        mtrCommWarningTickCounter = 0;
    }
    else if (mtrCommWarningState == 2) {
        mtrCommWarningTickCounter++;
        if (mtrCommWarningTickCounter >= 4) { // Hold for ~500ms
            mtrCommWarningState = 3;
            mtrCommWarningTickCounter = 0;
        }
    }
    else if (mtrCommWarningState == 3) {
        MtrComm_Warning.startFadeAnimation(0, 30); // Fade out
        mtrCommWarningState = 4;
        mtrCommWarningTickCounter = 0;
    }
    else if (mtrCommWarningState == 4) {
        mtrCommWarningTickCounter++;
        if (mtrCommWarningTickCounter >= 4) { // Wait before next flash
            mtrCommWarningState = 1; // Restart flashing loop
            mtrCommWarningTickCounter = 0;
        }
    }
    if (cruiseIncState == 1) {
    cruiseIncTickCounter++;
    if (cruiseIncTickCounter >= 1) {
        cruiseIncState = 2;
        cruiseIncTickCounter = 0;
        }
    } else if (cruiseIncState == 2) {
        cruiseIncTickCounter++;
        if (cruiseIncTickCounter >= 4) {
            CruiseINC.startFadeAnimation(0, 15); // fade out
            cruiseIncState = 3;
            cruiseIncTickCounter = 0;
        }
    } else if (cruiseIncState == 3) {
        cruiseIncTickCounter++;
        if (cruiseIncTickCounter >= 1) {
            CruiseINC.setVisible(false);
            cruiseIncState = 0;
            cruiseIncTickCounter = 0;
        }
    }

    // Cruise DEC animation logic
    if (cruiseDecState == 1) {
        cruiseDecTickCounter++;
        if (cruiseDecTickCounter >= 1) {
            cruiseDecState = 2;
            cruiseDecTickCounter = 0;
        }
    } else if (cruiseDecState == 2) {
        cruiseDecTickCounter++;
        if (cruiseDecTickCounter >= 4) {
            CruiseDEC.startFadeAnimation(0, 15); // fade out
            cruiseDecState = 3;
            cruiseDecTickCounter = 0;
        }
    } else if (cruiseDecState == 3) {
        cruiseDecTickCounter++;
        if (cruiseDecTickCounter >= 1) {
            CruiseDEC.setVisible(false);
            cruiseDecState = 0;
            cruiseDecTickCounter = 0;
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
int packSOC = 0;
int packDTC = 0;
int packDischargeRelay = 0;
int packChargeRelay = 0;

bool previousBpsErrorState = false;
bool currentBpsErrorState = false;

bool previousPowerAuxErrorState = false;
bool currentPowerAuxErrorState = false;

bool previousMtrCommErrorState = false;
bool currentMtrCommErrorState = true;

void Screen1View::function1()
{
#ifndef SIMULATOR
    ReceivedCanData_t receivedCanData;
    if (xQueueReceive(canReceivedQueue, &receivedCanData, (TickType_t)0 ) == pdTRUE) {
        count     = receivedCanData.motor_controller_power_status.battery_voltage;
        packVolt  = receivedCanData.bps_pack_information.pack_voltage;
        packCurr  = receivedCanData.bps_pack_information.pack_current;
        packSOC   = receivedCanData.bps_pack_information.pack_soc;
        packDTC   = receivedCanData.bps_pack_information.dtc_status;
        packDischargeRelay = receivedCanData.bps_pack_information.discharge_relay_status;
        packChargeRelay = receivedCanData.bps_pack_information
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
        
        currentMtrCommErrorState = (receivedCanData.motor_controller_error.analog_sensor_err || receivedCanData.motor_controller_error.motor_current_sensor_u_err || receivedCanData.motor_controller_error.motor_current_sensor_w_err ||
        receivedCanData.motor_controller_error.fet_thermistor_err || receivedCanData.motor_controller_error.battery_voltage_sensor_err || receivedCanData.motor_controller_error.battery_current_sensor_adj_err ||
        receivedCanData.motor_controller_error.motor_current_sensor_adj_err || receivedCanData.motor_controller_error.accelerator_position_error || receivedCanData.motor_controller_error.controller_voltage_sensor_err ||
        receivedCanData.motor_controller_error.power_system_err || receivedCanData.motor_controller_error.overcurrent_err || receivedCanData.motor_controller_error.overvoltage_err ||
        receivedCanData.motor_controller_error.overcurrent_limit || receivedCanData.motor_controller_error.motor_system_err || receivedCanData.motor_controller_error.motor_lock ||
        receivedCanData.motor_controller_error.hall_sensor_short || receivedCanData.motor_controller_error.hall_sensor_open || receivedCanData.motor_controller_error.overheat_level)
        
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
    currentPowerAuxErrorState = 0;
    currentMtrCommErrorState = 1;
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
    } else if (isCruise || isCruiseInc || isCruiseDec) {
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

    if (isRegen) {
        RegenEN.setColor(touchgfx::Color::getColorFromRGB(0, 255, 51));
    } else {
        RegenEN.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }

    if (isLowPower) {
        LowPowerEN.setColor(touchgfx::Color::getColorFromRGB(0, 255, 51));
    } else {
        LowPowerEN.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    }

    
    if (currentBpsErrorState && !previousBpsErrorState) {
        triggerBpsWarning(); // Trigger only on rising edge
    }

    previousBpsErrorState = currentBpsErrorState; // Save for next tick

    if (currentPowerAuxErrorState && !previousPowerAuxErrorState) {
        triggerPowerAuxWarning();
    }

    previousPowerAuxErrorState = currentPowerAuxErrorState;

    if (currentMtrCommErrorState && !previousMtrCommErrorState) {
        triggerMtrCommWarning();
    }

    previousMtrCommErrorState = currentMtrCommErrorState;

    // Update displayed values
    Unicode::snprintfFloat(solarCurrBuffer, SOLARCURR_SIZE, "%.2f", manual);
    Unicode::snprintfFloat(solarTempBuffer, SOLARTEMP_SIZE, "%.2f", cruise);
    Unicode::snprintfFloat(solarVoltBuffer, SOLARVOLT_SIZE, "%.2f", brakeP);
    Unicode::snprintfFloat(solarPhotoBuffer, SOLARPHOTO_SIZE, "%.2f", throttle);
    Unicode::snprintfFloat(cellVoltBuffer, CELLVOLT_SIZE, "%.2f", packVolt);
    Unicode::snprintfFloat(cellTempBuffer, CELLTEMP_SIZE, "%.2f", packCurr);
    Unicode::snprintfFloat(powerAuxBuffer, POWERAUX_SIZE, "%.2f", currentMtrCommErrorState);
    Unicode::snprintfFloat(bpsErrorBuffer, BPSERROR_SIZE, "%.2f", currentBpsErrorState);
    Unicode::snprintfFloat(speedBuffer, SPEED_SIZE, "%.2f", rpm);
    Unicode::snprintfFloat(sessionBuffer, SESSION_SIZE, "%.2f", regenD);
    Unicode::snprintfFloat(cruiseSpeedBuffer, CRUISESPEED_SIZE, "%.2f", cruiseS);
    Unicode::snprintfFloat(regenBreakingBuffer, REGENBREAKING_SIZE, "%.2f", regen);
    Unicode::snprintfFloat(throttlePedalBuffer, THROTTLEPEDAL_SIZE, "%.2f", throttleP);
    Unicode::snprintfFloat(totalBuffer, TOTAL_SIZE, "%.2f", braking);
    Unicode::snprintfFloat(BPS_SOCBuffer, BPS_SOC_SIZE,     "%.2f", (float)packSOC);
    Unicode::snprintfFloat(DTCStatusBuffer, DTCSTATUS_SIZE            , "%.2f", (float)packDTC);
    Unicode::snprintfFloat(DischargeRelayStatusBuffer, DISCHARGERELAYSTATUS_SIZE , "%.2f", (float)packDischargeRelay);
    Unicode::snprintfFloat(ChargeRelayBuffer,       CHARGERELAY_SIZE ,      "%.2f", (float)packChargeRelay);
    Unicode::snprintf(leftTurnTextBuffer, LEFTTURNTEXT_SIZE, "%d", isLeft ? 1 : 0);
    Unicode::snprintf( rightTurnTextBuffer,   RIGHTTURNTEXT_SIZE,   "%d", isRight ? 1 : 0 );
    Unicode::snprintf( hazardsTextBuffer,     HAZARDSTEXT_SIZE,       "%d", isHaz   ? 1 : 0 );
    Unicode::snprintf( regenENTextBuffer,     REGENENTEXT_SIZE,      "%d", isRegen ? 1 : 0 );
    Unicode::snprintf( CruiseDECTextBuffer,   CRUISEDECTEXT_SIZE,    "%d", isCruiseDec ? 1 : 0 );
    Unicode::snprintf( CruiseENTextBuffer,    CRUISEENTEXT_SIZE,     "%d", isCruise   ? 1 : 0 );
    Unicode::snprintf( CruiseINCTextBuffer,   CRUISEINCTEXT_SIZE        ,    "%d", isCruiseInc ? 1 : 0 );
    Unicode::snprintf( lowPowerTextBuffer,    LOWPOWERTEXT_SIZE,     "%d", isLowPower  ? 1 : 0 );

    
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
    RegenEN.invalidate();
    LowPowerEN.invalidate();
    BPS_SOC.invalidate();
    DTCStatus.invalidate();
    DischargeRelayStatus.invalidate();
    ChargeRelay.invalidate();
    leftTurnText.invalidate();
    rightTurnText.invalidate();
    hazardsText.invalidate();
    regenENText.invalidate();
    CruiseDECText.invalidate();
    CruiseINCText.invalidate();
    lowPowerText.invalidate();
}
