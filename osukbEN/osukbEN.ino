#include<Keyboard.h>
#include<EEPROM.h> // this is for saving last light mode into memory (when you unplug or reset)

const int tl5 = 8; // writes " ", no light
const int tl4 = 7; // used to change between light modes, no light
const int tl3 = 4; // writes "e", no light
const int tl2 = 3; // writes "r", light on pin "led1" (5)
const int tl1 = 2; // writes "t", light on pin "led2" (6)
const int led1 = 5; // light for pin 3
const int led2 = 6; // light for pin 2
int svetlo1 = 0; 
int svetlo2 = 0;
int stupnovani = 1; // change speed of turning light off in light mode 1
int adresa = 1; // remembers last light mode
int nastaveni = 1;

void rozhodnuti_svetla()
{
  switch(nastaveni)
  {
    case 1:
    svetlo_a(); break; // light mode 1
    case 2: 
    svetlo_b(); break; // light mode 2
    case 3:
    svetlo_c(); break; // light mode 3
    case 4:
    svetlo_d(); break; // light mode 4
  }
}

// light mode 1 = when the button is pressed, led lights up, when it is not, light slowly goes dark
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

// light mode 2 = no light
void svetlo_b()
{
  // no light
}

// light mode 3 = light is on when pressed, when not pressed it's off
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

// light mode 4 = light is allways on
void svetlo_d()
{
  analogWrite(led1, 255);
  analogWrite(led2, 255);
}
    
void setup()
{
  // in case of memory fail, memory is reset 
  nastaveni = EEPROM.read(adresa);
  if (nastaveni == 0)
  {
      EEPROM.write(adresa, 1);
      nastaveni = EEPROM.read(adresa);
  }

  // setting button pins as inputs
  pinMode(tl1, INPUT);
  pinMode(tl2, INPUT); 
  pinMode(tl3, INPUT);
  pinMode(tl4, INPUT); 
  pinMode(tl5, INPUT); 

  // setting led pins as outputs
  pinMode(led1, OUTPUT);           
  pinMode(led2, OUTPUT);

  // inicializing button pins
  digitalWrite(tl1, HIGH);
  digitalWrite(tl2, HIGH);
  digitalWrite(tl3, HIGH);
  digitalWrite(tl4, HIGH);
  digitalWrite(tl5, HIGH);

  // starting keyboard library
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

  // side button is used to change light modes
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
    // nedělá nic 
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

