
//This function executes a curl command. You can use it to make a rest request.
String doCurl(String COM) {
 Process p;
 p.runShellCommand(COM);
 while (p.running());//Wait for the process to finish
 String result;

 if (p.exitValue() == 0) {
   while (p.available() > 0) {
     char c = p.read();
     result += c;
   }
 }
 else {
   resultado = F("ErrorCurl:");
   result += p.exitValue();
 }
 return result;
}
