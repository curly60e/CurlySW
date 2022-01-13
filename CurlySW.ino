/*
CurlySW
https://github.com/curly60e/CurlySW

SmartWatchy
https://github.com/theRealc2c2/SmartWatch

Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy

Face for Watchy watch
https://watchy.sqfmi.com
*/

#include <Watchy.h> //include the Watchy library
#include "resource.h"
#include "settings.h"

class WatchFace : public Watchy { //inherit and extend Watchy class
  using Watchy::Watchy;
  public:


    bool VibeMode = false;
    //(function below toggles the motor on or off)
    void VibeTo(bool Mode){
        if (Mode != VibeMode){
            if (Mode){
                sensor.enableFeature(BMA423_WAKEUP, false);
                pinMode(VIB_MOTOR_PIN, OUTPUT);
                digitalWrite(VIB_MOTOR_PIN, true);
            }else{
                digitalWrite(VIB_MOTOR_PIN, false);
                sensor.enableFeature(BMA423_WAKEUP, true);
            }
            VibeMode = Mode;
        }
    }
    
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h;
      String textstring;
      String textstringMinute;
      bool light = true; // left this here if someone wanted to tweak for dark
      //resets step counter at midnight everyday
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }
      
      //pinMode(MENU_BTN_PIN, INPUT);
      pinMode(BACK_BTN_PIN, INPUT);
      //pinMode(UP_BTN_PIN, INPUT);
      //pinMode(DOWN_BTN_PIN, INPUT);
   
      //if (digitalRead(MENU_BTN_PIN) == 1) {
      //  VibeTo(true);
      //  delay(100);
      //  VibeTo(false);
      //} 
      if (digitalRead(BACK_BTN_PIN) == 1) {
        VibeTo(true);
        delay(50);
        VibeTo(false);
      } 
      //if (digitalRead(UP_BTN_PIN) == 1) {
      //  VibeTo(true);
      //  delay(100);
      //  VibeTo(false);
      //} 
      //if (digitalRead(DOWN_BTN_PIN) == 1) {
      //  VibeTo(true);
      //  delay(100);
      //  VibeTo(false);
      //}
        
      // ** DRAW **

      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.fillRoundRect(2,2,196,196,8,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(6,6,188,188,5,light ? GxEPD_WHITE : GxEPD_BLACK);
      
      display.setFont(&PebblecoNumbers_MONO32pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw time
      textstring = currentTime.Hour;
      textstring += ":";
      if (currentTime.Minute < 10) {
        textstring += "0";
      } else {
        textstring += "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(96-w/2,88);
      display.print(textstring);
      
      //vibrate per o'clock
      if (currentTime.Minute < 10) {
        textstringMinute = "0";
      } else {
        textstringMinute = "";
      }
      textstringMinute += currentTime.Minute;
      display.getTextBounds(textstringMinute, 0, 0, &x1, &y1, &w, &h);
      if (textstringMinute == "00") {
        VibeTo(true);
        delay(100);
        VibeTo(false);
      }

      // draw battery
      display.fillRoundRect(16,16,34,12,4,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(49,20,3,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(18,18,30,8,3,light ? GxEPD_WHITE : GxEPD_BLACK);
      float batt = (getBatteryVoltage()-3.3)/0.9;
      if (batt > 0) {
       display.fillRoundRect(20,20,26*batt,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      }                 

      display.setFont(&Teko_Regular12pt7b);
      lasty = 200 - 16;

      //draw steps
      textstring = sensor.getCounter();
      textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.fillRoundRect(16,lasty-h-2,w + 7,h+4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setCursor(19, lasty-3);
      display.setTextColor(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.print(textstring);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      lasty += -8-h;

      // draw year
      textstring = currentTime.Year + 1970;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;

      // draw date
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;
      
      // draw day
      textstring = dayStr(currentTime.Wday);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -40;

      const uint8_t WEATHER_ICON_WIDTH = 48;
      const uint8_t WEATHER_ICON_HEIGHT = 32;

      weatherData currentWeather = getWeatherData();
  
      int8_t temperature = currentWeather.temperature;
      int16_t weatherConditionCode = currentWeather.weatherConditionCode;
  
      display.setFont(&Teko_Regular12pt7b);
      display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
      if(159 - w - x1 > 87){
          display.setCursor(140, 175);
          //lasty += -70;
      }else{
          display.setFont(&Teko_Regular12pt7b);
          display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
          display.setCursor(140, 175);
          //lasty += -70;
      }
      textstring = "C";
      display.println(temperature);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(158, 175);
      display.print(textstring);
      
      light = (currentTime.Hour >= 18 || currentTime.Hour <= 5) ? true : false;
      const unsigned char* weatherIcon;
  
      //https://openweathermap.org/weather-conditions
      if (weatherConditionCode == 999) { //RTC
        weatherIcon = rtc;
      } else if (weatherConditionCode == 998) { //RTC SLEEEP
        weatherIcon = rtcsleep;
      } else if (weatherConditionCode > 801 && weatherConditionCode < 805) { //Cloudy
        weatherIcon = scatteredclouds;
      } else if (weatherConditionCode == 801) { //Few Clouds
        weatherIcon = (light) ? fewcloudsnight : fewclouds;
      } else if (weatherConditionCode == 800) { //Clear
        weatherIcon = (light) ? clearskynight : clearsky;
      } else if (weatherConditionCode >= 700) { //Atmosphere
        weatherIcon = mist;
      } else if (weatherConditionCode >= 600) { //Snow
        weatherIcon = snow;
      } else if (weatherConditionCode >= 500) { //Rain
        weatherIcon = rain;
      } else if (weatherConditionCode >= 300) { //Drizzle
        weatherIcon = drizzle;
      } else if (weatherConditionCode >= 200) { //Thunderstorm
        weatherIcon = thunderstorm;
      }
    
      display.fillRect(141, 91, 49, 44, GxEPD_WHITE); //Redraw Helper
      display.drawBitmap(130, 115, weatherIcon, 45, 40,GxEPD_BLACK);
    }

};


WatchFace m(settings); //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
