class Inverter {
private:
    double maxPower;
    double batteryVoltage;
    double batteryCurrent;
    double power;
    double gridFrequency;
    double gridVoltage;

public:
    Inverter(double maxP, double volt, double curr, double gridFreq, double gridVolt);

    void setPower(double p);
    double getMaxPower();
    double getBatteryVoltage();
    double getBatteryCurrent();
    double getPower();
};

