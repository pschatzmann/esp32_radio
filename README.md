# ESP32/Vue Radio Player

I wanted to have a nice looking Radio Player that is working together with an ESP32 Micro Controller.
Here is the result: The GUI was written with Vue.js. I am using [radiobrowser-api-rust](https://github.com/segler-alex/radiobrowser-api-rust) to find the Radio Stations - so many thanks to Alex Segler for providing this project.

The Micro Controller is controlled by a Webservice and can provide two output modes: you can stream the Radios direcly or you can activate Bluetooth and stream the Radios from your GUI device via Bluetooth.

Of cause you can also enjoy this player without an ESP32:

http://github.pschatzmann.ch/esp32_radio

