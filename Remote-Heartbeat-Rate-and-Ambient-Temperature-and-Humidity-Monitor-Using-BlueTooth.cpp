
//for the project details, email at navid_bin_ahmed@yahoo.com

// for DHT11, VCC: 5V or 3V GND: GND; DATA: 5

#include <DHT.h>
//#include <SimpleDHT.h>
//int pinDHT11 = 2;
#define pinDHT11 2
#define DHTTYPE DHT11
DHT dht(pinDHT11, DHTTYPE);
//SimpleDHT11 dht11(pinDHT11);

//pulse initialization code
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
const int PulseWire = A4;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value.                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

//blutooth data transmission for both - pulse and then dht
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10,11); //Tx, Rx

char inchar; // Will hold the incoming character from the GSM shield
String TextForSms ;
String MyBPM= "Heartbeat" ;
//String sign = "  BPM"; 
String humidity = "   %";
String temperature = "   Temperature";
//String sign = "  deg C";
int powerb = 6; // to power up the dht11 sensor, dht11 5v wire is connected with pin6 of the arduino. 

/* "Drawing" the degree symbol
byte degreesymbol[8] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000  
};*/



void setup() {
// initialize digital pin LED_BUILTIN as an output.
  //pinMode(pinDHT11, OUTPUT);
  Serial.begin(115200);
  BTserial.begin(9600); 
  pinMode(powerb, OUTPUT);
  digitalWrite(powerb,HIGH);
  
// Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
// Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
//Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
    } 
    }
   /*
   void delay2(unsigned long ms){
  unsigned long start = micros();
  while (micros() - start <= ms);

    }
*/
void loop()  {  

int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".myBPM" hold this BPM value now. 
if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
Serial.print("Pulse Rate: "); Serial.print(myBPM );Serial.print(" BPM, ");  // If test is "true", print a message "a heartbeat happened".Print phrase "Heartbeat: ". Print the value inside of myBPM.
   delay(200); }                   // considered best practice in a simple sketch.
  
  //dht code part                    //Serial.println("Sample DHT11...");

byte     temperature = 0;
byte     humidity = 0;   //byte instead
  /*int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return; }*/
  temperature = dht.readTemperature ()-3;
  humidity = dht.readHumidity ()+43; 

  Serial.print("at Temperature: ");  Serial.print((int)temperature ); Serial.print(" deg C, ");  
  //Serial.print( degreesymbol[8]); 
  Serial.print("and Humidity: ");  Serial.print((int)humidity); Serial.println(" %");
  // DHT11 sampling rate is 1HZ.
  delay(1000);
 

//transmission part 
if(BTserial.available() == 0);
  if(BTserial.available() >0)
  {
    inchar=BTserial.read(); 
  Serial.println(inchar);
    delay(20);
    if (inchar=='K')    
    {
      delay(10);
 
   Serial.println(inchar);

   delay(500); 
   
  TextForSms = TextForSms+"Pulse Rate: ";
  TextForSms.concat(myBPM);
  TextForSms = TextForSms + " BPM,";
  
  TextForSms = TextForSms + "at Temperature: ";
  TextForSms.concat(temperature);
  TextForSms = TextForSms + " deg C, ";

  TextForSms = TextForSms + "and Humidity: ";
  TextForSms.concat(humidity);
  TextForSms = TextForSms + " %.";
  TextForSms = TextForSms +  "        To receive data again, please type 'S' and click on Send. Thank you.";  
 
  BTserial.print(TextForSms);
  Serial.println(TextForSms);
  delay(1000);
  TextForSms = " ";
    }                   
    }
}
