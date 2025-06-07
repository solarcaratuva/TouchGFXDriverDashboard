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

    bool isLeftTurnSignal() const;
    bool isRightTurnSignal() const;
    bool isHazards() const;
    bool isRegenEn() const;
    bool isCruiseEn() const;
    bool isCruiseInc() const;
    bool isCruiseDec() const;
    bool isLowPowerMode() const;

    void setLeftTurnSignal(bool on);
    void setRightTurnSignal(bool on);
    void setRegenEn(bool on);
    void setLowPowerEn(bool on);

protected:
    ModelListener* modelListener;

private:
    bool leftTurnSignal = false;
    bool rightTurnSignal = false;
    bool regen = false;
    bool lowPower = false;
    bool cruise = false;
    bool hazard = false;

    bool prevLeftButtonState = true;
    bool prevRightButtonState = true;
    bool prevLowPowerButtonState = true;
    bool prevRegenButtonState = true;
    bool prevCruiseButtonState = true;
    bool prevHazardButtonState = true;

};

#endif // MODEL_HPP
