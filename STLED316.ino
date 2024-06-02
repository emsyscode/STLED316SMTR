//This is only a tree of code to get ideas as control the 
//driver LED 7 segments on the panel.


#define F_CPU 16000000UL

#define DSP_in 8// If 0 write LCD, if 1 read of LCD
#define DSP_clk 9 // if 0 is a command, if 1 is a data0
#define DSP_stb 10 // Must be pulsed to LCD fetch data of bus

#define BUTTON_PIN 3 //Att check wich pins accept interrupts... Uno is 2 & 3. This is our trigger pin used. 
volatile byte buttonReleased = false;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

bool flag = false;

void setup() {
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);

pinMode(BUTTON_PIN, INPUT);

 attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                  buttonReleasedInterrupt,
                  FALLING);

// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  interrupts();
}
void cmd_without_stb(unsigned char a)
{
  // send without stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  
  //This don't send the strobe signal, to be used in burst data send
         for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
           digitalWrite(DSP_clk, LOW);
           //delayMicroseconds(5);
                 if (data & mask){ // if bitwise AND resolves to true
                    digitalWrite(DSP_in, HIGH);
                 }
                 else{ //if bitwise and resolves to false
                   digitalWrite(DSP_in, LOW);
                 }
          delayMicroseconds(2);
          digitalWrite(DSP_clk, HIGH);
          delayMicroseconds(2);
         }
}
void cmd_with_stb(unsigned char a)
{
  // send with stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(DSP_stb, LOW);
  //delayMicroseconds(5);
         for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
           digitalWrite(DSP_clk, LOW);
           delayMicroseconds(2);
                 if (data & mask){ // if bitwise AND resolves to true
                    digitalWrite(DSP_in, HIGH);
                 }
                 else{ //if bitwise and resolves to false
                   digitalWrite(DSP_in, LOW);
                 }
          digitalWrite(DSP_clk, HIGH);
          delayMicroseconds(2);
         }
   digitalWrite(DSP_stb, HIGH);
   delayMicroseconds(2);
}
void switchOnOff()
{
  //Command to switch ON/OFF of STLED316MTR
  uint8_t chr = 0x00;
  
  chr = 0B00001110;
  cmd_with_stb(chr);
  delay(500);

  chr = 0B00001101;
  cmd_with_stb(chr);
  delay(500);
}
void DSP(void)
{
  //Control of strobe PIN 
digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//
}
void hello(void)
{
  DSP();
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b00000000); delay(10); DSP();  //
  cmd_without_stb(0b00000001); cmd_with_stb(0b00000000); delay(10); DSP();  //
  cmd_without_stb(0b00000000); cmd_with_stb(0b11010110); delay(10); DSP();  //Letter H
  delay(500); DSP(); 
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b00000000); delay(10); DSP();  //
  cmd_without_stb(0b00000001); cmd_with_stb(0b11010110); delay(10); DSP();  //Letter H
  cmd_without_stb(0b00000000); cmd_with_stb(0b11100011); delay(10); DSP();  //Letter E
  delay(500); DSP();
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b11010110); delay(10); DSP();  //Letter H
  cmd_without_stb(0b00000001); cmd_with_stb(0b11100011); delay(10); DSP();  //Letter E
  cmd_without_stb(0b00000000); cmd_with_stb(0b01000011); delay(10); DSP();  //Letter L
  delay(500); DSP();
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b11100011); delay(10); DSP();  //Letter E
  cmd_without_stb(0b00000001); cmd_with_stb(0b01000011); delay(10); DSP();  //Letter L
  cmd_without_stb(0b00000000); cmd_with_stb(0b01000011); delay(10); DSP();  //Letter L
  delay(500); DSP();
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b01000011); delay(10); DSP();  //Letter L
  cmd_without_stb(0b00000001); cmd_with_stb(0b01000011); delay(10); DSP();  //Letter L
  cmd_without_stb(0b00000000); cmd_with_stb(0b01110111); delay(10); DSP();  //Letter O
  delay(500); DSP();
}
void numbers(void)
{ 
//  //This command is to display numbers at STLED316MTR
//  DSP(); 
//  delayMicroseconds(2);//                     gfab-ced
//  cmd_without_stb(0b00010000); cmd_with_stb(0b00000000); cmd_with_stb(0xFB); delay(500); DSP(); // Here we define the dimmer of digits 2 & 1 Page 11
//  cmd_without_stb(0b00010000); cmd_with_stb(0b00000001); cmd_with_stb(0b11100111); delay(500); DSP(); // Here we define the dimmer of digits 4 & 3 Page 11
//  cmd_without_stb(0b00010001); cmd_with_stb(0b00000010); cmd_with_stb(0b00000000); delay(500); DSP(); // Here we define the dimmer of digits 6 & 5 Page 11
//  cmd_without_stb(0b00010001); cmd_with_stb(0b00000011); cmd_with_stb(0b00000000); delay(500); DSP(); // Here we define the dimmer of digits 6 & 5 Page 11
DSP(); 
  // Presente numberes at first Digit 
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000000); cmd_with_stb(0b01110111); delay(500); DSP(); //0
  cmd_without_stb(0b00000000); cmd_with_stb(0b00010100); delay(500); DSP(); //1
  cmd_without_stb(0b00000000); cmd_with_stb(0b10110011); delay(500); DSP(); //2
  cmd_without_stb(0b00000000); cmd_with_stb(0b10110101); delay(500); DSP(); //3
  cmd_without_stb(0b00000000); cmd_with_stb(0b11010100); delay(500); DSP(); //4
  cmd_without_stb(0b00000000); cmd_with_stb(0b11100101); delay(500); DSP(); //5
  cmd_without_stb(0b00000000); cmd_with_stb(0b11100111); delay(500); DSP(); //6
  cmd_without_stb(0b00000000); cmd_with_stb(0b00110100); delay(500); DSP(); //7
  cmd_without_stb(0b00000000); cmd_with_stb(0b11110111); delay(500); DSP(); //8
  cmd_without_stb(0b00000000); cmd_with_stb(0b11110101); delay(500); DSP(); //9
  // Presente numberes at second Digit DSP(); 
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000001); cmd_with_stb(0b01110111); delay(500); DSP(); //0
  cmd_without_stb(0b00000001); cmd_with_stb(0b00010100); delay(500); DSP(); //1
  cmd_without_stb(0b00000001); cmd_with_stb(0b10110011); delay(500); DSP(); //2
  cmd_without_stb(0b00000001); cmd_with_stb(0b10110101); delay(500); DSP(); //3
  cmd_without_stb(0b00000001); cmd_with_stb(0b11010100); delay(500); DSP(); //4
  cmd_without_stb(0b00000001); cmd_with_stb(0b11100101); delay(500); DSP(); //5
  cmd_without_stb(0b00000001); cmd_with_stb(0b11100111); delay(500); DSP(); //6
  cmd_without_stb(0b00000001); cmd_with_stb(0b00110100); delay(500); DSP(); //7
  cmd_without_stb(0b00000001); cmd_with_stb(0b11110111); delay(500); DSP(); //8
  cmd_without_stb(0b00000001); cmd_with_stb(0b11110101); delay(500); DSP(); //9
  DSP(); 
  delayMicroseconds(2);//                     gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b01110111); delay(500); DSP(); //0
  cmd_without_stb(0b00000010); cmd_with_stb(0b00010100); delay(500); DSP(); //1
  cmd_without_stb(0b00000010); cmd_with_stb(0b10110011); delay(500); DSP(); //2
  cmd_without_stb(0b00000010); cmd_with_stb(0b10110101); delay(500); DSP(); //3
  cmd_without_stb(0b00000010); cmd_with_stb(0b11010100); delay(500); DSP(); //4
  cmd_without_stb(0b00000010); cmd_with_stb(0b11100101); delay(500); DSP(); //5
  cmd_without_stb(0b00000010); cmd_with_stb(0b11100111); delay(500); DSP(); //6
  cmd_without_stb(0b00000010); cmd_with_stb(0b00110100); delay(500); DSP(); //7
  cmd_without_stb(0b00000010); cmd_with_stb(0b11110111); delay(500); DSP(); //8
  cmd_without_stb(0b00000010); cmd_with_stb(0b11110101); delay(500); DSP(); //9
}
void readButtons(){
//Take special attention to the initialize digital pin LED_BUILTIN as an output.
//
//Important note: The instructions presents on Datasheet of STLED316 reffere at
//read process of Output data happen only after 2 signals rise of clock, by this reason
//I used from 0~8 bits read process. This is very important because if the read of 8 bits
//don't take place correct, the flags of KEY1 and KEY2 bytes will not be Reset.
//Because the line of data IN/OUT is bidireccional, need a pull-up resistor, for example the value of
//5600 ohms to allow the both direction IMPORTANTE!
//
int ledPin = 13;   // LED connected to digital pin 13
int inPin = 8;     // pushbutton connected to digital pin 7
int val = 0;       // variable to store the read value
int dataIn=0;

byte array[8] = {0,0,0,0,0,0,0,0};
byte together = 0;

//unsigned char receive = 8; //define our transmit pin
unsigned char data = 0; //value to transmit, binary 10101010
unsigned char mask = 1; //our bitmask

array[0] = 1;

unsigned char btn1 = 0x41;
digitalWrite(DSP_clk, HIGH); // Clock is High when the Clock go Down
delayMicroseconds(2);//
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//
digitalWrite(DSP_clk, LOW);
delayMicroseconds(5);   
cmd_without_stb(0b01001000); // cmd 2 //10=Read Keys; 00=Wr DSP;
delayMicroseconds(2);
      
  pinMode(8, INPUT);  // Important this point! Here I'm changing the direction of the pin to INPUT data.
  delayMicroseconds(2);
         for (int z = 0; z < 3; z++){
                   for (int h =8; h >=0; h--) {
                      digitalWrite(DSP_clk, HIGH);  // Remember wich the read data happen when the clk go from LOW to HIGH! Reverse from write data to out.
                      delayMicroseconds(5);
                     val = digitalRead(inPin);
                           if (val == 1){ // if bitwise AND resolves to true
                           //Serial.print(val);
                            //data =data | (1 << mask);
                            array[h] = 1;
                           }
                           else{ //if bitwise and resolves to false
                           //Serial.print(val);
                           // data = data | (1 << mask);
                           array[h] = 0;
                           }
                    digitalWrite(DSP_clk, LOW);
                    delayMicroseconds(5);
                   } 
             
              //Serial.print(" - " );
                        //This cycle for is only to debug and print the line of bits received from the driver.
                         for (int bits = 8 ; bits >=0; bits--) {
                              Serial.print(array[bits]);
                         }
                        
//             Serial.println();
//             Serial.print("Byte:");
//             Serial.println(z);  // All the lines of print is only used to debug, comment it, please!  
             
                          if (z==0){
                            if(array[5] == 1){
                              //Put your code here to run at key "n" of panel
                            }
                        }
                        
                         
                        if (z==0){
                            if(array[7] == 1){
                              //Put your code here to run at key "n" of panel
                             // digitalWrite(10, !digitalRead(10)); // For example change status of pin 10 of Arduino
                          }
                        }
                        
                        if (z==1){
                           if(array[8] == 1){
                            Serial.println("   Reach this point!"); //Only to debug and see if trigger take place, comment it.
                             flag=true;
                            }
                          }                        
                 // Serial.println(); //Only to debug, comment it.
          }  // End of "for" of "z"
      //Serial.println();  // This line is only used to debug, please comment it!

 digitalWrite(DSP_stb, HIGH);
 delayMicroseconds(2);

 delayMicroseconds(2);
 pinMode(8, OUTPUT);  // Important this point! Here I'm changing the direction of the pin to OUTPUT data again.

 panelLED();
 
 buttonReleased = false;
}
void panelLED(){
         if(flag==true){
         digitalWrite(DSP_stb, HIGH);
         delayMicroseconds(2);
         digitalWrite(DSP_stb, LOW);
         delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
         cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00100000); //Switch ON LED 1
         delayMicroseconds(2);//
         digitalWrite(DSP_stb, HIGH);
         delay(2);
        }
        else{
          digitalWrite(DSP_stb, HIGH);
         delayMicroseconds(2);
         digitalWrite(DSP_stb, LOW);
         delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
         cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00000000);  //Switch OFF LED 1
         delayMicroseconds(2);//
         digitalWrite(DSP_stb, HIGH);
         delay(2);
        }
 delay(10);
}
void LEDsOn(){
  //switch segments on/off with order like: "gfab-ced"
digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00100000);
digitalWrite(DSP_stb, HIGH);
delay(200);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00010000);
digitalWrite(DSP_stb, HIGH);
delay(200);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00001000);
digitalWrite(DSP_stb, HIGH);
delay(200);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00000100);
digitalWrite(DSP_stb, HIGH);
delay(200);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                        gfab-ced                       1234      //I only make the teste over 4 LED's presents on panel.
cmd_without_stb(0b00001111); cmd_without_stb(0b11111111); cmd_without_stb(0b00000000);
digitalWrite(DSP_stb, HIGH);
delay(200);
}
void dsp7segOn(){
  //switch segments on/off with order like: "gfab-ced"
digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                       gfab-ced
  cmd_without_stb(0b00000000); cmd_with_stb(0b11110111);
  digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                       gfab-ced
  cmd_without_stb(0b00000001); cmd_with_stb(0b11110111);
  digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);//                       gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b11110111);
  digitalWrite(DSP_stb, HIGH); 
}
void dsp7segOff(){
  //Here all segments of 3 digits are cleanned!
digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);                       //gfab-ced
  cmd_without_stb(0b00000000); cmd_with_stb(0b00000000);
  digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);                      // gfab-ced
  cmd_without_stb(0b00000001); cmd_with_stb(0b00000000);
  digitalWrite(DSP_stb, HIGH);
delayMicroseconds(2);
digitalWrite(DSP_stb, LOW);
delayMicroseconds(2);                      // gfab-ced
  cmd_without_stb(0b00000010); cmd_with_stb(0b00000000);
  digitalWrite(DSP_stb, HIGH); 
}
void loop() {
unsigned int s = 0;
 switchOnOff();
      for (s=0x00; s <=3; s++){
        LEDsOn();
      }
//
hello();

numbers();

// 
        for( s = 0x00; s < 3; s++){
            dsp7segOn();
            delay(500);
            dsp7segOff();
            delay(500);
        } 
}
void buttonReleasedInterrupt() {
 // buttonReleased = true; // This is the line of interrupt button to advance one step on the search of segments!
  digitalWrite(13, !digitalRead(13)); //This is only to debug and confirm on the LED of Arduino the trigger take place!
  flag=false; 
  readButtons();
}
