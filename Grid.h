class Grid {
private:
    double powerSold;
    double powerBought;
    double voltage;
    double frequency;

public:
    Grid(double sold = 0.0, double bought = 0.0, double voltage = 0.0, double frequency = 0.0)
        : powerSold(sold), powerBought(bought), voltage(voltage), frequency(frequency) {}

    double getPowerSold()  { return powerSold; }
    double getPowerBought()  { return powerBought; }
    double getVoltage()  { return voltage; }
    double getFrequency()  { return frequency; }
};

