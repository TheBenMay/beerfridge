#include <Process.h>
int led = 13;
int i = 1;
String theTemp = "100";
String command;
String tempParam;
String sendTemp;
String getParam;
int getValue;

void setup() {
  Serial.begin(9600);
  Bridge.begin();
  pinMode(led, OUTPUT);
//  Process p;            
//  p.begin("curl");      
//  p.addParameter("http://192.168.1.202/listen2.php?changeTemp=22"); 
//  p.run();
}


void loop() {
  tempParam = "http://192.168.1.202/listen2.php?temp=";
  sendTemp = tempParam + theTemp;
  getParam = "curl http://192.168.1.202/listen2.php?getTemp=1";
//  Process t;
//  t.begin("curl");
//  t.addParameter(sendTemp);
////  t.run();

Process g;
g.runShellCommand(getParam);
while(g.running());  //Wait
  String result="";
  while (g.available()>0) {
   char c=g.read();
   result=result +c;
   theTemp = result;
  }
  
  Process t;
  t.begin("curl");
  t.addParameter(sendTemp);
  t.run();
  delay(5000);
}
