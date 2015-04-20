//
//  ofxMoment.cpp
//  ofxMoment
//
//  Created by  Tyler Parker on 4/19/15.
//
//

#include "ofxMoment.h"

ofxMoment::ofxMoment(){
    valid = true;
}

ofxMoment::ofxMoment(string timeStr){
    int tzd;
    valid = Poco::DateTimeParser::tryParse(timeStr, currDT, tzd);
}


ofxMoment::~ofxMoment(){};

string ofxMoment::format(){
    string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";
    return format(timeFormat);
}

string ofxMoment::format(string timeFormat){
    return Poco::DateTimeFormatter::format(currDT.timestamp(), timeFormat);
}

bool ofxMoment::isValid(){
    return valid;
}

int ofxMoment::seconds(){
    return currDT.second();
}

void ofxMoment::seconds(int sec){
    DT dt = getDT(currDT);
    dt.sec = sec;
    if(!validDT(dt)){
        // Bubble up to minutes
        add(floor(sec/60), "minutes");
        seconds(sec%60);
    }
    else{
        assignDT(currDT, dt);
    }
}

int ofxMoment::minutes(){
    return currDT.minute();
}

void ofxMoment::minutes(int min){
    DT dt = getDT(currDT);
    dt.min = min;
    if(!validDT(dt)){
        // Bubble up to hours
        add(floor(min/60),"hours");
        minutes(min%60);
    }
    else{
        assignDT(currDT, dt);
    }
}

int ofxMoment::hours(){
    return currDT.hour();
}

void ofxMoment::hours(int hour){
    DT dt = getDT(currDT);
    dt.hour = hour;
    if(!validDT(dt)){
        // Bubble up to days
        add(floor(hour/24),"days");
        hours(hour%24);
    }
    else{
        assignDT(currDT, dt);
    }
}


int ofxMoment::days(){
    return currDT.day();
}

void ofxMoment::days(int day){
    DT dt = getDT(currDT);
    dt.day = day;
    if(!validDT(dt)){
        dt.day = (dt.day - Poco::DateTime::daysOfMonth(dt.year, dt.month));
        add(1, "months");
        days(dt.day);
    }
    else{
        assignDT(currDT, dt);
    }
}

int ofxMoment::months(){
    return currDT.month();
}

void ofxMoment::months(int month){
    DT dt = getDT(currDT);
    dt.month = month;
    if(dt.month > 12){
        // Bubble up to years
        dt.year += floor(month/12);
        dt.month = dt.month%12;
    }
    if(dt.day > Poco::DateTime::daysOfMonth(dt.year, dt.month)){
        dt.day = Poco::DateTime::daysOfMonth(dt.year, dt.month);
    }
    assignDT(currDT, dt);
}


int ofxMoment::years(){
    return currDT.year();
}

void ofxMoment::years(int year){
    DT dt = getDT(currDT);
    dt.year = year;
    assignDT(currDT, dt);
}

void ofxMoment::add(int num, string timeUnit){
    Poco::Timespan ts;
    if(timeUnit == "years" || timeUnit == "y"){
        DT dt = getDT(currDT);
        dt.year += num;
        assignDT(currDT, dt);
        return;
    }
    else if(timeUnit == "months" || timeUnit == "M"){
        int m = months()+num;
        if(m <= 0){
            int yDiff = 0;
            DT dt = getDT(currDT);
            dt.year += floor(m/12)-1;
            dt.month = ((11-m)%12)+1;
            assignDT(currDT, dt);
        }
        else{
            months(m);
        }

        return;
    }
    else if(timeUnit == "weeks" || timeUnit == "w"){
        ts = Poco::Timespan(num*7*Poco::Timespan::DAYS);
    }
    else if(timeUnit == "days" || timeUnit == "d"){
        ts = Poco::Timespan(num*Poco::Timespan::DAYS);
    }
    else if(timeUnit == "hours" || timeUnit == "h"){
        ts = Poco::Timespan(num*Poco::Timespan::HOURS);
    }
    else if(timeUnit == "minutes" || timeUnit == "m"){
        ts = Poco::Timespan(num*Poco::Timespan::MINUTES);
    }
    else if(timeUnit == "seconds" || timeUnit == "s"){
        ts = Poco::Timespan(num*Poco::Timespan::SECONDS);
    }
    else if(timeUnit == "milliseconds" || timeUnit == "ms"){
        ts = Poco::Timespan(num*Poco::Timespan::MILLISECONDS);
    }
    else{
        ofLogError("ofxMoment","Invalid time unit '"+timeUnit+"'");
        return;
    }
    
    currDT += ts;
}

void ofxMoment::subtract(int num, string timeUnit){
    add(-1*num,timeUnit);
}

DT ofxMoment::getDT(){
    getDT(currDT);
}

DT ofxMoment::getDT(Poco::DateTime datetime){
    DT dt;
    dt.year = datetime.year();
    dt.month = datetime.month();
    dt.day = datetime.day();
    dt.hour = datetime.hour();
    dt.min = datetime.minute();
    dt.sec = datetime.second();
    dt.ms = datetime.millisecond();
    dt.us = datetime.microsecond();
    dt.jd = datetime.julianDay();
    return dt;
}

bool ofxMoment::validDT(DT dt){
    return Poco::DateTime::isValid(dt.year, dt.month, dt.day, dt.hour, dt.min, dt.sec, dt.ms, dt.us);
}

bool ofxMoment::assignDT(Poco::DateTime& datetime, DT dt){
    bool vdt = validDT(dt);
    if(vdt){
        datetime.assign(dt.year, dt.month, dt.day, dt.hour, dt.min, dt.sec, dt.ms, dt.us);
    }
    return vdt;
}