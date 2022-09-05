#include <SPI.h>
#include <MFRC522.h>
// RFID
#define SS_PIN 10
#define RST_PIN 9
#define vibration 2
#define relay 7 // relay pin
#define buzz 4  // buzzer pin
//#define ACCESS_DELAY 2000
//#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte readCard[4];
String MasterTag = "3B10691D"; // ID terdaftar
String tagID = "";             // variabel kosong untuk menampung tagID

void setup()
{

  pinMode(relay, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(vibration, INPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // inisialisasi rfid
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println(" Security System ");
  Serial.println("Tap Your Card!");
}
void loop()
{
  vibrationSensor();
  digitalWrite(relay, HIGH);
  while (getID())
  {

    if (tagID == MasterTag)
    {

      Serial.println(" Access Diterima !");

      // code
      // digitalWrite(buzzPin, HIGH); // aktif low
      delay(1000);
      Serial.print(" ID : ");
      Serial.println(tagID);
      Serial.println("Selamat Datang\n");
      digitalWrite(relay, LOW);
      digitalWrite(buzz, HIGH);
      delay(1000);
    }
    else
    {
      Serial.println(" Access Ditolak!!");
      // digitalWrite(buzzPin, HIGH);
      delay(1000);
      // digitalWrite(buzzPin, LOW);
      delay(1000);
      Serial.print(" ID : ");
      Serial.println(tagID);
      Serial.println("Kartu Tidak Terdaftar!\n");
      digitalWrite(relay, HIGH);
      digitalWrite(buzz, LOW);
      delay(1000);
    }
  }
}

boolean getID() // fungsi untuk membaca kartu rfid
{
  // membaca  PICCs
  if (!mfrc522.PICC_IsNewCardPresent())
  { // Jika PICC baru ditempatkan ke pembaca RFID, lanjutkan
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  { // Sejak PICC ditempatkan, dapatkan Serial dan lanjutkan
    return false;
  }
  tagID = "";
  for (uint8_t i = 0; i < 4; i++)
  { // menggunakan 4 byte UID;
    // readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();  // merubah hasil ke huruf kapital
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
void vibrationSensor()
{
  int vibrationValue = digitalRead(vibration);
  if (vibrationValue == 1)
  {
    digitalWrite(buzz, LOW);
    Serial.println("Getaran terdeteksi");
  }
  else
  {
    digitalWrite(buzz, HIGH);
    Serial.println("Getaran tidak terdeteksi");
  }
}
