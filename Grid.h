
class Grid {
private:
    double powerSold;
    double powerBought;
    double voltage;
    double frequency;

public:
    Grid(double sold = 0.0, double bought = 0.0, double voltage = 0.0, double frequency = 0.0);

    double getPowerSold();
    double getPowerBought();
    double getVoltage();
    double getFrequency();
};

