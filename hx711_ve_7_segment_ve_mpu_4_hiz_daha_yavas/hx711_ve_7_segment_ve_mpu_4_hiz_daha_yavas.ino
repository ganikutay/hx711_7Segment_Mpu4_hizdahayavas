#include<Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <ShiftRegister74HC595.h>
#include <HX711.h>


Servo motor;



int hiz=0;

int delhiz=50;
//*********************  HX711  ************************
//*********************  HX711  ************************
const int DOUT = A3; 
const int CLK = A2;

HX711 scale;
 
float kalibrasyon_faktoru = 10000; // buraya kalibrasyon işleminde bulduğunuz kalibrasyon faktörünü yazınız.
 
//*********************  MPU6050  ************************
//*********************  MPU6050  ************************
    MPU6050 mpu6050(Wire);         // SCL (yeşil kablo) A5 & SDA A4 (beyaz kablo)
    float y_acisi;
    float x_acisi;
//*********************  HIZ GÖSTERGESİ  ************************
//*********************  HIZ GÖSTERGESİ  ************************  
    #define led1 3
    #define led2 4
    #define led3 5
//*********************  7 SEGMENT  ************************
//*********************  7 SEGMENT  ************************  
    #define SDI 7
    #define SCLK 6
    #define LOAD 5
    #define DIGITS 2

    ShiftRegister74HC595 <DIGITS>sr( SDI, SCLK, LOAD);

    int value,digit1,digit2,digit3,digit4;
    uint8_t digits[] = {B11000000,//0
                    B11111001,//1
                    B10100100,//2
                    B10110000,//3
                    B10011001,//4
                    B10010010,//5
                    B10000010,//6
                    B11111000,//7
                    B10000000,//8
                    B10010000 //9
                    };

                    
void setup() {
    Serial.begin(9600);

    scale.begin(DOUT, CLK);
    scale.set_scale(kalibrasyon_faktoru ); // Kalibrasyon faktörü tanımlama
    scale.tare(); // Ölçeği sıfırlama


    motor.attach(11 ,1000, 2000);


    Wire.begin();
    mpu6050.begin();   //   SCL A5  ve SDA A4 
    mpu6050.calcGyroOffsets(true);


    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    agirlik=0; //burada ilk baslarken agirligi 0 yaptik, cunku aradan zaman gecip kaykayi kullanmazsam, bir takim mekani arizalar cikiyor ve agirligin ilk baslangic degeri her seferinde degisiyor


}



void loop() {

    int agirlik = scale.get_units();

    
    mpu6050.update();
    float y_acisi = mpu6050.getAngleY();
    float x_acisi = mpu6050.getAngleX();
    delay(15);
    Serial.println("Y açısı : ");
    Serial.println(mpu6050.getAngleY());
    Serial.println("X açısı : ");
    Serial.println(mpu6050.getAngleX());
    delay(15); 
    


Serial.print("AGIRLIK = ");
    Serial.println(agirlik);

    Serial.print("HIZ Degeri = ");
    Serial.println(hiz);
    delay(20);



//----------------------------------------------------------- DÜZ YOL -----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- DÜZ YOL -----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- DÜZ YOL -----------------------------------------------------------------------------------------------------------------------


if( x_acisi >= -10)                  //  DÜZ YOL*********************************************************************************************    DÜZ YOL    ********
    {
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
//________________________________SIFIR_____________________________________
if(agirlik <= 20){
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
    if(hiz <= 0){
      hiz=0;
      motor.write(hiz);
      delay(delhiz); 
      Serial.println("Hiz Degeri = 0");
      showNumber(hiz);
    }
    
    else if(hiz > 0){ 
        hiz=0;
        motor.write(hiz);
        delay(delhiz);
        Serial.println("Hiz Degeri = 0 else if");
        showNumber(hiz);
    }  
}


//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________
//________________________________BIR_____________________________________

else if(agirlik > 20 && agirlik <=40){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
      if(hiz < 10){
          for( hiz=1; hiz<=10; hiz++){
            motor.write(hiz);   
            delay(delhiz+20);
            showNumber(hiz);
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ for dongulerinin icerisine analogread(agirlik) koyup
            // agirlik = 0 ise break komutu ekleyip, donguyu kirmasini saglayalim
          }
          hiz=10;
      }

// 10 ten buyukse(yani 20 ten buraya dusunce)
      else if(hiz > 10 && hiz <= 20){
        hiz=10;
        delay(delhiz);
            
      }


    
      else if(hiz == 10){//ustteki asamalar tamamlaninca,  buraya giriyor ve hiz 10 ye esitleniyor
          motor.write(hiz);
          delay(delhiz);
                Serial.println("10 BURAYA GIRDI");
                showNumber(hiz);
        }
    
}






//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
//________________________________IKI_____________________________________
else if(agirlik > 40 && agirlik <=60){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);

      if(hiz >= 10 && hiz < 15){
          for( hiz=11; hiz<=15; hiz++){
            motor.write(hiz);
            delay(delhiz);
            showNumber(hiz);
          }
          hiz=15;
      }
// 10 dan kucukse(yani sifirdan direkt burraya gelirse)
      else if(hiz < 10 && hiz < 15){
          for( hiz=hiz; hiz<=14; hiz++){ //hiz=0 yerine hiz=hiz olabilir? o anki hizdan itibaren artar. Ancak bu else if in amaci 0 dan direkt buraya girerse...
              motor.write(hiz);
              delay(delhiz);
              showNumber(hiz);
            }
            hiz=15;
      }
// 15 dan buyukse(yani 20 ten buraya dusunce)
      else if(hiz > 15 && hiz <= 20){
        hiz=15;
        delay(delhiz);    
      }
//motor hizi 15 olur
      else if(hiz == 15){//ustteki asama tamamlaninca, buraya giriyor ve hiz 15 ye esitleniyor
          motor.write(hiz);
          delay(delhiz);
          Serial.println("15 BURAYA GIRDI");
          showNumber(hiz);
        }
    
}




//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
//________________________________UC_____________________________________
else if(agirlik > 60 ){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);

      if(hiz >= 15 && hiz < 20){
          for( hiz=16; hiz<=20; hiz++){
            motor.write(hiz);
            delay(delhiz);
            showNumber(hiz);
          }
          hiz=20;
      }



// 15 dan kucukse(yani sifirdan direkt veya 10 den direkt burraya gelirse)
      else if(hiz < 15 && hiz < 20){
          for( hiz=hiz; hiz<=19; hiz++){ 
              motor.write(hiz);
              delay(delhiz);
              showNumber(hiz);
            }
            hiz=20;
      }
  
      else if(hiz == 20){//ustteki asama tamamlaninca, buraya giriyor ve hiz 20 ye esitleniyor
          motor.write(hiz);
          delay(delhiz);
          Serial.println("20 BURAYA GIRDI");
          showNumber(hiz);
        }   
}

else {
  //HERHANGI BIR HATADA ELSE
    motor.write(0);
    delay(40);
    showNumber(99);
  }  
}























//----------------------------------------------------------- YOKUŞ AŞAĞI -----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- YOKUŞ AŞAĞI -----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------- YOKUŞ AŞAĞI -----------------------------------------------------------------------------------------------------------------------




else if( x_acisi < -10)                             // YOKUŞ AŞAĞI, İNİŞ *************************************************************************************** YOKUŞ AŞAĞI, İNİŞ ******
     {

      Serial.print(" YOKUŞ AŞAĞI MOD , MOTORLAR KAPALI ");
      
      Serial.println("aci degeri ");
      Serial.print(mpu6050.getAngleY());


      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);  
      hiz=10;
      motor.write(hiz);
      delay(delhiz); 
      Serial.println("Hiz Degeri = 10");
      showNumber(hiz);

     }






//******************************** ELSE *****************************
//******************************** ELSE *****************************
//******************************** ELSE *****************************



else
{
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);  
      hiz=0;
      motor.write(hiz);
      delay(delhiz); 
      Serial.println("PROGRAM HATALI!");
      showNumber(0);
}
















  
}

















void showNumber(int num)
{
    digit2=num % 10;
    digit1=(num / 10) % 10;

    uint8_t numberToPrint[]= {digits[digit1],digits[digit2]};
    sr.setAll(numberToPrint);
}
