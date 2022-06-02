  int sensorValue = 0; 
  int sensorValue1 = 0; 
  int sensorPin = A1;
  float dirViento_tx=0;  
  String dirViento;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  veleta();
  Serial.print(dirViento_tx);
  delay(100);
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
  //Serial.println(dirViento);
}
