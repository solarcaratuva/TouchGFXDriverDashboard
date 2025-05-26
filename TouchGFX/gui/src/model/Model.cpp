#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

#ifdef SIMULATOR
bool Model::isRightTurnSignal() {
    return rightTurnSignal; 
}

bool Model::isLeftTurnSignal() {
    return leftTurnSignal;
}

bool Model::isHazards() {
    return false;
}

bool Model::isCruiseEn() {
    return false;
}

bool Model::isRegenEn() {
    return false;
}

bool Model::isCruiseInc() {
    return false;
}

bool Model::isCruiseDec() {
    return false;
}

bool Model::isLowPowerMode() {
    return false;
}

void Model::setLeftTurnSignal(bool on)
{
    leftTurnSignal = on;
}

void Model::setRightTurnSignal(bool on)
{
    rightTurnSignal = on;
}


#else
#include "main.h"

bool Model::isRightTurnSignal() {
    #ifdef SIMULATOR
        return rightTurnSignal;
    #else
        return HAL_GPIO_ReadPin(USR_BTN_2_GPIO_Port, USR_BTN_2_Pin) == GPIO_PIN_SET;
    #endif
}

// void Model::setRightTurnSignal() {
    
// }

bool Model::isLeftTurnSignal() {
    return HAL_GPIO_ReadPin(USR_BTN_3_GPIO_Port, USR_BTN_3_Pin) == GPIO_PIN_SET;
}

bool Model::isHazards() {
    return HAL_GPIO_ReadPin(USR_BTN_4_GPIO_Port, USR_BTN_4_Pin) == GPIO_PIN_SET;
}

bool Model::isCruiseEn() {
    return HAL_GPIO_ReadPin(USR_BTN_5_GPIO_Port, USR_BTN_5_Pin) == GPIO_PIN_SET;
}

bool Model::isRegenEn() {
    return HAL_GPIO_ReadPin(USR_BTN_6_GPIO_Port, USR_BTN_6_Pin) == GPIO_PIN_SET;
}

bool Model::isCruiseInc() {
    return HAL_GPIO_ReadPin(USR_BTN_7_GPIO_Port, USR_BTN_7_Pin) == GPIO_PIN_SET;
}

bool Model::isCruiseDec() {
    return HAL_GPIO_ReadPin(USR_BTN_8_GPIO_Port, USR_BTN_8_Pin) == GPIO_PIN_SET;
}

bool Model::isLowPowerMode() {
    return HAL_GPIO_ReadPin(USR_BTN_9_GPIO_Port, USR_BTN_9_Pin) == GPIO_PIN_SET;
}

#endif