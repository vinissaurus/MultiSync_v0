#include <WiFi.h>
#include "time.h"

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* ntpServer = "pool.ntp.org"; // NTP server
const long gmtOffset_sec = 3600;       // Adjust for your timezone (e.g., -18000 for EST)
const int daylightOffset_sec = 3600;   // Adjust for daylight savings

unsigned long lastSyncTime = 0;        // Timestamp of last NTP sync
unsigned long lastMillis = 0;          // Snapshot of millis() at last NTP sync
float driftAdjustment = 1.0;           // Drift adjustment factor (1.0 = no drift)

struct tm timeinfo;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initial NTP sync
  syncWithNTP();
}

void loop() {
  // Calculate the current time using local clock
  unsigned long nowMillis = millis();
  unsigned long elapsedMillis = (nowMillis - lastMillis) * driftAdjustment; // Adjust for drift
  unsigned long currentTime = lastSyncTime + (elapsedMillis / 1000);        // Calculate current time

  // Print the current time
  Serial.println("Local Time: " + getFormattedTime(currentTime));
  
  delay(1000); // Update every second

  // Sync with NTP every 5 minutes (300 seconds)
  if (elapsedMillis >= 300000) {
    syncWithNTP();
  }
}

// Sync time with NTP server
void syncWithNTP() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if (getLocalTime(&timeinfo)) {
    unsigned long ntpTime = mktime(&timeinfo);   // Get current time from NTP
    unsigned long nowMillis = millis();

    // Calculate drift
    if (lastSyncTime > 0) {
      unsigned long elapsedLocal = (nowMillis - lastMillis); // Millis elapsed since last sync
      unsigned long elapsedNTP = ntpTime - lastSyncTime;     // Seconds elapsed in real time
      driftAdjustment = (float)elapsedNTP / (elapsedLocal / 1000.0); // Adjust drift
    }

    // Update last sync time
    lastSyncTime = ntpTime;
    lastMillis = nowMillis;

    Serial.println("NTP Time Synced: " + getFormattedTime(lastSyncTime));
    Serial.printf("Drift Adjustment: %.6f\n", driftAdjustment);
  } else {
    Serial.println("Failed to sync with NTP");
  }
}

// Format the given time_t timestamp into a readable string
String getFormattedTime(unsigned long timestamp) {
  time_t rawTime = timestamp;
  struct tm *timeinfo = localtime(&rawTime);
  char buffer[26];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return String(buffer);
}