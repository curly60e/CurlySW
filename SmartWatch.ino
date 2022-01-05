/*
CurlySmartWatchy
https://github.com/curly60e/CurlySmartWatch

Based on SmartWatchy
https://github.com/theRealc2c2/SmartWatch

Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy

Face for Watchy watch
https://watchy.sqfmi.com
*/

#include <Watchy.h> //include the Watchy library
#include "Teko_Regular12pt7b.h"
#include "Teko_Regular50pt7b.h"
#include "icons.h"
#include "settings.h"
#include <NTPClient.h>

class WatchFace : public Watchy { //inherit and extend Watchy class
  using Watchy::Watchy;
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h;
      String textstring;
      bool light = true; // left this here if someone wanted to tweak for dark

      //resets step counter at midnight everyday
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }

      // ** DRAW **

      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.fillRoundRect(2,2,196,196,8,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(6,6,188,188,5,light ? GxEPD_WHITE : GxEPD_BLACK);
      
      display.setFont(&Teko_Regular50pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw hours
      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100-5);
      display.print(textstring);
      
      //draw minutes
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100+3+h);
      display.print(textstring);

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
          display.setCursor(25, 90);
          //lasty += -70;
      }else{
          display.setFont(&Teko_Regular12pt7b);
          display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
          display.setCursor(25, 90);
          //lasty += -70;
      }
      textstring = "C";
      display.println(temperature);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(43, 90);
      display.print(textstring);
      //display.drawBitmap(40, 60, currentWeather.isMetric ? celsius : fahrenheit, 26, 20, light ? GxEPD_BLACK : GxEPD_WHITE);
      const unsigned char* weatherIcon;
  
      //https://openweathermap.org/weather-conditions
      if(weatherConditionCode > 801){//Cloudy
      weatherIcon = cloudy;
      }else if(weatherConditionCode == 801){//Few Clouds
      weatherIcon = cloudsun;
      }else if(weatherConditionCode == 800){//Clear
      weatherIcon = sunny;
      }else if(weatherConditionCode >=700){//Atmosphere
      weatherIcon = atmosphere;
      }else if(weatherConditionCode >=600){//Snow
      weatherIcon = snow;
      }else if(weatherConditionCode >=500){//Rain
      weatherIcon = rain;
      }else if(weatherConditionCode >=300){//Drizzle
      weatherIcon = drizzle;
      }else if(weatherConditionCode >=200){//Thunderstorm
      weatherIcon = thunderstorm;
      }else
      return;
      display.drawBitmap(16, 40, weatherIcon, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, light ? GxEPD_BLACK : GxEPD_WHITE);
    }

};


WatchFace m(settings); //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}
