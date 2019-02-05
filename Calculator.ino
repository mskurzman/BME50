/*

Blinkblob 

*/



void setup() {
  //start serial communication
  Serial.begin(115200);

  //give some time to open the serial monitor
  delay(2000);
  Serial.print(F("****************************"));
  Serial.println(F("****************************"));
  Serial.println(F("\tTHE BEST CALCULATOR"));
  Serial.print(F("****************************"));
  Serial.println(F("****************************"));
  Serial.println(); Serial.println();
}

void loop() {

    float a, b, c;
    char operation;
    
        // Inputs
        Serial.println(F("Insert the first number"));
        // WAIT FOR INPUT
        while(Serial.available() == 0)
          delay(10);
        // READ IN PUT
        if (Serial.available() > 0) {
          a = Serial.parseFloat();
         
         // EMPTY BUFFER
         while(Serial.available() > 0)
              Serial.read();
          }

          Serial.print(a);
            Serial.println(F("\t is what was read"));
            Serial.println();

           Serial.println(F("Insert the second number"));
        // WAIT FOR INPUT
        while(Serial.available() == 0)
          delay(10);
        // READ IN PUT
        if (Serial.available() > 0) {
          b = Serial.parseFloat();
         
         // EMPTY BUFFER
         while(Serial.available() > 0)
              Serial.read();
          }

          Serial.print(b);
            Serial.println(F("\t is what was read"));
            Serial.println();


                 Serial.println(F("Insert the operation"));
        // WAIT FOR INPUT
        while(Serial.available() == 0)
          delay(10);
        // READ IN PUT
        if (Serial.available() > 0) {
          operation = Serial.read();
         
         // EMPTY BUFFER
         while(Serial.available() > 0)
              Serial.read();
          }

          Serial.print(operation);
            Serial.println(F("\t is what was read"));
            Serial.println();


    
        // Cases depending on operation input
        if (operation == '+')
        {
            Serial.println(c = a + b); 
        }
        else if (operation == '-')
        {
            Serial.println(c = a - b);
        }
        else
        {
            Serial.println(c = a*b);
        }
    }
      

