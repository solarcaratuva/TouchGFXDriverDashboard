#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

#ifdef SIMULATOR
// Simulator stub — return dummy value
bool Model::isRightTurnSignal() {
    return false; 
}

bool Model::isLeftTurnSignal() {
    return false;
}
#else
#include "main.h"

bool Model::isRightTurnSignal() {
    return HAL_GPIO_ReadPin(USR_BTN_2_GPIO_Port, USR_BTN_2_Pin) == GPIO_PIN_SET;
}

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