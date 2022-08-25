// koneksi ke blynk
#define BLYNK_TEMPLATE_ID "TMPL6Fyoj83m"
#define BLYNK_DEVICE_NAME "PI"
#define BLYNK_AUTH_TOKEN "h16kOyMh1L4Xu-5985_NOaoMG-5jNAPZ" // Authentication
#define BLYNK_PRINT Serial

// Library yang digunain
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// passive buzzer
#define buzzPin D8 // Buzzer dihubungkan ke pin D8

// sensor getaran
#define vibrationSensorPin D2 // Vibration Sensor di hubungkan ke Pin D2
int vibrationSensorState = 0; // Status saat pertama mulai = 0

// RFID
const int pinRST = 5; // pin RST  module RC522
const int pinSDA = 4; // pin SDA  module RC522
MFRC522 mfrc522(pinSDA, pinRST);
byte readCard[4];
String MasterTag = "3B10691D"; // ID terdaftar
String tagID = "";             // variabel kosong untuk menampung tagID

// relay
int relay = D11;

// koneksi wifi + blynk cloud
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

// virtual pin untuk LCD
WidgetLCD lcd(V1);

void setup()
{
  Blynk.begin(auth, ssid, pass); // inisialisasi koneksi wifi
  pinMode(buzzPin, OUTPUT);      // set buzzer sebagai output
  pinMode(relay, OUTPUT);
  pinMode(vibrationSensorPin, INPUT); // Jadikan Vibration sensor sebagai input
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // inisialisasi rfid
  // Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println(" Security System ");
  Serial.println("Tap Your Card!");
  lcd.print(0, 0, "Security System");
  lcd.print(1, 0, "Tap Your Card!");
}
void loop()
{
  // Blynk.run();                 // menjalankan blynk

  // vibrationSensorState = digitalRead(vibrationSensorPin);
  // vibration(); // fungsi vibration
  // rfid();      // fungsi rfid

  // lcd.clear();

  // if (vibrationSensorState == LOW)
  // {

  //   Serial.println("Silahkan Tempelkan kartu!");
  //   lcd.print(1, 0, "Silahkan Tempelkan kartu");
  //   rfid(); // fungsi rfid
  // }
  // else
  // {
  //   Serial.println("Getaran Terdeteksi!");
  //   lcd.print(0, 0, "Getaran Terdeteksi!");
  //   digitalWrite(buzzPin, LOW);
  //   delay(1000);
  //   digitalWrite(buzzPin, HIGH);
  //   delay(1000);
  //   Serial.println("Silahkan Tempelkan kartu!");
  //   lcd.print(1, 0, "Silahkan Tempelkan kartu");
  //   rfid(); // fungsi rfid
  // }
  rfid();
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

/* Alert!
  ================== Wilayah Testing Sensor =======================


*/
void rfid()
{

  while (getID())
  {

    if (tagID == MasterTag)
    {

      Serial.println(" Access Diterima !");

      // code
      digitalWrite(buzzPin, HIGH); // aktif low
      delay(1000);
      Serial.print(" ID : ");
      Serial.println(tagID);
      Serial.println("Selamat Datang\n");
      digitalWrite(relay, HIGH);
      delay(10000);
    }
    else
    {
      Serial.println(" Access Ditolak!!");
      digitalWrite(buzzPin, HIGH);
      delay(1000);
      digitalWrite(buzzPin, LOW);
      delay(1000);
      Serial.print(" ID : ");
      Serial.println(tagID);
      Serial.println("Kartu Tidak Terdaftar!\n");
      digitalWrite(relay, LOW);
      delay(10000);
    }

    // Serial.print(" ID : ");
    // Serial.println(tagID);

    delay(2000);
  }
}
void vibration()
{

  if (vibrationSensorState == 1)
  { // Jika ada getaran di sensor = HIGH
    Serial.println("Getaran Terdeteksi!");
    digitalWrite(buzzPin, LOW);
    delay(1000);
    digitalWrite(buzzPin, HIGH);
    delay(1000);
  }
}

void relayTesting()
{
  digitalWrite(relay, HIGH);
  delay(1000);
  digitalWrite(relay, LOW);
}