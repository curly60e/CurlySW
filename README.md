# CurlySmartWatch
https://github.com/curly60e/CurlySmartWatch

<img src="home.jpg" width="30%" />


This repo's format:

Bin folder contains the current bin that you can use esptool (.py or .exe) to install the current bin to the Watchy.

For those **WANTING** to use this Watchy code without programming and having to install Arduino or PlatformIO, you *CAN* install it with the base Watchy face you received when you got your Watchy.

1. Download the Bin folder's file `CurlySW.ino.esp32.bin` onto the machine that you can connect your Watchy to by WiFi (laptop, cellphone, tablet, etc).
2. Once downloaded, for speed, turn the WiFi off on the device you're going to use with the Watchy, but keep the WiFi settings open.
3. Go into the Watchy's menu, push up (so it goes up to the bottom) until you stop on Setup WiFi.  Press Menu to continue.
4. Turn your device's WiFi back on and find the `"Watchy AP"` connection on your device and connect to it.
5. Once connected, go to a web browser and type in the IP address from the Watchy's screen in the address bar of the web browser and press Enter.
6. On the web page that showed up, you'll see a button called `"Update"`, click that (left side of image below).
![WiFiManager](https://github.com/GuruSR/Watchy_GSR/blob/main/Images/OTAUpdate.JPG)
7. Press the `Choose File` button (right side of image above) then locate and select the `CurlySW.ino.esp32.bin` you downloaded in Step 1.
8. Click the RED colored button below that showed up and wait.  (It doesn't show any progress until it says it failed or succeeded.)
9. If all went well, you'll see the success message and your Watchy will reboot with this Watchy face.
10. If you didn't get this far, then you either didn't connect to Watchy AP fast enough or something else happened, so try again at Step 2.


## SmartWatch
https://github.com/theRealc2c2/SmartWatch  

## Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy  

## Face for Watchy watch  
https://watchy.sqfmi.com
