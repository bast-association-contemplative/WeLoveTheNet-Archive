#include <Process.h>
#include <Bridge.h>
#include <Console.h>
#include <Servo.h>

Servo petard;

void setup() {
  Bridge.begin();
  Console.begin();

  petard.attach(9);
  petard.write(90);
}

void loop() {
  Process p;
  p.runShellCommand("/usr/bin/curl http://www.anabole.com/datadada/pingouin.php?id=5");
  Console.println("run curl command");

  while (p.running());

  while (p.available()) {
    int result = p.parseInt();          // look for an integer
    Serial.print(result);
    Console.println(result);

    if (result == 1) {
      petard.write(45);
      delay(1665);
      petard.write(90);                  // stop
    } else {
      petard.write(90);                  // stop
    }
  }
}
