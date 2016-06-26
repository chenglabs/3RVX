// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#include "Meter.h"
#include <math.h>
#include <sstream>

Meter::Meter(std::wstring bitmapName, int x, int y, int units) :
_value(0.0f),
_drawnValue(-1.0f),
_units(units),
_drawnUnits(-1) {
    _rect.X = x;
    _rect.Y = y;

    Gdiplus::Bitmap *bmp = Gdiplus::Bitmap::FromFile(
        bitmapName.c_str(), false);
    CLOG(L"Loading meter bitmap: %s\nStatus: %d",
        bitmapName.c_str(), bmp->GetLastStatus());
    _bitmap = bmp;

    _rect.Width = bmp->GetWidth();
    _rect.Height = bmp->GetHeight();
}

Meter::Meter(int x, int y, int units) :
_bitmap(NULL),
_value(0.0f),
_drawnValue(-1.0f),
_units(units),
_drawnUnits(-1) {
    _rect.X = x;
    _rect.Y = y;
}

Meter::~Meter() {
    delete _bitmap;
}

float Meter::Value() const {
    return _value;
}

void Meter::Value(float value) {
    if (value > 1.0) { value = 1.0; }
    if (value < 0) { value = 0; }

    _value = value;
}

void Meter::UpdateDrawnValues() {
    _drawnUnits = CalcUnits();
    _drawnValue = _value;
}

int Meter::Units() const {
    return _units;
}

bool Meter::Dirty() {
    /* Not dirty if the meter's value is unchanged */
    if (Value() == _drawnValue) {
        return false;
    }

    /* Not dirty if the change in value won't affect the meter graphically */
    if (CalcUnits() == _drawnUnits) {
        return false;
    }

    return true;
}

int Meter::CalcUnits() {
    //return (int) ceil(_value * _units - 0.00001f);
    return (int) round(_value * _units - 0.00001f);
}

int Meter::X() const {
    return _rect.X;
}

int Meter::Y() const {
    return _rect.Y;
}

void Meter::X(int x) {
    _rect.X = x;
}

void Meter::Y(int y) {
    _rect.Y = y;
}

int Meter::Width() const {
    return _rect.Width;
}

int Meter::Height() const {
    return _rect.Height;
}

std::wstring Meter::ToString() {
    std::wstringstream ss;
    ss << L"Geometry: (" << _rect.X << L", " << _rect.Y << "); ";
    ss << _rect.Width << L"x" << _rect.Height << std::endl;
    ss << L"Units: " << Units() << std::endl;
    ss << L"Current Value: " << Value() << L" (" << CalcUnits() << L" units)";
    return ss.str();
}