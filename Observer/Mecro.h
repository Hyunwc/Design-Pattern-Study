#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <unordered_set>
#include <vector>
using namespace std;

string currentDateTime() //현재 시간 받는 함수.
{
    time_t now = time(0); //현재 시간을 time_t 타입으로 저장.
    struct tm tstruct;
    tstruct = *localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss

    return buf;
}