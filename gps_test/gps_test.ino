


// To see the position of the the value displayed in the serial monitor:
//      copy past the string from the serial to the site below:
//                          https://rl.se/gprmc



#include <AltSoftSerial.h>   // import AltSoftSerial lib
AltSoftSerial altSerial;     // create object of type AltSoftSerial


// AltSoftSerial always uses these pins:
// Board          Transmit    Receive      PWM Unusable
//  -----          --------    -------      ------------
// Uno                9            8           10
// Mega               46          48          (44, 45)

void setup() {               // put your setup code here, to run once:
  Serial.begin(115200);
  altSerial.begin(9600);
}

void loop() {                // put your main code here, to run repeatedly:
  while(altSerial.available()){
  Serial.write(altSerial.read());
  
  
  }
  Serial.println("");
  delay(2000);
  
}
