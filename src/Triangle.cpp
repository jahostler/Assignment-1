

#include "Triangle.h"

Triangle::Triangle(Vertex a, Vertex b, Vertex c) 
{
	v1 = a;
	v2 = b;
	v3 = c;
	std::vector<float> x;
	x.push_back(a.getX());
	x.push_back(b.getX());
	x.push_back(c.getX());
	xvalues = x;
	std::vector<float> y;
	y.push_back(v1.getY());
	y.push_back(v2.getY());
	y.push_back(v3.getY());
	yvalues = y;
	std::vector<float> z;
	z.push_back(v1.getZ());
	z.push_back(v2.getZ());
	z.push_back(v3.getZ());
	zvalues = z;
}