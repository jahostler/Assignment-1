#pragma once
#include "Vertex.h"
#include <vector>


class Triangle 
{
public:
	Triangle(Vertex a, Vertex b, Vertex c);
	void setV1(const Vertex &v) { v1 = v; }
	void setV2(const Vertex &v) { v2 = v; }
	void setV3(const Vertex &v) { v3 = v; }
	Vertex getV1() const { return v1; }
	Vertex getV2() const { return v2; }
	Vertex getV3() const { return v3; }
	std::vector<float> getXVals() const { return xvalues; }
	std::vector<float> getYVals() const { return yvalues; }
	std::vector<float> getZVals() const { return zvalues; }
private:
	Vertex v1;
	Vertex v2;
	Vertex v3;
	std::vector<float> xvalues;
	std::vector<float> yvalues;
	std::vector<float> zvalues;
};