#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

#define DHT_A 2
#define DHTTYPE DHT22


LiquidCrystal_I2C lcd(0x27, 20, 4); //Direccion hexadecimal,tamaño x, tamaño y


#define L_POR_BALANCEO 0.2794; 
const int RecordTime = 3; //Define Measuring Time (Seconds)
unsigned long time_ret=0;
const int anemoPin2 =  2;// the number of the LED pin
const int pluviPin3 =  3;// the number of the LED pin

int countup=0, conta2=0;
int Reg_anemo=0;
volatile int contadorPluvi = 0;
int sensorValue = 0; 
int sensorPin = A1;
float lluvia=0;
float sensorValue1=0;
float velocidad=0;
float humedad=0;
float temperatura=0;
int cantidadLLuvia=0;
float dirViento_tx=0;
float h;
float t;
float hic;
int dir_esclavo = 1;

byte bytewrite[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int dato1 = 0 ,dato2 = 0,dato3 = 0,dato4 = 0,dato5 = 0,
dato6 = 0,dato7 = 0,dato8 = 0,dato9 = 0,dato10 = 0,
dato11 = 0,dato12 = 0,dato13 = 0,dato14 = 0,dato15 = 0,
dato16 = 0,dato17 = 0,dato18 = 0,dato19 = 0,dato20 = 0;

const int A2pin = 2;
DHT dht(A2, DHTTYPE);

String dirViento;

volatile int InterruptCounter=0;

int InterruptCounterPluviometro=0;
float WindSpeed;

void setup() {
  Serial.begin(9600);
  pinMode(anemoPin2, INPUT);//blujula
  pinMode(pluviPin3, INPUT);//plumiometro
  pinMode(9, OUTPUT);//blujula
  lcd.init();//inicializa la pantalla
  lcd.backlight();//Enciende la luz de fondo

  lcd.setCursor(4, 1); //posicion 5 en x en la primer linea
  lcd.print("Bienvenidos");//

  lcd.setCursor(4,2);//posiciona el cursor x,y
  lcd.print("Grupo GISTFA");//Imprime el msj */

  pinMode(A2pin, INPUT);

  dht.begin();
}

void displayDatos(float velocidad,String direccion, float humedad,float temperatura,int cantidadLLuvia){
   String velViento,humSensor,temperaturaSensor,pluviometro;

   lcd.init();
   
   velViento.concat(velocidad);
   lcd.setCursor(0, 0); //posicion 5 en x en la primer linea
   lcd.print("V:"+ velViento+" Km/H");//

   lcd.setCursor(0, 1); //posicion 5 en x en la primer linea
   lcd.print("Dv:"+ direccion+((char)223));
   // 
   lcd.setCursor(0, 2); //posicion 5 en x en la primer linea
   humSensor.concat(humedad);
   lcd.print("H:"+humSensor+((char)293));//

   lcd.setCursor(9, 2); //posicion 5 en x en la primer linea
   temperaturaSensor.concat(temperatura);
   lcd.print("T:"+temperaturaSensor+((char)223)+"C");//

   lcd.setCursor(0, 3); //posicion 5 en x en la primer linea
   pluviometro.concat(lluvia);
   lcd.print("PP: "+ pluviometro+"mm");
 }
 */

union Float_Byte{
  float datoF1;
  float datoF2;
  float datoF3;
  float datoF4;
  float datoF5;
  byte  datoB1[4];
  byte  datoB2[4];
  byte  datoB3[4];
  byte  datoB4[4];
  byte  datoB5[4];
} unionFB;

void loop(){
  veleta();
  anemometro();
  pluviometro();  
  sensorHumedad();
//  Serial.println("pluviometro:");
//  Serial.println(lluvia);
//  Serial.print("      ");
//  displayDatos(WindSpeed,dirViento,h,t,lluvia);
  buzzer();
  // envio_serial();
  enviar_trama();

Float_Byte();

      unionFB.datoF1 = t; 
      dato4 =  unionFB.datoB1[0];
      dato3 =  unionFB.datoB1[1];
      dato2 =  unionFB.datoB1[2];
      dato1 =  unionFB.datoB1[3];

      unionFB.datoF2 = h;
      dato8 =  unionFB.datoB2[0];
      dato7 =  unionFB.datoB2[1];
      dato6 =  unionFB.datoB2[2];
      dato5 =  unionFB.datoB2[3];

      unionFB.datoF3 = dirViento_tx;
      dato12 =  unionFB.datoB3[0];
      dato11 =  unionFB.datoB3[1];
      dato10 =  unionFB.datoB3[2];
      dato9 =  unionFB.datoB3[3];

      unionFB.datoF4 = WindSpeed;
      dato16 =  unionFB.datoB4[0];
      dato15 =  unionFB.datoB4[1];
      dato14 =  unionFB.datoB4[2];
      dato13 =  unionFB.datoB4[3];

      unionFB.datoF5 = lluvia;
      dato20 =  unionFB.datoB5[0];
      dato19 =  unionFB.datoB5[1];
      dato18 =  unionFB.datoB5[2];
      dato17 =  unionFB.datoB5[3];

      int funcion = 240;
      int dir_registroT = 1;

      bytewrite[0] = 73;
      bytewrite[1] = 01;
      bytewrite[2] = 04;
      bytewrite[3] = 01;
      //sens 1
      bytewrite[4] = dato1;
      bytewrite[5] = dato2;
      bytewrite[6] = dato3;
      bytewrite[7] = dato4;
      //sens 2
      bytewrite[8] = dato5;
      bytewrite[9] = dato6;
      bytewrite[10] = dato7;
      bytewrite[11] = dato8;
      //sens 3
      bytewrite[12] = dato9;
      bytewrite[13] = dato10;
      bytewrite[14] = dato11;
      bytewrite[15] = dato12;
      //sens 4
      bytewrite[16] = dato13;
      bytewrite[17] = dato14;
      bytewrite[18] = dato15;
      bytewrite[19] = dato16;
      //sens 5
      bytewrite[20] = dato17;
      bytewrite[21] = dato18;
      bytewrite[22] = dato19;
      bytewrite[23] = dato20;
  
  for(int i=0 ; i<=24 ; i++ ){
    Serial.write(bytewrite[i]);
  }

delay(1000);

}

void buzzer(){
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(9,LOW);
  }

void sensorHumedad(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  hic = dht.computeHeatIndex(t, h, false);
    Serial.println("Humidity: ");
    Serial.println(h);
    Serial.println("Temperature");
    Serial.println(hic);
}

void veleta(){
  sensorValue = analogRead(sensorPin);
  sensorValue1 =(sensorValue*5)/102.3 ;
  sensorValue1 =sensorValue1/10;
  
  if(sensorValue1>3.83 && sensorValue1<3.87 )
  {dirViento="Norte 0 ";dirViento_tx=0;}
  
  if(sensorValue1>1.96 && sensorValue1<2.00 )
  {dirViento="NE 22.6";dirViento_tx=22.6;}
  if(sensorValue1>2.24 && sensorValue1<2.28 )
  {dirViento="NE 45";dirViento_tx=45.0;}
  if(sensorValue1>0.38 && sensorValue1<0.42 )
  {dirViento="NE 67.5";dirViento_tx=67.5;}
  if(sensorValue1>0.42 && sensorValue1<0.46 )
  {dirViento="E 90";dirViento_tx=90.0;}
  if(sensorValue1>0.29 && sensorValue1<0.33 )
  {dirViento="SE 112.5";dirViento_tx=112.5;}
  if(sensorValue1>0.88 && sensorValue1<0.92 )
  {dirViento="SE 135";dirViento_tx=135.0;}
  if(sensorValue1>0.59 && sensorValue1<0.63 )
  {dirViento="SE 157.5";dirViento_tx=157.5;}
  if(sensorValue1>1.38 && sensorValue1<1.42 )
  {dirViento="S 180";dirViento_tx=180.0;}
  if(sensorValue1>1.17 && sensorValue1<1.21 )
  {dirViento="SO 202.5";dirViento_tx=202.5;}
  if(sensorValue1>3.07 && sensorValue1<3.11 )
  {dirViento="SO 225";dirViento_tx=225;}
  if(sensorValue1>2.92 && sensorValue1<2.96 )
  {dirViento="SO 247.5";dirViento_tx=247.5;}
  if(sensorValue1>4.60 && sensorValue1<4.64 )
  {dirViento="O 270";dirViento_tx=270;}
  if(sensorValue1>4.03 && sensorValue1<4.07 )
  {dirViento="NO 292.5";dirViento_tx=292.5;}
  if(sensorValue1>4.32 && sensorValue1<4.36 )
  {dirViento="NO 315";dirViento_tx=315;}
  if(sensorValue1>3.43 && sensorValue1<3.47 )
  {dirViento="NO 337.5";dirViento_tx=337.5;}
  Serial.println(dirViento);
}

void anemometro() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(2), contadoranemometro, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(2));
  WindSpeed = (float)InterruptCounter / (float)RecordTime * 2.4;

//  Serial.println("Wind Speed: ");
//  Serial.println(WindSpeed);       //Speed in km/h
//  Serial.println(" km/h - ");
//  Serial.println(WindSpeed / 3.6); //Speed in m/s
//  Serial.println(" m/s");

}

void contadoranemometro(){
  InterruptCounter++;
}

void balanceoPluviometro() { 
  attachInterrupt(digitalPinToInterrupt(3), balanceoPluviometro, RISING);
  contadorPluvi++;  
}

void  tomaDatos (){
  lluvia+=contadorPluvi*L_POR_BALANCEO;  
  contadorPluvi=0;  
}

void pluviometro(){
  attachInterrupt(digitalPinToInterrupt(3), balanceoPluviometro, RISING);
  detachInterrupt(digitalPinToInterrupt(3));
  tomaDatos();  
}
void envio_serial(){
  sensor tem_ambiente
  sensor humedad
  sensor_dir_vien
  sensor vel_vient
  sensor Precipitacion

  Serial.print(t);
  delay(100);
  Serial.print(h);
  delay(100);
  Serial.print(dirViento_tx);
  delay(100);
  if(WindSpeed >= 10.00){
     Serial.print(WindSpeed);   
  }else{
     Serial.print(WindSpeed); 
     Serial.print("0");     
   }
    delay(100);
    Serial.println(lluvia);
    delay(100);
}




      
      
