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

bool Model::isHazards()         const { return false; }
bool Model::isCruiseEn()        const { return false; }
bool Model::isRegenEn()         const { return false; }
bool Model::isCruiseInc()       const { return false; }
bool Model::isCruiseDec()       const { return false; }
bool Model::isLowPowerMode()    const { return false; }

#else

#include "main.h"

Model::Model() : modelListener(0) { }

void Model::tick() { }

bool Model::isLeftTurnSignal() const
{
    return HAL_GPIO_ReadPin(USR_BTN_3_GPIO_Port, USR_BTN_3_Pin) == GPIO_PIN_SET;
}
void Model::setLeftTurnSignal(bool) { }

bool Model::isRightTurnSignal() const
{
    return HAL_GPIO_ReadPin(USR_BTN_2_GPIO_Port, USR_BTN_2_Pin) == GPIO_PIN_SET;
}
void Model::setRightTurnSignal(bool) { }

bool Model::isHazards()      const { return HAL_GPIO_ReadPin(USR_BTN_4_GPIO_Port, USR_BTN_4_Pin) == GPIO_PIN_SET; }
bool Model::isCruiseEn()     const { return HAL_GPIO_ReadPin(USR_BTN_5_GPIO_Port, USR_BTN_5_Pin) == GPIO_PIN_SET; }
bool Model::isRegenEn()      const { return HAL_GPIO_ReadPin(USR_BTN_6_GPIO_Port, USR_BTN_6_Pin) == GPIO_PIN_SET; }
bool Model::isCruiseInc()    const { return HAL_GPIO_ReadPin(USR_BTN_7_GPIO_Port, USR_BTN_7_Pin) == GPIO_PIN_SET; }
bool Model::isCruiseDec()    const { return HAL_GPIO_ReadPin(USR_BTN_8_GPIO_Port, USR_BTN_8_Pin) == GPIO_PIN_SET; }
bool Model::isLowPowerMode() const { return HAL_GPIO_ReadPin(USR_BTN_9_GPIO_Port, USR_BTN_9_Pin) == GPIO_PIN_SET; }

#endif
