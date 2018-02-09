/*
 * Soundtouch Nerf Next target !!!
 * https://github.com/T3kstiil3/soundtouch-nerf-target
 * © Aurélien Loyer :D
 */

#include <Bridge.h>
#include <Console.h>
#include <HttpClient.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

const int statusLED = 13;
const int switchTilt = 2;
int val = 0;

const int port = 8090;
// edit with your soundtouch ip 
const String soundtouchIP = "10.0.10.166";
const String url = "http://" + soundtouchIP + ":8090/key";
const String data = "<?xml version='1.0' encoding='UTF-8' ?><key state='release' sender='Gabbo'>NEXT_TRACK</key>";
const String curlcommand = "curl -H 'Content-Type: application/xml' -X POST -d \"<?xml version='1.0' encoding='UTF-8' ?><key state='press' sender='Gabbo'>NEXT_TRACK</key>\" http://" + soundtouchIP + ":8090/key";

void setup() {
  Serial.begin(9600);

  pinMode (statusLED,OUTPUT);
  pinMode (switchTilt,INPUT);

  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop()
{

  YunClient client = server.accept();
  
  val = digitalRead(switchTilt);
  if (val == HIGH){
    digitalWrite(statusLED,HIGH);
    nextTrack();
    delay(30000); // 30 secondes avant le prochain changement !
  }
  else {
    digitalWrite(statusLED,LOW);
  }

  //Process Client Requests
  if (client) {
    process(client);
    client.stop();
  }

  delay(15);
}

void nextTrack() {
  Process p; 
  p.runShellCommand(curlcommand);
}

void process(YunClient client) {
  String command = client.readStringUntil('\r');
}

