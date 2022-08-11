
fjfjfjgfjhfgjh
#include <Arduino.h>
#include <Servo.h>

#define MAX_HOMBRO 140
#define MIN_HOMBRO 40
#define MAX_WRIST 180
#define MIN_WRIST 0
#define MAX_BASE 170
#define MIN_BASE 10

Servo mBase;  // Creamos un objeto "Servo" para controlar cada servomotor.
Servo mHombro;
Servo mCodo;
Servo mWrist;
Servo mPinza;

int posBase = 91;    //Valor actual posición servo Base giratoria.
int posHombro = 80;  //Valor actual posición servo HOMBRO.
int backHombro = posHombro;
int posCodo = 30;
int posWrist = 90;
int posPinza = 135;   //Valor actual posición servo PINZA.

int inByte;
boolean dato = false;

void mueveHombro(int x);
void carga_valores_iniciales();
void mueveWrist (int x);

void setup() {
  
 carga_valores_iniciales();

  mBase.attach(11);
  mHombro.attach(10);  // attaches the servo on pin 9 to the servo object
  mCodo.attach(9);
  mWrist.attach(8);
  mPinza.attach(6);
    
  Serial.begin(9600);
  while (!Serial);

 Serial.println("");  
 Serial.println("===================");  
 Serial.println("ROBOT   de    Rafa ");  
 Serial.println("===================");  
 Serial.println("Use las sig. teclas para cada movimiento:");  
 Serial.println("Base  : +w -q ");
 Serial.println("Hombro: +a -s ");
 Serial.println("Codo  : +b -c ");
 Serial.println("Muñeca: +n -m ");
 Serial.println("Pinza : +z -x "); 
 Serial.println("Ayuda : h "); 
 Serial.print("Robot> ");

  mBase.write(posBase);              // tell servo to go to position in variable 'pos'
  mHombro.write(posHombro);              // tell servo to go to position in variable 'pos'
  mPinza.write(posPinza);              // tell servo to go to position in variable 'pos'
  mCodo.write(posCodo);
  mWrist.write(posWrist);
  
    mPinza.write(135);
      delay(500);
    mPinza.write(45);
      delay(500);
    mPinza.write(135);
      delay(500);
    mPinza.write(45);
      delay(500);
}

void loop() {
  
if (Serial.available() > 0) {
  inByte = Serial.read();

switch (inByte) {

////// HOMBRO  ///////////////////
case 'a': 
  if(posHombro < MAX_HOMBRO){
      posHombro = posHombro + 10;
      mueveHombro(posHombro);
      Serial.println("Hombro +10 grados");
    }
  else{
    Serial.println("Límite superior HOMBRO alcanzado");
  }
  break;

case 's':
  if(posHombro > MIN_HOMBRO){
      posHombro = posHombro - 10;
      mueveHombro(posHombro);
      Serial.println("Hombro -10 grados");
    }
  else{
    Serial.println("Límite inferior HOMBRO alcanzado");
  }
break;

///////  PINZA   ////////
case 'z': 
    posPinza = 135;
    mPinza.write(posPinza);
       Serial.println("Cierra Pinza");
  break;
case 'x':
    posPinza = 45;
    mPinza.write(posPinza);
       Serial.println("Abre Pinza");
  break;

///////  CODO   ////////
case 'v':
    if (posCodo < 160) {
      posCodo = posCodo + 10;
      mCodo.write(posCodo);
      Serial.println("Codo +10");
    }
    else{
      Serial.println("Limite superior alcanzado");
    }
  break;
case 'c':
    if (posCodo > 10) {
      posCodo = posCodo - 10;
      mCodo.write(posCodo);
      Serial.println("Codo -10");
    }
    else{
      Serial.println("Limite inferior alcanzado");
    }
break;

///////  MUÑECA   ////////
case 'm':
    if (posWrist < MAX_WRIST) mueveWrist(10);
/*     {
      posWrist = posWrist + 10;
      mWrist.write(posWrist);
      Serial.print("Wrist: ");
      Serial.println(posWrist)
    }
*/    
    else{
      Serial.println("Limite superior alcanzado");
    }
  break;
case 'n':
    if (posWrist > MIN_WRIST) mueveWrist(-10);
/*    {
      posWrist = posWrist - 10;
      mWrist.write(posWrist);
      Serial.print("Wrist: ");
      Serial.println(posWrist)
    }
*/
    else{
      Serial.println("Limite inferior alcanzado");
    }
  break;

///////  BASE   ////////
case 'w':
    if (posBase < MAX_BASE) {
      posBase = posBase + 10;
      mBase.write(posBase);
      Serial.println("Base +10");
    }
    else{
      Serial.println("Limite superior alcanzado");
    }
  break;
  
case 'q':
    if (posBase > MIN_BASE) {
      posBase = posBase - 10;
      mBase.write(posBase);
      Serial.println("Base -10");
    }
    else{
      Serial.println("Limite inferior alcanzado");
    }
  break;

  

///////   POSICIÓN INICIAL  ////////////////////
case 'p':
  carga_valores_iniciales();
  mBase.write(posBase);              // tell servo to go to position in variable 'pos'
  mueveHombro(posHombro);              // tell servo to go to position in variable 'pos'
  mPinza.write(posPinza);              // tell servo to go to position in variable 'pos'
  mCodo.write(posCodo);
  Serial.println("Posición Inicial");
  break;

case 'h':
  Serial.println("");
  Serial.println("Base  : +w -q ");
  Serial.println("Hombro: +a -s ");
  Serial.println("Codo  : +b -c ");
  Serial.println("Muñeca: +n -m ");
  Serial.println("Pinza : +z -x ");
  break;

default:
  Serial.print('\"');
  Serial.print(char(inByte));
  Serial.print('\"');
  Serial.println(" no tiene asignada una tarea.");
  break;
}  

Serial.print("Robot> ");
}

inByte = 0;
}  //void loop()

//------------------------   FUNCIONES  -----------------------------------

void carga_valores_iniciales()
{
  posBase = 90;
  posHombro = 80;
  backHombro = posHombro;
  posCodo = 30;
  posWrist = 90;
  posPinza = 135;
}

void mueveHombro(int x){
  if (x > backHombro){
    while (backHombro < x) {
        backHombro = backHombro+1;
        mHombro.write(backHombro);
        delay(10);
    }
  }
  
  if (x < backHombro){
        backHombro=x;
        mHombro.write(backHombro);
  
  }  
}

void mueveWrist (int x){
      posWrist = posWrist + x;
      mWrist.write(posWrist);
      Serial.print("Wrist: ");
      Serial.println(posWrist);

}
