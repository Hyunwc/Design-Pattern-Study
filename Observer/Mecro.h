#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <unordered_set>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

string currentDateTime() //���� �ð� �޴� �Լ�.
{
    time_t now = time(0); //���� �ð��� time_t Ÿ������ ����.
    struct tm tstruct;
    //tstruct = *localtime(&now);
    localtime_s(&tstruct, &now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss

    return buf;
}