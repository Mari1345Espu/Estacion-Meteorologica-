  
  int countup=0, conta2=0;
  int Reg_anemo=0;
  const int RecordTime = 3; //Define Measuring Time (Seconds)
  const int anemoPin2 =  2;// the number of the LED 
  float WindSpeed;
  volatile int InterruptCounter=0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(anemoPin2, INPUT);//blujula
}
void loop() {
  // put your main code here, to run repeatedly:
  anemometro();
  if(WindSpeed >= 10.00){
      Serial.print(WindSpeed);   
    }else{
      Serial.print(WindSpeed); 
      Serial.print("0");     
    }
}

void anemometro() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(2), contadoranemometro, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(2));
  WindSpeed = (float)InterruptCounter / (float)RecordTime * 2.4;
}

void contadoranemometro(){
  InterruptCounter++;
}
