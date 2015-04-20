//
//  ofxMoment.h
//  ofxMoment
//
//  Created by  Tyler Parker on 4/19/15.
//
//


#include "ofMain.h"

#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/URI.h"

struct DT{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;
    int ms = 0;
    int us = 0;
//    int tzd = 0;
    double jd = 0.0;
};
class ofxMoment{
public:
    ofxMoment();
    ofxMoment(string timeStr);
    ~ofxMoment();
    
    ///   * %w - abbreviated weekday (Mon, Tue, ...)
    ///   * %W - full weekday (Monday, Tuesday, ...)
    ///   * %b - abbreviated month (Jan, Feb, ...)
    ///   * %B - full month (January, February, ...)
    ///   * %d - zero-padded day of month (01 .. 31)
    ///   * %e - day of month (1 .. 31)
    ///   * %f - space-padded day of month ( 1 .. 31)
    ///   * %m - zero-padded month (01 .. 12)
    ///   * %n - month (1 .. 12)
    ///   * %o - space-padded month ( 1 .. 12)
    ///   * %y - year without century (70)
    ///   * %Y - year with century (1970)
    ///   * %H - hour (00 .. 23)
    ///   * %h - hour (00 .. 12)
    ///   * %a - am/pm
    ///   * %A - AM/PM
    ///   * %M - minute (00 .. 59)
    ///   * %S - second (00 .. 59)
    ///   * %s - seconds and microseconds (equivalent to %S.%F)
    ///   * %i - millisecond (000 .. 999)
    ///   * %c - centisecond (0 .. 9)
    ///   * %F - fractional seconds/microseconds (000000 - 999999)
    ///   * %z - time zone differential in ISO 8601 format (Z or +NN.NN)
    ///   * %Z - time zone differential in RFC format (GMT or +NNNN)
    ///   * %% - percent sign
    
    string format();
    string format(string timeFormat);

    bool isValid();
    
    int seconds();
    void seconds(int sec);
    
    int minutes();
    void minutes(int min);
    
    int hours();
    void hours(int hour);
    
    int days();
    void days(int day);
    
    int months();
    void months(int month);
    
    int years();
    void years(int year);
    
    void add(int num, string timeUnit);
    void subtract(int num, string timeUnit);
    
    
    static DT getDT(Poco::DateTime datetime);
    DT getDT();
private:
    Poco::DateTime currDT;
    bool valid;
    
    bool assignDT(Poco::DateTime& datetime, DT dt);
    bool validDT(DT dt);
};
