
#include "Vertex.h"

Vertex::Vertex(float xx, float yy, float zz, float rr, float gg, float bb) : x(xx), y(yy), z(zz), r(rr), g(gg), b(bb) {}
Vertex::Vertex(const Vertex& vv) : x(vv.x), y(vv.y), z(vv.z), r(vv.r), g(vv.g), b(vv.b) {}
Vertex::Vertex()
{

}
