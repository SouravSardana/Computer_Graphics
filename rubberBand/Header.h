#pragma once
#ifndef DATA_H_         //if not define-if the header file is not defined, compile it, if the header file already exists, do not repeat the compilation  
#define DATA_H_
#include<vector>
using namespace std;
class point //Point class, which stores the two coordinate values ​​of a point
{
public:
	int x;
	int y;
};
class polygon             //Polygon class, save a polygon
{
public:
	vector<point> p;                  //The vertices of the polygon
};
#endif