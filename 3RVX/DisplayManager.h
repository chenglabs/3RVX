// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#pragma once
#include <Windows.h>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "Monitor.h"

class DisplayManager {
public:
    static std::unordered_map<std::wstring, Monitor> &MonitorMap();
    static void UpdateMonitorMap();
    static Monitor Primary();
    static Monitor MonitorAtPoint(POINT &pt, bool workingArea = false);
    static Monitor MonitorAtWindow(HWND hWnd, bool workingArea = false);
    static std::list<DISPLAY_DEVICE> ListAllDevices();

    static bool IsFullscreen(HWND hWnd);
    static bool Direct3DOccluded(HWND hWnd);
private:
    static MONITORINFO Info(HMONITOR monitor);
    static const int Width(HMONITOR monitor);
    static const int Height(HMONITOR monitor);
    static RECT Rect(HMONITOR monitor);

    static BOOL CALLBACK MonitorEnumProc(
        HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
};