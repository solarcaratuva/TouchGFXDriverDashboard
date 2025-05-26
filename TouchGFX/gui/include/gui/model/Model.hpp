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
};

#endif // MODEL_HPP
