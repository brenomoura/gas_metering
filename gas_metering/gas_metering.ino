#include <TimerOne.h>
#include <WISOL.h>
#include <Tsensors.h>
#include <math.h>
Isigfox *Isigfox = new WISOL();
Tsensors *tSensors = new Tsensors();

const int buttonPin = A1;
int pulses = 0;
float m3 = 0.00;


// Init function
void setup() {
  Serial.begin(9600);// Init serial connection between Arduino and Modem
  Isigfox->initSigfox();// WISOL modem test
  Isigfox->testComms();
  tSensors->initSensors();// Init sensors on Thinxtra Module
  tSensors->setButton(buttonIR); // Init an interruption on the button of the Xkit
  // pinMode(buttonPin, INPUT);
  Timer1.initialize(3000000000); // Inicializa o Timer1 e configura para um período de X segundos
  Timer1.attachInterrupt(send_data); // Configura a função Send_Pload() como a função para ser chamada a cada interrupção do Timer1
}

// Infinite loop of the program
void loop() {
  /*int buttonPinState = digitalRead(buttonPin);
  if(buttonPinState == HIGH){
    pulses++;
  }
  m3 = pulses*0.01;
  */
  Serial.print("Consumo (m3): "); Serial.println(m3);
  delay(1000);
}

// SendPayload Function => Send messages to the Sigfox Network
void Send_Pload(uint8_t *sendData, int len) {
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  Isigfox->sendPayload(sendData, len, 0, RecvMsg);
  free(RecvMsg);
}

void send_data(){
  Send_Pload((const char*)&m3, sizeof(m3));
  Serial.println("The data was sent");
}

void buttonIR(){
    pulses++;
    m3 = pulses*0.01;
}
