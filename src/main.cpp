#include <Arduino.h>
#include <Wire.h>
#include <PCF8563.h>
#include <string>
#include "date_utils.h"
#include "platform/mbed_rtc_time.h"

PCF8563 pcf;

time_t time_from_rtc(Time &pcfTime);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Wire.begin();

  pcf.init(); // initialize the clock

  // initial setup for RTC
  // pcf.stopClock(); // stop the clock
  // std::string date = std::string(__DATE__);
  // std::string month = date.substr(0, 3);
  // std::string day = date.substr(4, 2);
  // std::string year = date.substr(9, 2);

  // std::string time = std::string(__TIME__);
  // std::string hour = time.substr(0, 2);
  // std::string minute = time.substr(3, 2);
  // std::string second = time.substr(6, 2);

  // pcf.setYear(std::atoi(year.c_str()));       // set year
  // pcf.setMonth(get_month_from_string(month)); // set month
  // pcf.setDay(std::atoi(day.c_str()));         // set dat
  // pcf.setHour(std::atoi(hour.c_str()));       // set hour
  // pcf.setMinut(std::atoi(minute.c_str()));    // set minut
  // pcf.setSecond(std::atoi(second.c_str()));   // set second

  pcf.startClock(); // start the clock

  delay(1000);

  Time nowTime = pcf.getTime();
  time_t t = time_from_rtc(nowTime);  
  Serial.println((long long)t);

  set_time(t);
}

void loop()
{
  Time nowTime = pcf.getTime(); // get current time

  // print current time
  Serial.print(nowTime.day);
  Serial.print("/");
  Serial.print(nowTime.month);
  Serial.print("/");
  Serial.print(nowTime.year);
  Serial.print(" ");
  Serial.print(nowTime.hour);
  Serial.print(":");
  Serial.print(nowTime.minute);
  Serial.print(":");
  Serial.println(nowTime.second);


  time_t now = time(nullptr);
  Serial.println((long long)now);
  delay(1000);
}

time_t time_from_rtc(Time &pcfTime)
{
  struct tm timeinfo{};
  timeinfo.tm_year = pcfTime.year + 100;
  timeinfo.tm_mon = pcfTime.month - 1;
  timeinfo.tm_mday = pcfTime.day;
  timeinfo.tm_hour = pcfTime.hour;
  timeinfo.tm_min = pcfTime.minute;
  timeinfo.tm_sec = pcfTime.second;
  timeinfo.tm_isdst = 0;

  return mktime(&timeinfo);
}