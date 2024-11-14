
class House {
private:
    double powerConsumed;
    double voltage;
    double frequency;
    double current;

public:
    House(double power, double voltage, double frequency, double current);
    double getPowerConsumed();
    double getVoltage();
    double getFrequency();
    double getCurrent();
};