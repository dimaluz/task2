// task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

struct Point{
	double x;
	double y;
	Point(double _x, double _y){
		x=_x; y=_y;
	}
};

int calculation(string, string);
int fileopen(string, vector<Point>*);
double rotate(Point, Point, Point);
int intersect(Point, Point, Point, Point);
int pointloc(vector<Point>*, Point);

int main(int argc, char* argv[]){
	if(argc<3)
		cout<<"WARNING main(): You should specify all files."<<endl;
	else{
		string filename1, filename2;
		filename1=argv[1]; filename2=argv[2];
		calculation(filename1, filename2);
	}
	system("pause");
	return 0;
}

int calculation(string file1, string file2){
	vector<Point> Vertices; vector<Point> Points;
	if(fileopen(file1, &Vertices)==-1){
		cout<<"WARNING calculation(): File" << &file1 << " cannot be opened."<<endl;
		return -1;
	}
	if(fileopen(file2, &Points)==-1){
		cout<<"WARNING calculation(): File" << &file2 << " cannot be opened."<<endl;
		return -1;
	}
	
	for(Point point: Points)
		cout<<pointloc(&Vertices, point)<<endl;

	return 0;
}
int fileopen(string filename, vector<Point>* buffer){
	ifstream fin(filename, ios_base::in);
	if(!fin.is_open()){
		fin.close();
		return -1;
	}
	else{
		double x, y;
		for(fin>>x>>y; !fin.eof(); fin>>x>>y)
			(*buffer).push_back(Point(x, y));
		fin.close();
	}
	return 0;
}
double rotate(Point A, Point B, Point C){
	return (B.x - A.x)*(C.y - B.y) - (B.y - A.y)*(C.x - B.x);
}
int intersect(Point A, Point B, Point C, Point D){
	double expression1=rotate(A, B, C)*rotate(A, B, D);
	double expression2=rotate(C, D, A)*rotate(C, D, B);
	if(expression1<0 && expression2<0)
		return 1;
	else if(expression1<=0.00000001 && expression2<0)
		return 0;
	else 
		return -1;
	//return (expression1 <= 0 && expression2 < 0);
}
int pointloc(vector<Point>* vertices, Point point){
	int N = (*vertices).size();
	for(int i=0; i<N; i++){
		if(point.x==(*vertices)[i].x && point.y==(*vertices)[i].y)
			return 0;
	}
	double exp1 = rotate((*vertices)[0], (*vertices)[1], point);
	double exp2 = rotate((*vertices)[0], (*vertices)[N-1], point);
	if(exp1 > 0 || exp2 < 0)
		return 3;
	int result; double expr1, expr2;
	if(rotate((*vertices)[0], (*vertices)[2], point)>0){
		result = intersect((*vertices)[1], (*vertices)[2], (*vertices)[0], point);
		expr1=rotate((*vertices)[1], (*vertices)[2], (*vertices)[0])*rotate((*vertices)[1], (*vertices)[2], point);
		expr2=rotate((*vertices)[0], point, (*vertices)[1])*rotate((*vertices)[0], point, (*vertices)[2]);
	}
	else{
		result = intersect((*vertices)[2], (*vertices)[3], (*vertices)[0], point);
		expr1=rotate((*vertices)[2], (*vertices)[3], (*vertices)[0])*rotate((*vertices)[2], (*vertices)[3], point);
		expr2=rotate((*vertices)[0], point, (*vertices)[2])*rotate((*vertices)[0], point, (*vertices)[3]);
	}
	if(result==-1 && (abs(expr1) > 0.000001 && abs(expr2) > 0.000001))
		return 2;
	else if(result==1 && (abs(expr1)>0.000001 && abs(expr2)>0.000001))
		return 3;
	else
		return 1;
}
