#include "SumoMath.h"

bool done = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(SumoMath::QSqrt(10));
}
