#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

int button_tmp=0;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(2, OUTPUT);
  Serial.setTimeout(8000);
 
}
void loop() {

  if(button_tmp == 10) button_tmp = 0;

  if(Serial.available())
  {
    char c;
    char a = Serial.read();
    c = a;
    
    if(c == 'a')
    {
      delay(200);
      digitalWrite(2, HIGH);
    }
    
    else if (c == 'b')
    {
      delay(200);
      digitalWrite(2, LOW);   
    }

    else if(c == 'd')
    {
      delay(200);
      int i = Serial.parseInt();
      delay(200);
      int result = i*i;
      while(result > 0)
      {
        Serial.write(result%10);
        result = (result - result%10)/10;
      }
      int endcount = -1;
      Serial.write(endcount);
    }

    else if(c == 'e')
    {    
      int button = 0;
      while(button == 0){
        delay(10); 
        button = digitalRead(8);
      }    

      if(button == 1)
      {
      delay(200);
        button_tmp++;
        char button_temp = button_tmp;
        Serial.write(button_temp);
      }
    }
  }

}
