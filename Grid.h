
#ifndef Controller_HEADER
#define Controller_HEADER

class Grid {
private:
    double powerSold;
    double powerBought;
    double voltage;
    double frequency;

public:
    Grid(double sold, double bought, double voltage, double frequency);

    double getPowerSold();
    double getPowerBought();
    double getVoltage();
    double getFrequency();

    void sellPower(double power);
    void buyPower(double power);
};

#endif
