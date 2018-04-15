# Custom Version of WiFi Ducky v1.1 (Customized By 777anon666@protonmail.com)

# Live Execution Page
Upload, save and run keystroke injections remotely with an ESP8266 + ATmega32u4 (I used a WHID Cactus for this firmware)

![image of Custom WiFi Ducky Live Execution Page](https://github.com/777anon666/Custom-WiFi-Ducky-v1.1/blob/master/Custom_WiFi_Ducky-v.1.1/images/Live_Execute_Page_screenshot.jpg)

# Info Page
![image of Custom WiFi Ducky Info Page](https://github.com/777anon666/Custom-WiFi-Ducky-v1.1/blob/master/Custom_WiFi_Ducky-v.1.1/images/custom_WiFi_Ducky_Info_page.jpg)

# Settings Page
![image of Custom WiFi Ducky Settings Page](https://github.com/777anon666/Custom-WiFi-Ducky-v1.1/blob/master/Custom_WiFi_Ducky-v.1.1/images/Settings_Page.jpg)




## Contents
- [Introduction](#introduction)
  - [What it is](#what-it-is)
  - [How it works](#how-it-works)
  - [The benefits of adding Wi-Fi](#the-benefits-of-adding-wi-fi)
- [Disclaimer](#disclaimer)
- [Installation](#installation)
  - [Preparation](#preparation)  
  - [ESP8266](#esp8266)
  - [Arduino ATmega32u4](#arduino-atmega32u4)
  - [Wire everything up](#wire-everything-up)
  - [Update ESP8266 over the Webinterface](#update-esp8266-over-the-webinterface)
- [How to use it](#how-to-use-it)
- [Improvements](#improvements)
- [License](#license)
- [Sources and additional Links](#sources-and-additional-links)

## Introduction ##

### What it is

It's a Wi-Fi controlled BadUSB device to remotely execute Ducky Scripts. 

Using a USB device which act as a keyboard to inject keystrokes is well kown these days. 
The [USB Rubber Ducky](https://hakshop.com/products/usb-rubber-ducky-deluxe) by [Hak5](https://www.hak5.org/) is THE hacker gadget for this kind of attack. It introduced a simple script language called *Ducky Script*, which this project uses too.

### How it works

The ESP8266 is a popular Wi-Fi chip used in a lot of projects. Because it's cheap, small and has its own file system ([SPIFFS](https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md)), it's perfect for enabling an easy remote connection and holding Ducky Script payloads.

Although the ESP8266 is awesome, it doesn't have native USB, which means it can't act as a keyboard :(  
([cnlohr](https://github.com/cnlohr) made a cool project on this and added a USB stack himself: https://github.com/cnlohr/espusb. The problem with that is, that it isn't compatible with the current SDK version, also I wanted to use Arduino to make it more user friendly.)  

Here comes the ATmega32u4 into play!  
It can act as keyboard and thanks to [Seytonic](http://youtube.com/seytonic) run Ducky Script ([link](https://github.com/Seytonic/Duckduino-microSD)).  
So what I did is connecting the ATmega to the ESP8266 via serial.

The ESP will open up a Wi-Fi access point and host a webinterface from what you can upload and manage your scripts.  
When you hit run, it will send the script to the ATmega, which then will execute it on the target machine.  

### The benefits of adding Wi-Fi

**But why add Wi-Fi** ...you might ask.  
With Wi-Fi you can upload and run your Ducky Script payloads remotely.  
You just need to plug the device in, connect to its Wi-Fi network and you have full control over the target machine.  

It also gives you one big advantage over other BadUSBs, you can test your scripts live! You don't need to copy them onto a micro-sd card or compile them. You can run them live over the webinterface, which makes its super easy for testing and improving your scripts.

It also adds a lot of possibilites for different attacks.   
You could make the target download executables from the Wi-Fi chip, instead of the internet.
Or execute different attacks and send the results back to the Chip. Or open up a reverse shell on the ESP8266s Wi-Fi.  
And so on... there are so much possibilities!

## Disclaimer

Use it only for testing purposes on your own devices!  
I don't take any responsibility for what you do with this project.  

## Installation

### Short version:
Upload the `arduino_Custom_wifi_ducky_v1.1.ino` sketch From the arduino_wifi_duck Folder using Arduino to your ATmega32u4 and Flash the `esp8266_custom_wifi_ducky_v1.1_4m.ino.generic.bin` From the esp8266_wifi_duck Folder to your ESP8266 using nodemcu-flasher or 
upload the `esp8266_wifi_duck.ino` sketch From the esp8266_wifi_duck Folder using Arduino to your ESP8266.


---

### Preparation

What you will need:
- **ESP8266 Wi-Fi chip**  
  I recommend using an ESP-12. It's widely used, cheap, tiny and has 4MB of flash memory.  
  However if you're a beginner you should probably start with a developer board like the NodeMCU or a Wemos d1 mini.  
- **ATmega32u4**  
  The Arduino Micro and Arduino Leonardo use an ATmega32u4 for example. You could also get a Arduino Pro Micro or other cheap Arduino clones which use the ATmega32u4. I will use an [ATmega32u4 / WHID cactus](https://www.tindie.com/products/aprbrother/cactus-whid-wifi-hid-injector-usb-rubberducky).  
- **(a 3.3V regulator)**  
  I put that in brackets because you will only need this if your ATMega32u4 board doesn't provide 3.3V. The ESP8266 only works with 3.3V, so depending on your board you may need a regulator to get 3.3V out of the 5V.  
- **Some skill, knowledge and common sense on this topic**  
  That's probably the most important part here. **This project is not noob friendly!** If you are a beginner, please start with other projects and get some knowledge about how Arduino and its code works, how to handle errors and how to work with the ESP8266. **I can't cover every little detail here. Please respect that.** Depending on your hardware choices you may need to add or change a bit of the Arduino code.  

### ESP8266

First you will need to flash your ESP8266.  
You can either flash the bin file directly or compile it yourself using Arduino.  

**Upload using Arduino**  
Open the `esp8266_wifi_duck` sketch with [Arduino](https://www.arduino.cc/en/Main/Software).
You need to install the following Librarys:
- [the latest ESP8266 SDK](https://github.com/esp8266/Arduino)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)

Then compile and upload it to your ESP8266 (check if your settings are right).

### Arduino ATmega32u4

Open the `arduino_wifi_duck` sketch in Arduino and upload it to your ATmega32u4 "or" Arduino Based Board.  


### Update ESP8266 over the Webinterface

Once you flashed the software, you can update it over the webinterface.  
Go to `192.168.4.1/update` and upload the new .bin file.  
(In Arduino go to `Sketch`->`Export compiled Binary` to compile your own .bin file)  

## How to use it

Plug your Wi-Fi Ducky in and connect to the new Wi-Fi network `WiFi Duck`. The password is `quackquack`.  
Open your browser and go to `192.168.4.1`. 

![screenshot of the webinterface](https://raw.githubusercontent.com/spacehuhn/wifi_ducky/master/images/wifiduck_screenshot_1.jpg)

There you can now upload, view, delete and run new Ducky Scripts.

**PLEASE NOTE that the max length per row for a script is 600 chars.**

How to write Ducky Scripts: https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript


Happy hacking :)

## Improvements

- change settings within the webinterface (Wi-Fi SSID, password etc.) Settings page dont work you have to compile the settings you want/need in the Arduino sketch then upload it
- full support of all Ducky Script commands (DEFAULTDELAY is missing)
- auto execute scripts settings page dont work for some reason... so just edit the autostart.txt with the script you want to auto execute if you dont want a script to auto execute just delete all the text from the autostart.txt and save it 

## License

This project is licensed under the MIT License - see the [license file](LICENSE) file for details

## Sources and additional Links

The USB Rubber Ducky: https://hakshop.com/products/usb-rubber-ducky-deluxe

The Malduino: (a BadUSB-Arduino/Rubber-Ducky-alternative by Seytonic): https://www.indiegogo.com/projects/malduino-badusb-arduino-usb#/
WHID Cactus: https://www.tindie.com/products/aprbrother/cactus-whid-wifi-hid-injector-usb-rubberducky/
Seytonic: http://youtube.com/seytonic
          https://github.com/seytonic

Arduino Ducky Script interpreter: https://github.com/Seytonic/Duckduino-microSD

Cnlohrs ESP8266 USB Software Driver: https://github.com/cnlohr/espusb
