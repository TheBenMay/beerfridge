
float temp=12.2;

//The curl command is curl --data "db=m&t=i_t&te=12.2" http://my_web_server/my_script.php
//We must escape the "
//db=m this is for switching between a mysql database and a sqlite database
//t=i_t this means "task=insert temperature"
//te=12.2 this is the temperature we want to insert

String  s = F("curl --data \"db=m&t=i_t&te=");
s += tem_act;
s +="\" http://my_web_Server/my_script.php";

String result=doCurl(command);
