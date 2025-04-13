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
    return true;
}
#else
#include "main.h"

bool Model::isRightTurnSignal() {
    return HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9);
}

bool Model::isLeftTurnSignal() {
    return HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_10);
}
#endif