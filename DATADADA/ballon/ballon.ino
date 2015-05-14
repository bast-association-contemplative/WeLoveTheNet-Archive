#include <Process.h>
#include <Bridge.h>
#include <Console.h>

const int relais = 10;
String requete;
String res;
String pourcentage;

void setup() {
  Bridge.begin();
  Console.begin();
  Serial.begin(9600);
  
  pinMode(relais, OUTPUT);
  digitalWrite(relais, HIGH);
}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl http://mathemagie.net/projects/grossetete/results.php");
  Serial.println("run curl command");
  
  while (p.running());
    while (p.available()) {
      int result;
      result = p.parseInt();
      String ensemble_de_la_requete = String(result);
      
      // On test si il y a une nouvelle requete.
      requete = ensemble_de_la_requete.substring(0, 1);
      
      //Si il y a une nouvelle requete (requete = 1)
      if(requete == "1"){
         Serial.println("Une requete arrive!");
        
        // On attend 1 = Sourir ou 2 = Pas de sourir.
        res = ensemble_de_la_requete.substring(1, 2);
          Serial.println(res);
        
        // On attend un pourcentage (0% a 100%) 
        pourcentage = ensemble_de_la_requete.substring(2, 5);
          Serial.println(pourcentage);
          
          // Si il y a un Sourir
          if(res == "1"){
            // Si il y a un Sourir avec un pourcentage suprieur  50% le ballon gonfle un peu.
            if(pourcentage.toInt() > 50){
              digitalWrite(relais, LOW);
              delay (500);
              digitalWrite(relais, HIGH);
              Serial.println("Mega Smile");
            } 
            // Si il y a un Sourir avec un pourcentage inferieur a 50% le ballon gonfle beaucoup, a priori sans exploser!
            else {
              digitalWrite(relais, LOW);
              delay (1000);
              digitalWrite(relais, HIGH);
              Serial.println("Smile");
            }  
          }
         
         // Si il y a pas de Sourir, le ballon explose
         else {
            digitalWrite(relais, LOW);
            delay (2000);
            digitalWrite(relais, HIGH);
            Serial.println("Mega Sad");
          }
          delay (3000);
      }
      // Si il y a pas de nouvelle requete (requete = 2)
      else{
        Serial.println("pas de nouvelle requete");
      }
    };
  delay (3000);
}
