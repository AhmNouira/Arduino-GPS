// Simple Arduino GPS Location 

// Inlucde the necessart libraries

#include <SoftwareSerial.h>                      // to use a pesudo serial interface (uart) 
#include <TinyGPS.h>                             // to handle the problem of converting NMEA sentances


// Define the Arduino pins 
#define Rx_gps_pin 8 
#define Tx_gps_pin 9

const double HOME_Lon = 10.8161;


const  double HOME_Lat = 35.7668;


// Define variables and const
#define parse_wait  3000                        // wait for 3 seconds



SoftwareSerial GPS_SS(Rx_gps_pin, Tx_gps_pin);  // create an instance of the SoftwareSerial
TinyGPS gps;                                    // create object of type TinyGPS


void setup() {                                  // put your setup code here, to run once:
  Serial.begin(115200);
  GPS_SS.begin(9600);                           // GPS module serial bit rate 
}

void loop() {                                   // put your main code here, to run repeatedly:

  bool newData = false;                         // new record ?  
  unsigned long chars;          // number of characters to feed => needed for stats() function
  unsigned short sentences;
  unsigned short failed;
  
  // parse (be sure) GPS data for 3 seconds 
  for (unsigned long start = millis(); millis() - start < parse_wait; ) {
    while ( GPS_SS.available()) {                 // valid data
      char c = GPS_SS.read();                     // read data form GPS_SS
      if (gps.encode(c))  {                       // is the sentance valid ? 
      newData = true;                             // record data
      //Serial.println("New Data Recorded");                   
      }
    }
  }

  if (newData) {                                  // if there is a Data 

   // Extract the GPS data from the received sentances 
   float lat;                                      // latitude
   float lon;                                      // longtitude
   unsigned long age;                              //  age !
   String month_;
   gps.f_get_position(&lat, &lon, &age);           // get the current position
   int year;        // year
   byte month, day, hour, minute, second, hundredths;
   gps.crack_datetime ( &year, &month, &day, &hour, &minute, & hundredths);   // get the current datetime
   float alt = gps.f_altitude();                   // get altitude 
   float Speed = gps.f_speed_kmph();               // get the speed of deplacment 
   double distance = TinyGPS::distance_between(HOME_Lat, HOME_Lon, lat, lon); 

   // send the data to serial
   // print time 
   Serial.print("Time = ");Serial.print(hour + 1, DEC);Serial.print(":");
   Serial.print(minute, DEC);Serial.print(":");Serial.println(second, DEC);

   switch(month) {
    case 1: month_  = "January";break;
    case 2: month_  = "February";break;
    case 3: month_  = "March"; break;
    case 4: month_  = "April"; break;
    case 5: month_  = "May";break;
    case 6: month_  = "June";break;
    case 7: month_  = "July";break;
    case 8: month_  = "August"; break;
    case 9: month_  = "September";break;
    case 10: month_ = "October";break;
    case 11: month_ = "November";break;
    case 12: month_ = "December"; break;    
   }


   // pirnt day 
   Serial.print("Day = ");Serial.print(day); Serial.print(", ");Serial.print(month_);
   Serial.print(" ");Serial.println(year);

   // print Latitude 
   Serial.print("Latitude = ");Serial.println(lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat, 4);

   // print Longtitude
   Serial.print ("Longtitude = ");Serial.println(lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon, 4);

   // print altitude 
   // Serial.print("Altitude =");Serial.println(alt == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : alt);

    // print Distance to my house LOL  
    Serial.print(">LOL> >>> Distance To My House: ");Serial.print(distance);Serial.println("m");
    Serial.print("                                ");Serial.print(distance/1000);Serial.println("Km"); 
    //print speed 
   Serial.print("Speed = "); Serial.print(Speed);Serial.println("Km/Hr");
   

   Serial.println("\n"); 
   delay(1000);  // wait 1 second between affichage 
  }
  
}
