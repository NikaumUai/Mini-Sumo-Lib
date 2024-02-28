#pragma once

namespace SumoMotor{
    enum class DriverId{
        DRV8874,
        L298N,
        INVALID
    };

    class MotorDriver{
        private:
            int signalPins[2];
            int pwmPins[2];
            DriverId id;
        
        public:
            int teste;
            MotorDriver();
            ~MotorDriver();

            int GetPin(int r_pin);
            bool SetPin(int r_pin, int u_pin);
            DriverId GetId();
            bool SetId(DriverId u_id);
            void Controls(int u_pwm);
    };
}