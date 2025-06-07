#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifdef SIMULATOR

Model::Model()
    : modelListener(0),
      leftTurnSignal(false),
      rightTurnSignal(false)
{
}

void Model::tick()
{

}

bool Model::isLeftTurnSignal() const
{
    return leftTurnSignal;
}
void Model::setLeftTurnSignal(bool on)
{
    leftTurnSignal = on;
}

bool Model::isRightTurnSignal() const
{
    return rightTurnSignal;
}
void Model::setRightTurnSignal(bool on)
{
    rightTurnSignal = on;
}

void Model::setRegenEn(bool on) {
    regen = on;
}

bool Model::isRegenEn() const 
{
    return regen;
}

bool Model::isLowPowerMode() const 
{ 
    return lowPower; 
}

void Model::setLowPowerEn(bool on) {
    lowPower = on;
}



bool Model::isHazards()         const { return false; }
bool Model::isCruiseEn()        const { return false; }
bool Model::isCruiseInc()       const { return false; }
bool Model::isCruiseDec()       const { return false; }

#else

#include "main.h"

Model::Model() : modelListener(0) { }

void Model::tick() {
    // Left turn signal
    bool currentLeft = HAL_GPIO_ReadPin(USR_BTN_3_GPIO_Port, USR_BTN_3_Pin);
    if (prevLeftButtonState == 1 && currentLeft == 0) { // pressed
        leftTurnSignal = !leftTurnSignal;
    }
    prevLeftButtonState = currentLeft;

    // Right turn signal
    bool currentRight = HAL_GPIO_ReadPin(USR_BTN_2_GPIO_Port, USR_BTN_2_Pin);
    if (prevRightButtonState == 1 && currentRight == 0) { // pressed
        rightTurnSignal = !rightTurnSignal;
    }
    prevRightButtonState = currentRight;

    // low power
    bool currentLowPower = HAL_GPIO_ReadPin(USR_BTN_9_GPIO_Port, USR_BTN_9_Pin);
    if (prevLowPowerButtonState == 1 && currentLowPower == 0) {
        lowPower = !lowPower;
    }
    prevLowPowerButtonState = currentLowPower;

    // Regen Enable
    bool currentRegen = HAL_GPIO_ReadPin(USR_BTN_6_GPIO_Port, USR_BTN_6_Pin);
    if (prevRegenButtonState == 1 && currentRegen == 0) {
        regen = !regen;
    }
    prevRegenButtonState = currentRegen;

    // Cruise Enable
    bool currentCruise = HAL_GPIO_ReadPin(USR_BTN_5_GPIO_Port, USR_BTN_5_Pin);
    if (prevCruiseButtonState == 1 && currentCruise == 0) {
        cruise = !cruise;
    }
    prevCruiseButtonState = currentCruise;

    // Hazards
    bool currentHazard = HAL_GPIO_ReadPin(USR_BTN_4_GPIO_Port, USR_BTN_4_Pin);
    if (prevHazardButtonState == 1 && currentHazard == 0) {
        hazard = !hazard;
        if (hazard) {
            leftTurnSignal = false;
            rightTurnSignal = false;
        }
    }
    prevHazardButtonState = currentHazard;
}

bool Model::isLeftTurnSignal() const
{
    return leftTurnSignal;
}
void Model::setLeftTurnSignal(bool) { }

bool Model::isRightTurnSignal() const
{
    return rightTurnSignal;
}
void Model::setRightTurnSignal(bool) { }

void Model::setRegenEn(bool) { }

void Model::setLowPowerEn(bool on) { }

bool Model::isHazards()      const { return hazard; }
bool Model::isCruiseEn()     const { return cruise; }
bool Model::isRegenEn()      const { return regen; }
bool Model::isCruiseInc()    const { return HAL_GPIO_ReadPin(USR_BTN_7_GPIO_Port, USR_BTN_7_Pin) == GPIO_PIN_RESET; }
bool Model::isCruiseDec()    const { return HAL_GPIO_ReadPin(USR_BTN_8_GPIO_Port, USR_BTN_8_Pin) == GPIO_PIN_RESET; }
bool Model::isLowPowerMode() const { return lowPower; }


#endif
