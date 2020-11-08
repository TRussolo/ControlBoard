#include <Wire.h>

unsigned int buttonMillis;

//Encoder 1
const int enc1CLK = 2; //PINO DIGITAL (CLK)
const int enc1DT = 3;  //PINO DIGITAL (DT)
//Pino SW será conectado ao PCF8574
const int enc1SW = 5; //PINO DIGITAL (SW)

//Encoder 2
const int enc2CLK = 4; //PINO DIGITAL (CLK)
const int enc2DT = 5;  //PINO DIGITAL (DT)
//Pino SW será conectado ao PCF8574
//const int enc2SW = 5; //PINO DIGITAL (SW)

//Encoder 3
const int enc3CLK = 6; //PINO DIGITAL (CLK)
const int enc3DT = 7;  //PINO DIGITAL (DT)
//Pino SW será conectado ao PCF8574
//const int enc3SW = 5; //PINO DIGITAL (SW)

//Encoder 4
const int enc4CLK = 8; //PINO DIGITAL (CLK)
const int enc4DT = 9;  //PINO DIGITAL (DT)
//Pino SW será conectado ao PCF8574
//const int enc4SW = 5; //PINO DIGITAL (SW)

//Encoder 5
const int enc5CLK = 10; //PINO DIGITAL (CLK)
const int enc5DT = 11;  //PINO DIGITAL (DT)
//Pino SW será conectado ao PCF8574
//const int enc5SW = 5; //PINO DIGITAL (SW)


//Variáveis globais para o encoder 1
int enc1ContadorPos = 0;  //Contador de posições do encoder
int enc1UltPosicao; //Registra a última posição do encoder
boolean enc1BCW; //Variável de controle do sentido (Horário / Anti-Horário)

//Variáveis globais para o encoder 2
int enc2ContadorPos = 0;  //Contador de posições do encoder
int enc2UltPosicao; //Registra a última posição do encoder
boolean enc2BCW; //Variável de controle do sentido (Horário / Anti-Horário)

//Variáveis globais para o encoder 3
int enc3ContadorPos = 0;  //Contador de posições do encoder
int enc3UltPosicao; //Registra a última posição do encoder
boolean enc3BCW; //Variável de controle do sentido (Horário / Anti-Horário)

//Variáveis globais para o encoder 4
int enc4ContadorPos = 0;  //Contador de posições do encoder
int enc4UltPosicao; //Registra a última posição do encoder
boolean enc4BCW; //Variável de controle do sentido (Horário / Anti-Horário)

//Variáveis globais para o encoder 5
int enc5ContadorPos = 0;  //Contador de posições do encoder
int enc5UltPosicao; //Registra a última posição do encoder
boolean enc5BCW; //Variável de controle do sentido (Horário / Anti-Horário)

int enc1PosBuffer = 0;
int enc2PosBuffer = 0;
int enc3PosBuffer = 0;
int enc4PosBuffer = 0;
int enc5PosBuffer = 0;

bool enc1pmais;
bool enc2pmais;
bool enc3pmais;
bool enc4pmais;
bool enc5pmais;

bool newEncValue;


void setup() {
  Serial.begin (9600); //Inicializa a serial
  //Encoder #1
  pinMode (enc1CLK, INPUT); //Define o pino como entrada
  pinMode (enc1DT, INPUT); //Define o pino como entrada
  enc1UltPosicao = digitalRead(enc1CLK); //Variável recebe a leitura do pino CLK
  //pinMode (enc1SW,INPUT_PULLUP); //Define o pino como entrada / "_PULLUP" é para ativar o resustor interno
  //do arduino para garantir que não exista flutuação entre 0 (low) e 1 (high)

  //Encoder #2
  pinMode (enc2CLK, INPUT); //Define o pino como entrada
  pinMode (enc2DT, INPUT); //Define o pino como entrada
  enc2UltPosicao = digitalRead(enc2CLK); //Variável recebe a leitura do pino CLK

  //Encoder #3
  pinMode (enc3CLK, INPUT); //Define o pino como entrada
  pinMode (enc3DT, INPUT); //Define o pino como entrada
  enc3UltPosicao = digitalRead(enc3CLK); //Variável recebe a leitura do pino CLK

  //Encoder #4
  pinMode (enc4CLK, INPUT); //Define o pino como entrada
  pinMode (enc4DT, INPUT); //Define o pino como entrada
  enc4UltPosicao = digitalRead(enc4CLK); //Variável recebe a leitura do pino CLK

  //Encoder #5
  pinMode (enc5CLK, INPUT); //Define o pino como entrada
  pinMode (enc5DT, INPUT); //Define o pino como entrada
  enc5UltPosicao = digitalRead(enc5CLK); //Variável recebe a leitura do pino CLK

}

void loop() {

  int i, bm_ch = 0;
  unsigned long time = millis();



  //Read the PCF buttons
  unsigned int currentMillis = millis();

  //Limit button read to 20 times a second
  //Fast enough for most buttons
  if (currentMillis - buttonMillis >= 50) {
    buttonMillis = currentMillis;
  } else {
    //Ler encoder 1

    if (enc1PosBuffer != enc1ContadorPos) {
      Serial.println(enc1ContadorPos);
      enc1PosBuffer = enc1ContadorPos;
      enc1pmais = HIGH;
      newEncValue = HIGH;
    }
    else {
      lerEncoder(enc1CLK, &enc1UltPosicao, enc1DT, &enc1ContadorPos, &enc1BCW);

    }

 

    //Ler encoder 2
    if (enc2PosBuffer != enc2ContadorPos) {
      //    Serial.println("Enc2");
      //    Serial.println(enc2ContadorPos);
      enc2PosBuffer = enc2ContadorPos;
      enc2pmais = HIGH;
      newEncValue = HIGH;
    }
    else {
      lerEncoder(enc2CLK, &enc2UltPosicao, enc2DT, &enc2ContadorPos, &enc2BCW);
      if (newEncValue == LOW) {
        enc2pmais = LOW;
      }
    }

    //Ler encoder 3
    if (enc3PosBuffer != enc3ContadorPos) {
      //Serial.println("Enc3");
      //    Serial.println(enc3ContadorPos);
      enc3PosBuffer = enc3ContadorPos;
      enc3pmais = HIGH;
      newEncValue = HIGH;
    }
    else {
      lerEncoder(enc3CLK, &enc3UltPosicao, enc3DT, &enc3ContadorPos, &enc3BCW);
      if (newEncValue == LOW) {
        enc3pmais = LOW;
      }
    }

    //Ler encoder 4
    if (enc4PosBuffer != enc4ContadorPos) {
      //    Serial.println("Enc4");
      //    Serial.println(enc4ContadorPos);
      enc4PosBuffer = enc4ContadorPos;
      enc4pmais = HIGH;
      newEncValue = HIGH;
    }
    else {
      lerEncoder(enc4CLK, &enc4UltPosicao, enc4DT, &enc4ContadorPos, &enc4BCW);
      if (newEncValue == LOW) {
        enc4pmais = LOW;
      }
    }

    //Ler encoder 5
    if (enc5PosBuffer != enc5ContadorPos) {
      //    Serial.println("Enc5");
      //    Serial.println(enc5ContadorPos);
      enc5PosBuffer = enc5ContadorPos;
      enc5pmais = HIGH;
      newEncValue = HIGH;
    }
    else {
      lerEncoder(enc5CLK, &enc5UltPosicao, enc5DT, & enc5ContadorPos, &enc5BCW);
      if (newEncValue == LOW) {
        enc5pmais = LOW;
      }
    }
  }
}

void lerEncoder(int pinoCLK, int* ultPosicao, int pinoDT, int* contadorPos, boolean * bCW)
{

  int leituraCLK = digitalRead(pinoCLK); //VARIÁVEL RECEBE A LEITURA DO PINO CLK
  if (leituraCLK != *ultPosicao) { //SE VALOR DA VARIÁVEL FOR DIFERENTE DO VALOR DE "ultPosicao", FAZ
    if (digitalRead(pinoDT) != leituraCLK) { //SE LEITURA DO PINO FOR DIFERENTE DA LEITURA DE "leituraCLK",
      //SIGNIFICA QUE O EIXO ESTÁ SENDO GIRADO NO SENTIDO HORÁRIO E FAZ
      *contadorPos = *contadorPos + 1; //INCREMENTA CONTAGEM DA VARIÁVEL EM +1
      *bCW = true; //VARIÁVEL BOOLEANA RECEBE VERDADEIRO (SENTIDO HORÁRIO)
    } else { //SENÃO, SIGNIFICA QUE O EIXO ESTÁ SENDO GIRADO NO SENTIDO ANTI-HORÁRIO E FAZ
      *bCW = false; //VARIÁVEL BOOLEANA RECEBE FALSO (SENTIDO ANTI-HORÁRIO)
      *contadorPos = *contadorPos - 1; //DECREMENTA CONTAGEM DA VARIÁVEL EM -1
    }

  }
  *ultPosicao = leituraCLK; //VARIÁVEL RECEBE O VALOR DE "leituraCLK"
}
