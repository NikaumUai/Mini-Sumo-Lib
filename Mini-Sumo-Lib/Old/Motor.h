#pragma once

#include <Arduino.h>

namespace SumoMotor{
  enum class IdMotor{
    TB66,
    L298N,
    INVALID
  };

  enum class Sentido{
    HORARIO,
    ANTI_HORARIO,
    INVALID
  };

  class Motor{
    private:
      uint8_t pinoSinal[2];
      uint8_t pinoPwm;
      bool inverter;
      IdMotor id;
    public:
      Motor();
      ~Motor();

      bool Set(uint8_t, uint8_t, uint8_t, IdMotor, bool);
      bool Set(uint8_t, uint8_t, IdMotor, bool);
      void Movimenta(uint8_t, Sentido);
      void L298N_Movimenta(uint8_t, Sentido);
      void TB66_Movimenta(uint8_t, Sentido);
  };
}