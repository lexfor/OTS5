#pragma once
#include<vector>
class edge
{
public:
	int id_;
	bool is_oriented_;
	CPoint coordinates_[2];
	int connectID_[2];
	int choosenSide_[2];
	int type_;
	int width_;
	bool drawID;
	enum class Orientation{right,left}orientation_;
	COLORREF color_;
	COLORREF tempColor_;
public:
	edge();
	edge(int, CPoint,int);
	void Draw(HDC);
	void Move(CPoint*, int);
	bool Check(CPoint);
	void MakeNonOrient();
	void MakeOrient();
	void Swap();
};

