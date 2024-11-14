
class House {
private:
    double powerConsumed;
    double voltage;
    double frequency;
    double current;

public:
    House(double power = 0.0, double voltage = 0.0, double frequency = 0.0, double current = 0.0);
    double getPowerConsumed();
    double getVoltage();
    double getFrequency();
    double getCurrent();
};