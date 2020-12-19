unsigned long MS;
unsigned long start;

void setup()
{
  Serial.begin (9600);                  // Serial.begin (115200);
  start=millis();
}

void loop()
{
  MS = millis()-start;
/*
  centitot1 = (MS % 1000) / 10 ;        // centieme to display
  secotot1 = (MS / 1000) % 60 ;         // second to display
  minutot1 = (MS / 1000) / 60 ;         // minute to display
*/
  Serial.print ((MS / 1000) / 60);      // minutes
  Serial.print ("' ");
  Serial.print ((MS / 1000) % 60);      // secondes
  Serial.print ("'' ");
  Serial.println (MS % 1000);           // millièmes
}
