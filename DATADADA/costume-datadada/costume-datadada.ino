#include <Process.h>
#include <Bridge.h>
#include <Console.h>

//#define ID 204
#define FAN_PIN 13

void setup() {
  Bridge.begin();
  Console.begin();
  Serial.begin(9600);
  
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl http://www.albertinemeunier.net/angelino/tweet/tweetart2m.php?n=204" );
  Serial.println("run curl command");
  
  while (p.running());
    while (p.available()) {
      int result = p.parseInt();
      Serial.println(result);
      Console.println(result);
      
      if (result == 1){
        Serial.println("Event: #");
        //On rentre ici le temps de ventilation (ici : 30sec);
        fan(30000);
      }
      else{digitalWrite(FAN_PIN, LOW);}
    }
  delay (1000);
}

void fan(int time){
  digitalWrite(FAN_PIN, HIGH);
  delay(time);
  digitalWrite(FAN_PIN, LOW);
}
