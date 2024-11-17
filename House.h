#ifndef BAA_HEADER
#define BAA_HEADER
class House {
private:
    double powerConsumed;
    double voltage;
    double frequency;
    double current;

public:
    House(double voltage, double frequency, double current);
    double getPowerConsumed();
    double getVoltage();
    double getFrequency();
    double getCurrent();
};
#endif
