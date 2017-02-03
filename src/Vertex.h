#pragma once

class Vertex
{
public:
	Vertex(float xx, float yy, float zz, float rr, float gg, float bb);
	Vertex(const Vertex& vv);
	Vertex();
	void setX(float i) { x = i; }
	void setY(float i) { y = i; }
	void setR(float i) { r = i; }
	void setG(float i) { g = i; }
	void setB(float i) { b = i; }
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getR() const { return r; }
	float getG() const { return g; }
	float getB() const { return b; }
	
private:
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};