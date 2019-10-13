#include <TimerOne.h>
#include <WISOL.h>
#include <Tsensors.h>
#include <math.h>
Isigfox *Isigfox = new WISOL();
Tsensors *tSensors = new Tsensors();

const int buttonPin = A1;
int pulses = 0;
float m3 = 0.00;
unsigned long time = 0;
int period = 20000;

// Init function
void setup() {
  Serial.begin(9600);// Init serial connection between Arduino and Modem
  Isigfox->initSigfox();// WISOL modem test
  Isigfox->testComms();
  tSensors->initSensors();// Init sensors on Thinxtra Module
  tSensors->setButton(buttonIR); // Init an interruption on the button of the Xkit
  // pinMode(PINO DO REED SWITCH, INPUT);
}

// Infinite loop of the program
void loop() {
  /*int buttonPinState = digitalRead(buttonPin);
  if(buttonPinState == HIGH){
    pulses++;
  }
  m3 = pulses*0.01;
  */
  if(millis() > time + period){
    time = millis();
    Serial.print("Consumo (m3): "); Serial.println(m3);
    Send_Pload((const char*)&m3, sizeof(m3));
    Serial.println("The data was sent");
  }
}

// SendPayload Function => Send messages to the Sigfox Network
void Send_Pload(uint8_t *sendData, int len) {
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  Isigfox->sendPayload(sendData, len, 0, RecvMsg);
  free(RecvMsg);
}

void buttonIR(){
    pulses++;
    m3 = pulses*0.01;
}
