#include "Arduino.h"
#include "Motor.h"

using namespace SumoMotor;

Motor::Motor(){
}

Motor::~Motor(){
}

bool Motor::Set(uint8_t p_sinal1, uint8_t p_sinal2, uint8_t p_pwm, IdMotor p_id, bool p_inverte){
  switch(p_id){
    case IdMotor::TB66:
      pinoSinal[0] = p_sinal1;
      pinoSinal[1] = p_sinal2;
      pinoPwm = p_pwm;
      inverter = p_inverte;
      id = p_id;
      return true;
    break;
    case IdMotor::L298N:
      return Set(p_sinal1, p_pwm, p_id, p_inverte);
    break;
  }
}

bool Motor::Set(uint8_t p_sinal, uint8_t p_pwm, IdMotor p_id, bool p_inverte){
  switch (p_id){
    case IdMotor::TB66:
      Serial.println("CONFIGURAÇÃO DE ID INCORRETA");
      return false;
    break;
    case IdMotor::L298N:
      pinoSinal[0] = p_sinal;
      pinoPwm = p_pwm;
      inverter = p_inverte;
      id = p_id;
      return true;
    break;
  }
}

void Motor::Movimenta(uint8_t p_pwm, Sentido p_sentido){
  switch(id){
    case IdMotor::L298N:
      L298N_Movimenta(p_pwm, p_sentido);
    break;
    case IdMotor::TB66:
      TB66_Movimenta(p_pwm, p_sentido);
    break;
  }
}

void Motor::L298N_Movimenta(uint8_t p_pwm, Sentido p_sentido){
  switch(p_sentido){
    case Sentido::HORARIO:
      if(!inverter){
        digitalWrite(pinoSinal[0], LOW);
        analogWrite(pinoPwm, p_pwm);
      } else {
        digitalWrite(pinoSinal[0], HIGH);
        analogWrite(pinoPwm, 255-p_pwm);
      }
    break;
    case Sentido::ANTI_HORARIO:
      if(!inverter){
        digitalWrite(pinoSinal[0], HIGH);
        analogWrite(pinoPwm, 255-p_pwm);
      } else {
        digitalWrite(pinoSinal[0], LOW);
        analogWrite(pinoPwm, p_pwm);
      }
    break;
  }
}

void Motor::TB66_Movimenta(uint8_t p_pwm, Sentido p_sentido){
  switch(p_sentido){
    case Sentido::HORARIO:
      if(!inverter){
        digitalWrite(pinoSinal[0], LOW);
        digitalWrite(pinoSinal[1], HIGH);
        analogWrite(pinoPwm, p_pwm);
      } else {
        digitalWrite(pinoSinal[0], HIGH);
        digitalWrite(pinoSinal[1], LOW);
        analogWrite(pinoPwm, p_pwm);
      }
    break;
    case Sentido::ANTI_HORARIO:
      if(!inverter){
        digitalWrite(pinoSinal[0], HIGH);
        digitalWrite(pinoSinal[1], LOW);
        analogWrite(pinoPwm, p_pwm);
      } else {
        digitalWrite(pinoSinal[0], LOW);
        digitalWrite(pinoSinal[1], HIGH);
        analogWrite(pinoPwm, p_pwm);
      }
    break;
  }
}