
#define L_POR_BALANCEO 0.2794; 

  const int pluviPin3 =  3;// the number of the LED pin
  float lluvia =0;
  float humedad=0;
  int cantidadLLuvia=0;
  volatile int contadorPluvi = 0;
  int InterruptCounterPluviometro=0;
  
void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  pinMode(pluviPin3, INPUT);//plumiometro
}

void loop() {
  // put your main code here, to run repeatedly:
  pluviometro(); 
  Serial.println(lluvia);
  delay(100);
}

void balanceoPluviometro() { 
  //attachInterrupt(digitalPinToInterrupt(3), balanceoPluviometro, RISING);
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
