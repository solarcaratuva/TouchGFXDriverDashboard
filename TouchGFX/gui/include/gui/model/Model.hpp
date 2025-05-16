#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    bool isRightTurnSignal();
    bool isLeftTurnSignal();
    bool isHazards();
    bool isRegenEn();
    // bool isCruiseEn();
    bool isCruiseInc();
    bool isCruiseDec();
    bool isLowPowerMode();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
