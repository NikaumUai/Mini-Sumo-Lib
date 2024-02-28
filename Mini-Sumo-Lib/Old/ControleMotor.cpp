#include "ControleMotor.h"
#include "SumoMath.h"

using namespace SumoMotor;

ControleMotor::ControleMotor(){
}

ControleMotor::~ControleMotor(){
}

void ControleMotor::InicializarCondicaoInicial(){
  velocidade[0] = 0;
  velocidade[1] = 0;
  pwm[0] = 0;
  pwm[1] = 0;
  sentido[0] = {Sentido::INVALID};
  sentido[1] = {Sentido::INVALID};
}

void ControleMotor::Set(uint8_t m1_sinal1, uint8_t m1_sinal2, uint8_t m1_pwm, IdMotor m1_id, uint8_t m2_sinal1, uint8_t m2_sinal2, uint8_t m2_pwm, IdMotor m2_id, RodasInvertidas inverte){
  InicializarCondicaoInicial();

  switch(inverte){
    case RodasInvertidas::AMBAS:
      motores[LadoMotor::DIREITA].Set(m1_sinal1, m1_sinal2, m1_pwm, m1_id, true);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal1, m2_sinal2, m2_pwm, m2_id, true);
    break;
    case RodasInvertidas::DIREITA:
      motores[LadoMotor::DIREITA].Set(m1_sinal1, m1_sinal2, m1_pwm, m1_id, true);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal1, m2_sinal2, m2_pwm, m2_id, false);
    break;
    case RodasInvertidas::ESQUERDA:
      motores[LadoMotor::DIREITA].Set(m1_sinal1, m1_sinal2, m1_pwm, m1_id, false);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal1, m2_sinal2, m2_pwm, m2_id, true);
    break;
    case RodasInvertidas::INVALID:
      motores[LadoMotor::DIREITA].Set(m1_sinal1, m1_sinal2, m1_pwm, m1_id, false);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal1, m2_sinal2, m2_pwm, m2_id, false);
    break;
  }
}

void ControleMotor::Set(uint8_t m1_sinal1, uint8_t m1_sinal2, uint8_t m1_pwm, IdMotor m1_id, uint8_t m2_sinal1, uint8_t m2_sinal2, uint8_t m2_pwm, IdMotor m2_id){
  InicializarCondicaoInicial();

  motores[LadoMotor::DIREITA].Set(m1_sinal1, m1_sinal2, m1_pwm, m1_id, false);
  motores[LadoMotor::ESQUERDA].Set(m2_sinal1, m2_sinal2, m2_pwm, m2_id, false);
}

void ControleMotor::Set(uint8_t m1_sinal, uint8_t m1_pwm, IdMotor m1_id, uint8_t m2_sinal, uint8_t m2_pwm, IdMotor m2_id, RodasInvertidas inverte){
  InicializarCondicaoInicial();

  switch(inverte){
    case RodasInvertidas::AMBAS:
      motores[LadoMotor::DIREITA].Set(m1_sinal, m1_pwm, m1_id, true);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal, m2_pwm, m2_id, true);
    break;
    case RodasInvertidas::DIREITA:
      motores[LadoMotor::DIREITA].Set(m1_sinal, m1_pwm, m1_id, true);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal, m2_pwm, m2_id, false);
    break;
    case RodasInvertidas::ESQUERDA:
      motores[LadoMotor::DIREITA].Set(m1_sinal, m1_pwm, m1_id, false);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal, m2_pwm, m2_id, true);
    break;
    case RodasInvertidas::INVALID:
      motores[LadoMotor::DIREITA].Set(m1_sinal, m1_pwm, m1_id, false);
      motores[LadoMotor::ESQUERDA].Set(m2_sinal, m2_pwm, m2_id, false);
    break;
  }
}

void ControleMotor::Set(uint8_t m1_sinal, uint8_t m1_pwm, IdMotor m1_id, uint8_t m2_sinal, uint8_t m2_pwm, IdMotor m2_id){
  InicializarCondicaoInicial();

  motores[LadoMotor::DIREITA].Set(m1_sinal, m1_pwm, m1_id, false);
  motores[LadoMotor::ESQUERDA].Set(m2_sinal, m2_pwm, m2_id, false);
}

void ControleMotor::SetPwm(double i_velocidadeDireita, double i_velocidadeEsquerda){
  pwm[LadoMotor::DIREITA] = (SetVelocidade(i_velocidadeDireita, LadoMotor::DIREITA)) ? CalculaPwm(LadoMotor::DIREITA) : pwm[LadoMotor::DIREITA];
  pwm[LadoMotor::ESQUERDA] = (SetVelocidade(i_velocidadeEsquerda, LadoMotor::ESQUERDA)) ? CalculaPwm(LadoMotor::ESQUERDA) : pwm[LadoMotor::ESQUERDA];
}

bool ControleMotor::SetVelocidade(double i_velocidade, LadoMotor lado){
  int velocidade_antiga = velocidade[lado];
  velocidade[lado] = (i_velocidade > 100) ? 100 : (i_velocidade < 0) ? 0 : i_velocidade;
  return (velocidade[lado] != velocidade_antiga);
}

int ControleMotor::CalculaPwm(LadoMotor lado){
  return (SumoMath::QSqrt(velocidade[lado])*255);
}

void ControleMotor::On(SumoMotor::Sentido sentido){
    motores[LadoMotor::DIREITA].Movimenta(pwm[LadoMotor::DIREITA], sentido);
    motores[LadoMotor::ESQUERDA].Movimenta(pwm[LadoMotor::DIREITA], sentido);
    return;
}
