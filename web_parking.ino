#include <Ethernet.h>
#include<SPI.h>
#include <Servo.h>

Servo servo;

//declare variables for the data
int available1;
int available2;
int available3;

//distance for the ultrasonic sensor to the car object
long distance1;
long distance2;
long distance3;

//duration at which the sensor transmits the ultrasonic waves
long duration1;
long duration2;
long duration3;

//opening the servo so that cars enter

long servoduration;
long servodistance;

//input pins for the sensor
#define echo1  27
#define echo2  31
#define echo3  35

//the output pins for the sensor
#define trig1  26
#define trig2  30
#define trig3  34

//the out and in pins for the sensor
#define servotrig 40
#define servoecho 41

IPAddress ip(10,51,14,223);

//ethernet datapins
char server[] = "10.51.14.217";


//default computer address
byte mac[]={
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

int response;
EthernetClient client;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.println("Connecting.....");
  // else {
    //Serial.print("  DHCP assigned IP ");
    //Serial.println(Ethernet.localIP());
     // give the Ethernet shield a second to initialize:
  delay(1000);
  IPAddress ip = Ethernet.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

 
  //defining the modes of the pins for the sensor
  
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(trig3,OUTPUT);
 
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(echo3,INPUT);
  
  pinMode(servotrig,OUTPUT);
  pinMode(servoecho,INPUT);
  servo.attach(37);

}

void loop() {
  //finding the distance for each of the sensors
  digitalWrite(trig1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
  digitalWrite(trig2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2/2) / 29.1;
  
  digitalWrite(trig3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = (duration3/2) / 29.1;

  Serial.print("Distance 1:");
  Serial.print(distance1);
  Serial.println("cm");
  Serial.print("Distance 2:");
  Serial.print(distance2);
  Serial.println("cm");
  Serial.print("Distance 3:");
  Serial.print(distance3);
  Serial.println("cm");

  //getting the actual value required to do the project successfully
 
  if(distance1<6)
  {
    available1=0;
  }
  else{
    available1 =1;
  }   
  if(distance2<6)
  {
    available2=0;
  }
  else{
    available2 =1;
  }
  if(distance3<6)
  {
    available3=0;
  }
  else{
    available3 =1;
  }
  digitalWrite(servotrig, LOW);  
  delayMicroseconds(2); 
  digitalWrite(servotrig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(servotrig, LOW);
  servoduration = pulseIn(servoecho, HIGH);
  
    if(servodistance<10)
  {
    servo.write(90);
  }
  else
  {
    servo.write(-90);
  }
  //passing the variables to the php page.
  if (!client.connected()) 
    {
      Serial.print("available1=");
      Serial.println(available1);
      Serial.print("available2=");
      Serial.println(available2);
      Serial.print("available3=");
      Serial.println(available3);
      client.stop();
     delay(1000);

      if (client.connect(server, 80)) 
      {
        
        Serial.println("Connected ");
        // Make a HTTP request:
        client.print("GET /Parking/updateavailability.php?position=");
        client.print("1");
        client.print("&&");
        client.print("available=");
        client.print(available1);
        client.println(" HTTP/1.1");
        client.println("Host: 10.51.14.217");
        client.println("Connection: close");
        client.println();
        client.stop();
       } 
      else 
      {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
      }
      if (client.connect(server, 80)) 
      {
        
        Serial.println("connected");
       
        // Make a HTTP request:
        client.print("GET /Parking/updateavailability.php?position=");
        client.print("2");
        client.print("&&");
        client.print("available=");
        client.print(available2);
        client.println(" HTTP/1.1");
        client.println("Host: 10.51.14.217");
        client.println("Connection: close");
        client.println();
        client.stop();
       } 
      else 
      {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
      }
      if (client.connect(server, 80)) 
      {
        Serial.println("connected");
        // Make a HTTP request:
        client.print("GET /Parking/updateavailability.php?position=");
        client.print("3");
        client.print("&&");
        client.print("available=");
        client.print(available3);
        client.println(" HTTP/1.1");
        client.println("Host: 10.51.14.217");
        client.println("Connection: close");
        client.println();
        client.stop();
       } 
      else 
      {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
      }
         
      
    }
}
