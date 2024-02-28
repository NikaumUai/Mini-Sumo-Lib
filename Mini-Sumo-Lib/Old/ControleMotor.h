#pragma once

#include <Arduino.h>
#include "Motor.h"

namespace SumoMotor{
  typedef struct{
    uint8_t VELOCIDADE_MAXIMA = 100;
    uint8_t RESOLUCAO_PWM = 255;
    uint8_t DISTANCIA_RODAS = 60;
  } MotorDefinicoes;

  typedef enum{
    DIREITA,
    ESQUERDA,
    INVALID 
  }LadoMotor;

  enum class RodasInvertidas{
    DIREITA,
    ESQUERDA,
    AMBAS,
    INVALID
  };

  enum class ModoMovimento{
    NORMAL,
    ACELERADO,
    SONDADO,
    SONDADO_ACELERADO,
    UMA_RODA,
    UMA_RODA_SONDADO,
    RE,
    RE_ACELERADO,
    RE_SONDADO,
    RE_SONDADO_ACELERADO,
    RE_UMA_RODA,
    RE_UMA_RODA_SONDADO,
    INVALID
  };

  class ControleMotor{
    private:
      Motor motores[2];

      double velocidade[2];
      double pwm[2];
      Sentido sentido[2];

      const MotorDefinicoes defs;

      void SetPwm(double, double);
      bool SetVelocidade(double, LadoMotor);
      int CalculaPwm(LadoMotor);
      void InicializarCondicaoInicial();

    public:
      ControleMotor();
      ~ControleMotor();

      void Set(uint8_t, uint8_t, uint8_t, IdMotor, uint8_t, uint8_t, uint8_t, IdMotor, RodasInvertidas);
      void Set(uint8_t, uint8_t, uint8_t, IdMotor, uint8_t, uint8_t, uint8_t, IdMotor);
      void Set(uint8_t, uint8_t, IdMotor, uint8_t, uint8_t, IdMotor, RodasInvertidas);
      void Set(uint8_t, uint8_t, IdMotor, uint8_t, uint8_t, IdMotor);

      int GetVelocidade();
      int GetPwm();

      bool Frente(uint8_t, uint16_t, ModoMovimento);
      bool Direita(uint8_t, uint16_t, uint16_t, ModoMovimento);
      bool Direita(uint8_t, uint16_t, ModoMovimento);
      bool Esquerda(uint8_t, uint16_t, uint16_t, ModoMovimento);
      bool Esquerda(uint8_t, uint16_t, ModoMovimento);
  };
}