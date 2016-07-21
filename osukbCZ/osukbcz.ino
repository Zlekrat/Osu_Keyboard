#include<Keyboard.h>
#include<EEPROM.h>
const int tl5 = 8; //píše " ", nemá světlo
const int tl4 = 7; //píše "w", nemá světlo
const int tl3 = 4; //píše "e", nemá světlo
const int tl2 = 3; //píše "r", světlo na pin "led1" (5)
const int tl1 = 2; //píše "t", světlo na pin "led2" (6)
const int led1 = 5; //světlo k pinu 3
const int led2 = 6; //světlo k pinu 2
int svetlo1 = 0; 
int svetlo2 = 0;
int stupnovani = 1;
int adresa = 1; //pamatuje si naposledy použitou pozici světel
int nastaveni = 1;

void rozhodnuti_svetla()
{
  switch(nastaveni)
  {
    case 1:
    svetlo_a(); break; 
    case 2: 
    svetlo_b(); break; 
    case 3:
    svetlo_c(); break;
    case 4:
    svetlo_d(); break;
  }
}

//svetlo_a = breathing mód
void svetlo_a()
{
  if (digitalRead(tl2) == 0) 
  {
      svetlo1 = 255;
      analogWrite(led1, svetlo1);     
  }
  else              
  {
  if (!svetlo1 == 0)
  {    
      svetlo1 = svetlo1 - stupnovani; 
      analogWrite(led1, svetlo1);   
  }     
  }
  if (digitalRead(tl1) == LOW)       
    {     
      svetlo2 = 255;
      analogWrite(led2, svetlo2); 
    }
  else                
  {
    if (!svetlo2 == 0)
    {
      svetlo2 = svetlo2 - stupnovani; 
      analogWrite(led2, svetlo2); 
    } 
  }
}

//svetlo_b = beze světla
void svetlo_b()
{
  //beze světla
}

//svetlo_c = svítí při stisku tlačítka
void svetlo_c()
{
  if (digitalRead(tl2) == 0) 
  {
      svetlo1 = 255;
      analogWrite(led1, svetlo1);     
  }
  else              
  {
      svetlo1 = 0;
      analogWrite(led1, svetlo1);       
  }
  if (digitalRead(tl1) == LOW)       
    {     
      svetlo2 = 255;
      analogWrite(led2, svetlo2); 
    }
  else                
  {
      svetlo2 = 0; 
      analogWrite(led2, svetlo2); 
  } 
}

//svetlo_d = svítí pořád
void svetlo_d()
{
  analogWrite(led1, 255);
  analogWrite(led2, 255);
}
    
void setup()
{
  //pokud nastane problém s pamětí, program ji resetuje
  nastaveni = EEPROM.read(adresa);
  if (nastaveni == 0)
  {
      EEPROM.write(adresa, 1);
      nastaveni = EEPROM.read(adresa);
  }
  
  pinMode(tl1, INPUT);
  pinMode(tl2, INPUT); 
  pinMode(tl3, INPUT);
  pinMode(tl4, INPUT); 
  pinMode(tl5, INPUT); 
  
  pinMode(led1, OUTPUT);           
  pinMode(led2, OUTPUT);
    
  digitalWrite(tl1, HIGH);
  digitalWrite(tl2, HIGH);
  digitalWrite(tl3, HIGH);
  digitalWrite(tl4, HIGH);
  digitalWrite(tl5, HIGH);
  Keyboard.begin();
}

void loop()
{

  
  if (digitalRead(tl5) == 0) 
  {
    Keyboard.press(32);    
  }
  else              
  {
    Keyboard.release(32);   
  }

  //boční tlačítko pro změnu nastavení
  if (digitalRead(tl4) == 0) 
  {
    if (digitalRead(tl3) == 0)
    {
      nastaveni = nastaveni + 1;
      analogWrite(led1, 0);
      analogWrite(led2, 0);
      delay(300);
      if (nastaveni > 4)
      {
          nastaveni = 1;  
      }
      EEPROM.write(adresa, nastaveni);
    }   
  }
  else              
  {
    //nedělá nic 
  }
  
  if (digitalRead(tl3) == 0) 
  {
    Keyboard.press('e');    
  }
  else              
  {
    Keyboard.release('e');   
  }

  if (digitalRead(tl2) == 0) 
  {
    Keyboard.press('r');
    rozhodnuti_svetla();    
  }
  else              
  {
  Keyboard.release('r');   
  rozhodnuti_svetla();
  }
  
  if (digitalRead(tl1) == LOW)       
    {
    Keyboard.press('t');          
    rozhodnuti_svetla();
    }
  else                
    {
    Keyboard.release('t'); 
    rozhodnuti_svetla();
  }
}

