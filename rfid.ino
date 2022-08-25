
int relay = D11;

void setup()
{

  pinMode(relay, OUTPUT);

  Serial.begin(9600);

  Serial.println(" Security System ");
  Serial.println("Tap Your Card!");
}
void loop()
{

  digitalWrite(relay, HIGH);
  delay(1000);
  digitalWrite(relay, LOW);
}
