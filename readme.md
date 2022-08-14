
# Proyek Sistem Komputer Universitas Gunadarma

"Sistem Parameter Lingkungan Tanaman Cabai Pada Rumah Kaca Dan Notifikasi Kerusakan Dini Berbasis IoT"

# Schematic
![Logo](https://github.com/fauziallagan/rfid/blob/master/schematic.png)

## Documentation

#### Wemos D1 R1 ESP-8266 Pinout

| PIN | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `` | `` |  |
| `` | `` |  |
| `` | `` | |
| `` | `` | |
#### Sensor RFID Pinout

```C++
MFRC522 mfrc522(pinSDA, pinRST);
byte readCard[4];
String MasterTag = "3B10691D"; // ID terdaftar
String tagID = "";

  SPI.begin();
  mfrc522.PCD_Init(); // inisialisasi rfid
  // Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println(" Security System ");

  Serial.println("Tap Your Card!");

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
    }

    // Serial.print(" ID : ");
    // Serial.println(tagID);

    delay(2000);
  }
}
```

| Parameter | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `-`      | `-` | - |


#### Sensor DHT Pinout

```c++
  DHT dht(D5, DHT22);
  int ldrSensors = A0;           // LDR instance named ldr, A0
  int ledTesting = D6;          // declare LED for testing
  int nilai;                   // count LDR
```

| Parameter | Description                |
| :-------- | :------------------------- |
| `DHT` |dht(pin,type)|


#### Get all items

```http
  -
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `-` | `-` | - |
