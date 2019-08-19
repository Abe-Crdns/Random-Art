#ifndef LPCLIB_H
#define LPCLIB_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

typedef unsigned char smallint;

#define Error(x) { cerr << "*** Runtime Error: " << x << endl; exit(-1); }

void Pause(double seconds);

string IntToString(int num);

string DoubleToString(double num);

int StringToInt(string str);

double StringToDouble(string str);

string ConvertToLowerCase(string str);

string ConvertToUpperCase(string str);

struct ColImpl;
struct Color
{
public:
    Color(unsigned char r=0, unsigned char g=0, unsigned char b=0);
    
private:
    ColImpl * _priv;
    friend class GraphicsWindow;
};

struct GWImpl;
class GraphicsWindow
{
    
public:
    GraphicsWindow(int width, int height, string title);
    int GetWidth() const;
    int GetHeight() const;
    void Refresh();
    
    void DrawLine(int x1, int y1, int x2, int y2, Color color);
    void DrawCircle(int x, int y, int radius, Color color, bool filled = false);
    void DrawEllipse(int x, int y, int xradius, int yradius, Color color, bool filled = false);
    void DrawRectangle(int x, int y, int width, int height, Color color, bool filled = false);
    void DrawString(string str, int x, int y, Color color, int fontsize = 13);
    void DrawImage(string imageFileName, int x, int y, int width = 0, int height = 0);

    void WaitForMouseDown();
    void WaitForMouseUp();
    int MouseX();
    int MouseY();
    bool MouseIsDown();
    
    char WaitForKeyPress();
    bool KeyPressed(string key);
    
    void Pause(double seconds);
    
    string WhatKey();

    
public:
    ~GraphicsWindow();
    
private:
    GWImpl * _priv;

    
};

#endif
