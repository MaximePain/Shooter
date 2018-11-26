#pragma once
class MathsMax
{
public:
	MathsMax();



	~MathsMax();
};

struct Point {
	double X;
	double Y;

	Point(double x, double y) {
		X = x;
		Y = y;
	}
};

bool PointInParal() {
	return false;
}


bool PointInTriangle(Point A, Point B, Point C, Point P) {
	double s1 = C.Y - A.Y;
	double s2 = C.X - A.X;
	double s3 = B.Y - A.Y;
	double s4 = P.Y - A.Y;

	double w1 = (A.X * s1 + s4 * s2 - P.X * s1) / (s3 * s2 - (B.X - A.X) * s1);
	double w2 = (s4 - w1 * s3) / s1;
	return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}


