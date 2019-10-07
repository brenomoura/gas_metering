const int reed_switch = 2;

int pulses = 0;
float m3 = 0.00;

void setup()
{
  Serial.begin(9600);
  pinMode(reed_switch, INPUT);

}

void loop()
{
  int reed_swicthState = digitalRead(reed_switch);

  
  if(reed_swicthState == HIGH){
    pulses++;
  }
  m3 = pulses*0.01;
  Serial.print("Consumo: ");
  Serial.print(m3);
  Serial.print(" m3\n");
  delay(100);
 }
