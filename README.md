# MultiSync_v0
This is the firmware for an ESP32 based board which will try to register and control ambient parameters.

MultiSync_V0 is the root board for other later applications that will use it. 

This board is only supposed to connect to a Wifi network and do scheduled tasks. 
The captive portal will only handle wifi credentials and timezone config, and the other interactions should be via MQTT.

Here are the appliances that I intend to use with this board:
- Reading a DHT22 sensor and controlling an AC Unit via infrared
- Switching lights
-

These functions are supposed run via schedulling in it's own Control Panel.
