#include "MotorDriver.h"

using namespace SumoMotor;

MotorDriver::MotorDriver(){
}

MotorDriver::~MotorDriver(){
}

bool MotorDriver::SetPin(int r_pin, int u_pin){
    if((r_pin >= 0) || (r_pin <= 1)){
        signalPins[r_pin] = (u_pin > 0) ? u_pin : 0;
        return true;
    } else if((r_pin >= 2) || (r_pin <= 3)){
        pwmPins[r_pin-2] = (u_pin > 0) ? u_pin : 0;
        return true;
    } else {
        return false;
    }
}

bool MotorDriver::SetId(DriverId u_id){
    switch(u_id){
        case DriverId::DRV8874:
        case DriverId::L298N:
            id = u_id;
            return true;
        case DriverId::INVALID:
            return false;
    }
}

DriverId MotorDriver::GetId(){
    return id;
}

int MotorDriver::GetPin(int r_pin){
    if((r_pin >= 0) || (r_pin <= 1)){
        return signalPins[r_pin];
    } else if((r_pin >= 2) || (r_pin <= 3)){
        return signalPins[r_pin-2];
    } else {
        return -1;
    }
}
