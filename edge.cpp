#include "pch.h"
#include "edge.h"
edge::edge() : id_(0),is_oriented_(true)
{
	color_ = RGB(0, 0, 0);
	type_ = PS_SOLID;
	width_ = 5;
	drawID = false;
}
edge::edge(int ID, CPoint point,int FigID) : id_(ID)
{
	type_ = PS_SOLID;
	width_ = 5;
	color_ = RGB(0, 0, 0);
	coordinates_[0] = point;
	is_oriented_ = false;
	connectID_[0] = FigID;
	orientation_ = Orientation::right;
	drawID = false;
}

void edge::Move(CPoint moveCoordinates[2], int ID) {
	CPoint diff;
	int temp;
	diff.x = moveCoordinates[1].x - moveCoordinates[0].x;
	diff.y = moveCoordinates[1].y - moveCoordinates[0].y;
	for (auto i = 0; i < 2; i++) {
		if (connectID_[i] == ID) {
			temp = i;
			break;
		}
		if (i == 1) {
			return;
		}
	}
	coordinates_[temp].x += diff.x;
	coordinates_[temp].y += diff.y;
}

bool edge::Check(CPoint point) {
	CRect rect;
	if (coordinates_[0].x < coordinates_[1].x) {
		rect.left = coordinates_[0].x - 10;
		rect.right = coordinates_[1].x + 10;
	}
	else {
		rect.right = coordinates_[0].x + 10;
		rect.left = coordinates_[1].x - 10;
	}
	if (coordinates_[0].y < coordinates_[1].y) {
		rect.top = coordinates_[0].y - 10;
		rect.bottom = coordinates_[1].y + 10;
	}
	else {
		rect.bottom = coordinates_[0].y + 10;
		rect.top = coordinates_[1].y - 10;
	}
	if (point.x > rect.left&& point.x < rect.right && point.y > rect.top&& point.y < rect.bottom) {
		return true;
	}
	return false;
}

void edge::MakeNonOrient() {
	is_oriented_ = false;
}

void edge::MakeOrient() {
	is_oriented_ = true;
	switch (orientation_)
	{
	case Orientation::right:
		if (coordinates_[0].x < coordinates_[1].x) {
			choosenSide_[0] = 1;
			choosenSide_[1] = 0;
		}
		else {
			choosenSide_[0] = 0;
			choosenSide_[1] = 1;
		}
		break;
	case Orientation::left:
		if (coordinates_[0].x < coordinates_[1].x) {
			choosenSide_[0] = 1;
			choosenSide_[1] = 0;
		}
		else {
			choosenSide_[0] = 0;
			choosenSide_[1] = 1;
		}
		break;
	default:
		break;
	}
}

void edge::Draw(HDC dc) {
	CPen pen(type_, width_, color_);
	SelectObject(dc, pen);
	CPoint arrowPoint[4], diffrence, linePoint, TempPoint;
	double arrowSin, arrowCos, radius;
	if (is_oriented_) {

		switch (orientation_)
		{
		case Orientation::right:
			diffrence.x = coordinates_[choosenSide_[0]].x - coordinates_[choosenSide_[1]].x;
			diffrence.y = coordinates_[choosenSide_[0]].y - coordinates_[choosenSide_[1]].y;
			radius = sqrt(pow(diffrence.x, 2) + pow(diffrence.y, 2));
			arrowCos = diffrence.x / radius;
			arrowSin = diffrence.y / radius;
			radius -= 20;
			linePoint.x = coordinates_[choosenSide_[1]].x + radius;
			linePoint.y = coordinates_[choosenSide_[1]].y;
			arrowPoint[0].x = linePoint.x - 10;
			arrowPoint[0].y = linePoint.y + 10;
			arrowPoint[1].x = linePoint.x - 10;
			arrowPoint[1].y = linePoint.y - 10;
			arrowPoint[2].x = (arrowPoint[0].x - coordinates_[choosenSide_[1]].x) * arrowCos - (arrowPoint[0].y - coordinates_[choosenSide_[1]].y) * arrowSin + coordinates_[choosenSide_[1]].x;
			arrowPoint[2].y = (arrowPoint[0].y - coordinates_[choosenSide_[1]].y) * arrowCos + (arrowPoint[0].x - coordinates_[choosenSide_[1]].x) * arrowSin + coordinates_[choosenSide_[1]].y;
			arrowPoint[3].x = (arrowPoint[1].x - coordinates_[choosenSide_[1]].x) * arrowCos - (arrowPoint[1].y - coordinates_[choosenSide_[1]].y) * arrowSin + coordinates_[choosenSide_[1]].x;
			arrowPoint[3].y = (arrowPoint[1].y - coordinates_[choosenSide_[1]].y) * arrowCos + (arrowPoint[1].x - coordinates_[choosenSide_[1]].x) * arrowSin + coordinates_[choosenSide_[1]].y;
			Polygon(dc, coordinates_, 2);
			arrowPoint[0] = coordinates_[choosenSide_[0]];
			arrowPoint[1] = arrowPoint[2];
			Polyline(dc, arrowPoint, 2);
			arrowPoint[1] = arrowPoint[3];
			Polyline(dc, arrowPoint, 2);
			break;
		case Orientation::left:
			diffrence.x = coordinates_[choosenSide_[1]].x - coordinates_[choosenSide_[0]].x;
			diffrence.y = coordinates_[choosenSide_[1]].y - coordinates_[choosenSide_[0]].y;
			radius = sqrt(pow(diffrence.x, 2) + pow(diffrence.y, 2));
			arrowCos = diffrence.x / radius;
			arrowSin = diffrence.y / radius;
			radius -= 20;
			linePoint.x = coordinates_[choosenSide_[0]].x + radius;
			linePoint.y = coordinates_[choosenSide_[0]].y;
			arrowPoint[0].x = linePoint.x - 10;
			arrowPoint[0].y = linePoint.y + 10;
			arrowPoint[1].x = linePoint.x - 10;
			arrowPoint[1].y = linePoint.y - 10;
			arrowPoint[2].x = (arrowPoint[0].x - coordinates_[choosenSide_[0]].x) * arrowCos - (arrowPoint[0].y - coordinates_[choosenSide_[0]].y) * arrowSin + coordinates_[choosenSide_[0]].x;
			arrowPoint[2].y = (arrowPoint[0].y - coordinates_[choosenSide_[0]].y) * arrowCos + (arrowPoint[0].x - coordinates_[choosenSide_[0]].x) * arrowSin + coordinates_[choosenSide_[0]].y;
			arrowPoint[3].x = (arrowPoint[1].x - coordinates_[choosenSide_[0]].x) * arrowCos - (arrowPoint[1].y - coordinates_[choosenSide_[0]].y) * arrowSin + coordinates_[choosenSide_[0]].x;
			arrowPoint[3].y = (arrowPoint[1].y - coordinates_[choosenSide_[0]].y) * arrowCos + (arrowPoint[1].x - coordinates_[choosenSide_[0]].x) * arrowSin + coordinates_[choosenSide_[0]].y;
			Polyline(dc, coordinates_, 2);
			arrowPoint[0] = coordinates_[choosenSide_[1]];
			arrowPoint[1] = arrowPoint[2];
			Polyline(dc, arrowPoint, 2);
			arrowPoint[1] = arrowPoint[3];
			Polyline(dc, arrowPoint, 2);
			break;
		default:
			break;
		}
	}else {
		Polygon(dc, coordinates_, 2);
	}
	if (drawID) {
		CPoint center;
		center.x = abs(coordinates_[0].x + coordinates_[1].x)/2;
		center.y = abs(coordinates_[0].y + coordinates_[1].y) / 2;
		SetBkMode(dc, TRANSPARENT);
		CString str;
		str.Format(_T("%i"), id_);
		TextOut(dc, center.x + 10, center.y + 10, str, str.GetLength());
	}
}

void edge::Swap() {
	if (orientation_ == Orientation::right) {
		orientation_ = Orientation::left;
	}
	else {
		orientation_ = Orientation::right;
	}

}