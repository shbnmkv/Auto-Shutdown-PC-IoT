#include <ESP8266WiFi.h>

const char* ssid = "SSID_WIFImu";
const char* password = "pwnyadisini";
const int relayPin = 4;  
bool isDisconnected = false;
bool initialized = false;  

void setup() {
  delay(2000);  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  
  
  connectToWiFi(); // Mencoba koneksi WiFi awal
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  
  // Mencoba menghubungkan ke WiFi selama 5 detik (10 kali)
  for (int attempts = 0; attempts < 10 && WiFi.status() != WL_CONNECTED; attempts++) {
    delay(500);  
  }
  
  // Jika terhubung, tandai sebagai terinisialisasi
  if (WiFi.status() == WL_CONNECTED) {
    initialized = true; 
    digitalWrite(relayPin, HIGH);  // Pastikan relay tetap mati
  }
}

void loop() {
  // Jika sudah terinisialisasi, periksa status WiFi
  if (initialized) {
    if (WiFi.status() != WL_CONNECTED) {
      if (!isDisconnected) {
        // Jika terputus, aktifkan relay sekali
        digitalWrite(relayPin, LOW);  // Nyalakan relay
        delay(300);                   // Tunggu 0,3 detik
        digitalWrite(relayPin, HIGH); // Matikan relay
        
        isDisconnected = true;  // Tandai sebagai terputus
      }
    } else {
      // Reset status disconnection jika terhubung
      isDisconnected = false;  
    }
  } else {
    // Jika belum terinisialisasi, coba sambungkan ke WiFi
    connectToWiFi(); // Panggil fungsi untuk mencoba sambungan
  }

  delay(1000);  // Cek status WiFi setiap detik
}
