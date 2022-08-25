#include <SPI.h>
#include <MFRC522.h>
// RFID
const int pinRST = 5; // pin RST  module RC522
const int pinSDA = 4; // pin SDA  module RC522
MFRC522 mfrc522(pinSDA, pinRST);
byte readCard[4];
String MasterTag = "3B10691D"; // ID terdaftar
String tagID = "";             // variabel kosong untuk menampung tagID
int relay = D11;

void setup()
{

  pinMode(relay, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // inisialisasi rfid
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println(" Security System ");
  Serial.println("Tap Your Card!");
}
void loop()
{
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
      digitalWrite(relay, HIGH);
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
      digitalWrite(relay, LOW);
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
