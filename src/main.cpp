#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>      // std::setw
#include <stdlib.h>     /* srand, rand */


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Triangle.h"
#include "Vertex.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

void printTriangle(const Triangle& t)
{
	Vertex p1 = t.getV1();
	Vertex p2 = t.getV2();
	Vertex p3 = t.getV3();

	float p1x = p1.getX();
	float p1y = p1.getY();
	float p2x = p2.getX();
	float p2y = p2.getY();
	float p3x = p3.getX();
	float p3y = p3.getY();

	cout << "v1x: " << p1x << endl;
	cout << "v1y: " << p1y << endl;
	cout << "v2x: " << p2x << endl;
	cout << "v2y: " << p2y << endl;
	cout << "v3x: " << p3x << endl;
	cout << "v3y: " << p3y << endl;
}
void printTriangleWithColor(const Triangle& t)
{
	Vertex v1 = t.getV1();
	Vertex v2 = t.getV2();
	Vertex v3 = t.getV3();

	float v1x = v1.getX();
	float v1y = v1.getY();
	float v1r = v1.getR();
	float v1g = v1.getG();
	float v1b = v1.getB();
	float v2x = v2.getX();
	float v2y = v2.getY();
	float v2r = v2.getR();
	float v2g = v2.getG();
	float v2b = v2.getB();
	float v3x = v3.getX();
	float v3y = v3.getY();
	float v3r = v3.getR();
	float v3g = v3.getG();
	float v3b = v3.getB();

	/*cout << "v1x: " << p1x << endl;
	cout << "v1y: " << p1y << endl;
	cout << "v1r: " << p1r << endl;
	cout << "v1g: " << p1g << endl;
	cout << "v1b: " << p1b << endl;
	cout << "v2x: " << p2x << endl;
	cout << "v2y: " << p2y << endl;
	cout << "v2r: " << p2r << endl;
	cout << "v2g: " << p2g << endl;
	cout << "v2b: " << p2b << endl;
	cout << "v3x: " << p3x << endl;
	cout << "v3y: " << p3y << endl;
	cout << "v3r: " << p3r << endl;
	cout << "v3g: " << p3g << endl;
	cout << "v3b: " << p3b << endl;*/

	cout << "v1: ";
	cout << "{" << v1x << ", " << v1y << ", " << v1r << ", " << v1g << ", " << v1b << "}" << endl;
	cout << "v2: ";
	cout << "{" << v2x << ", " << v2y << ", " << v2r << ", " << v2g << ", " << v2b << "}" << endl;
	cout << "v3: ";
	cout << "{" << v3x << ", " << v3y << ", " << v3r << ", " << v3g << ", " << v3b << "}" << endl;
}

//given Triangle and a Vertex, determine if that Vertex is inside the Triangle
//credit to http://blackpawn.com/texts/pointinpoly/ and http://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
bool inTriangle(Triangle t, Vertex p)
{
	Vertex p1 = t.getV1();
	Vertex p2 = t.getV2();
	Vertex p3 = t.getV3();

	float px = p.getX();
	float py = p.getY();
	float p1x = p1.getX();
	float p1y = p1.getY();
	float p2x = p2.getX();
	float p2y = p2.getY();
	float p3x = p3.getX();
	float p3y = p3.getY();

	float alpha = ((p2y - p3y)*(px - p3x) + (p3x - p2x)*(py - p3y)) / ((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	float beta = ((p3y - p1y)*(px - p3x) + (p1x - p3x)*(py - p3y)) / ((p2y - p3y)*(p1x - p3x) + (p3.getX() - p2x)*(p1y - p3y));
	float gamma = 1.0 - alpha - beta;

	if (alpha > 0 && beta > 0 && gamma > 0)
	{
		//cout << "true\n";
		return true;
	}
	else
	{
		//cout << "false\n";
		return false;
	}
}

vector<float> getMeshBoundingBox(const vector<Vertex>& vs)
{
	float xmin = std::numeric_limits<float>::max();
	float ymin = std::numeric_limits<float>::max();
	float xmax = std::numeric_limits<float>::min();
	float ymax = std::numeric_limits<float>::min();
	float zmin = std::numeric_limits<float>::max();
	float zmax = std::numeric_limits<float>::min();
	for (auto it = vs.begin(); it != vs.end(); ++it)
	{
		xmin = min(xmin, it->getX());
		ymin = min(ymin, it->getY());
		xmax = max(xmax, it->getX());
		ymax = max(ymax, it->getY());
		zmin = min(zmin, it->getZ());
		zmax = max(zmax, it->getZ());
	}

	return{ xmin, ymin, xmax, ymax, zmin, zmax };
}

//find bounding box of entire mesh
vector<float> getBigBoundingBox(const vector<Triangle>& ts)
{
	vector<float> xvals;
	vector<float> yvals;

	float xmin = std::numeric_limits<float>::max();
	float ymin = std::numeric_limits<float>::max();
	float xmax = std::numeric_limits<float>::min();
	float ymax = std::numeric_limits<float>::min();


	
	//find largest/smallest x and y values
	for (auto tri_it = ts.begin(); tri_it != ts.end(); ++tri_it)
	{
		xmax = max(xmax, tri_it->getV1().getX());
		xmax = max(xmax, tri_it->getV2().getX());
		xmax = max(xmax, tri_it->getV3().getX());

		xmin = min(xmin, tri_it->getV1().getX());
		xmin = min(xmin, tri_it->getV2().getX());
		xmin = min(xmin, tri_it->getV3().getX());

		ymax = max(ymax, tri_it->getV1().getY());
		ymax = max(ymax, tri_it->getV2().getY());
		ymax = max(ymax, tri_it->getV3().getY());

		ymin = min(ymin, tri_it->getV1().getY());
		ymin = min(ymin, tri_it->getV2().getY());
		ymin = min(ymin, tri_it->getV3().getY());
	}
	return{ xmin, ymin, xmax, ymax };
}
//returns triangle with appropriate scale and translation values
Triangle worldToImage(Triangle &t, float scale, float tx, float ty)
{
	//cout << "World Triangle: \n";
	//printTriangleWithColor(t);
	Vertex v1(scale * t.getV1().getX() + tx, scale * t.getV1().getY() + ty, t.getV1().getZ(), t.getV1().getR(), t.getV1().getG(), t.getV1().getB());
	
	Vertex v2(scale * t.getV2().getX() + tx, scale * t.getV2().getY() + ty, t.getV2().getZ(), t.getV2().getR(), t.getV2().getG(), t.getV2().getB());

	Vertex v3(scale * t.getV3().getX() + tx, scale * t.getV3().getY() + ty, t.getV3().getZ(), t.getV3().getR(), t.getV3().getG(), t.getV3().getB());

	Triangle new_t = Triangle(v1, v2, v3);
	//cout << "Image Triangle: \n";
	//printTriangleWithColor(new_t);
	//cout << "\n\n";
	return new_t;
}

//returns dimensions of single triangle bounding box
//vector: {xmin, ymin, xmax, ymax}
vector<float> getBoundingBox(const Triangle& t)
{
	//cout << "Getting Bounding Box\n";
	//printTriangle(t);
	//vector<float> xvals = t.getXVals();
	vector<float> xvals;
	xvals.push_back(t.getV1().getX());
	xvals.push_back(t.getV2().getX());
	xvals.push_back(t.getV3().getX());
	//vector<float> yvals = t.getYVals();
	vector<float> yvals;
	yvals.push_back(t.getV1().getY());
	yvals.push_back(t.getV2().getY());
	yvals.push_back(t.getV3().getY());
	//vector<float> zvals = t.getZVals();
	vector<float> zvals;
	zvals.push_back(t.getV1().getZ());
	zvals.push_back(t.getV2().getZ());
	zvals.push_back(t.getV3().getZ());

	float xmin = *min_element(xvals.begin(), xvals.end());
	float ymin = *min_element(yvals.begin(), yvals.end());

	float xmax = *max_element(xvals.begin(), xvals.end());
	float ymax = *max_element(yvals.begin(), yvals.end());

	float zmin = *min_element(zvals.begin(), zvals.end());
	float zmax = *max_element(zvals.begin(), zvals.end());

	return { xmin, ymin, xmax, ymax, zmin, zmax };
}

float convertZ(float input, float zmin, float zmax)
{
	float slope = 255 / (zmax - zmin);
	float output = slope * (input - zmin);
	return output;
}

Vertex interp(Triangle t, float px, float py)
{
	Vertex p1 = t.getV1();
	Vertex p2 = t.getV2();
	Vertex p3 = t.getV3();

	float p1x = p1.getX();
	float p1y = p1.getY();

	float p2x = p2.getX();
	float p2y = p2.getY();

	float p3x = p3.getX();
	float p3y = p3.getY();

	float p1r = p1.getR();
	float p2r = p2.getR();
	float p3r = p3.getR();
	float p1g = p1.getG();
	float p2g = p2.getG();
	float p3g = p3.getG();
	float p1b = p1.getB();
	float p2b = p2.getB();
	float p3b = p3.getB();

	float p1z = p1.getZ();
	float p2z = p2.getZ();
	float p3z = p3.getZ();

	float alpha = ((p2y - p3y)*(px - p3x) + (p3x - p2x)*(py - p3y)) / ((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	float beta = ((p3y - p1y)*(px - p3x) + (p1x - p3x)*(py - p3y)) / ((p2y - p3y)*(p1x - p3x) + (p3.getX() - p2x)*(p1y - p3y));
	float gamma = 1.0 - alpha - beta;

	float red = p1r*alpha + p2r*beta + p3r*gamma;
	float green = p1g*alpha + p2g*beta + p3g*gamma;
	float blue = p1b*alpha + p2b*beta + p3b*gamma;

	float z = p1z*alpha + p2z*beta + p3z*gamma;



	return Vertex(px, py, z, red, blue, green);

}
int main(int argc, char **argv)
{
	srand(time(NULL));
	if(argc < 6) {
		cout << "Usage: A1 meshfile filename width heigh mode" << endl;
		return 0;
	}
	string meshName(argv[1]);
	string filename(argv[2]);
	cout << meshName << endl;

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	//get triangles
	vector<Triangle> triangles;
	vector<Vertex> verts;
	int i = 1;
	for (auto it = posBuf.begin(); it != posBuf.end(); ++it)
	{
		if (i % 3 == 0) // we have 3 floats, make a vertex
		{
			//if (atoi(argv[5]) == 0)
			//{
				verts.push_back(Vertex(*(it - 2), *(it - 1), *it, rand() % 256, rand() % 256, rand() % 256));
			//}
			//else if (atoi(argv[5]) == 1)
			//{
			//	verts.push_back(Vertex(*(it - 2), *(it - 1), *it, *it, 0, 0));
			//}
			
		}
		++i;
	}
	if (verts.size() % 3 == 0 && verts.size() > 0)
	{
		auto it = verts.begin();
		while (it != verts.end())
		{
			Vertex a = *it;
			++it;
			Vertex b = *it;
			++it;
			Vertex c = *it;
			++it;
			triangles.push_back(Triangle(a, b, c));
		}
	}
	else
	{
		cerr << "invalid obj file\n";
		return 1;
	}

	vector<float> bounding_box = getMeshBoundingBox(verts); //bounding box for entire mesh
	//{xmin, ymin,
	float xmin = bounding_box[0];
	float ymin = bounding_box[1];
	float xmax = bounding_box[2];
	float ymax = bounding_box[3];
	float zmin = bounding_box[4];
	float zmax = bounding_box[5];
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	


	//cout << "width = " << width << endl;
	//cout << "height = " << height << endl;
	//cout << "xmin = " << xmin << endl;
	//cout << "ymin = " << ymin << endl;
	//cout << "xmax = " << xmax << endl;
	//cout << "ymax = " << ymax << endl;

	//find scale
	float scale;
	if (((ymax - ymin) /height) > ((xmax - xmin)/width)) //height is limiting
	{
		//cout << "height is limiting\n";
		scale = (float)(height) / (float)(ymax - ymin);

	}
		
	else //width is limiting or dimensions are equal
	{
		//cout << "width is limiting or dimensions are equal\n";
		scale = (float)(width) / (float)(xmax - xmin);
	}
		
	//cout << "scale = " << scale << endl;
	
	//find translation
	float midxw = 0.5*(xmin + xmax); //middle of world
	float midyw = 0.5*(ymin + ymax);
	float tx = (width / 2) - (scale*midxw); //x translation
	float ty = (height / 2) - (scale*midyw); //y translation
	/*if (tx < 0 || ty < 0)
	{
		cerr << "invalid translation\n";
		cerr << "tx = " << tx << endl;
		cerr << "ty = " << ty << endl;

		return 1;
	}*/
	//cout << "tx = " << tx << endl;
	//cout << "ty = " << ty << endl;
	vector<Triangle> img_triangles;
	for (auto it = triangles.begin(); it != triangles.end(); ++it)
	{
		Triangle t = worldToImage(*it, scale, tx, ty);
		img_triangles.push_back(t);
	}

	auto image = make_shared<Image>(width, height);
	vector<vector<float>> zbuf(width, vector<float>(height, numeric_limits<float>::min()));

	for (auto it = img_triangles.begin(); it != img_triangles.end(); ++it)
	{
		//printTriangle(*it);




		vector<float> bb = getBoundingBox(*it);
		float _xmin = bb[0];
		float _ymin = bb[1];
		float _xmax = bb[2];
		float _ymax = bb[3];
		//cout << "triangle bb xmin = " << _xmin << endl;
		//cout << "triangle bb ymin = " << _ymin << endl;
		//cout << "triangle bb xmax = " << _xmax << endl;
		//cout << "triangle bb ymax = " << _ymax << endl;
		for (int y = _ymin; y <= _ymax; ++y) {
			for (int x = _xmin; x <= _xmax; ++x) {
				Vertex v = Vertex(x, y, 0, 0, 0, 0);
				if (inTriangle(*it, v))
				{
					Vertex pixel = interp(*it, x,y);
					/*cout << "pixel x = " << pixel.getX() << endl;
					cout << "pixel y = " << pixel.getY() << endl;
					cout << "pixel z = " << pixel.getZ() << endl;
					cout << "pixel r = " << pixel.getR() << endl;
					cout << "pixel g = " << pixel.getG() << endl;
					cout << "pixel b = " << pixel.getB() << endl;*/

					if (pixel.getZ() > zbuf[x][y])
					{
						zbuf[x][y] = pixel.getZ();
						float zcolor = convertZ(pixel.getZ(), zmin, zmax);
						float ycolor = convertZ(pixel.getY(), ymin*scale + ty, ymax*scale + ty);
						if (atoi(argv[5]) == 0)
						{
							image->setPixel(pixel.getX(), pixel.getY(), pixel.getR(), pixel.getG(), pixel.getB());
						}
						else if (atoi(argv[5]) == 1)
						{
							image->setPixel(pixel.getX(), pixel.getY(), zcolor, 0, 0);
						}
						else if (atoi(argv[5]) == 2)
						{
							image->setPixel(pixel.getX(), pixel.getY(), ycolor, 255-ycolor, 0);
						}
					}
					
				}
				
			}
		}
	}
	image->writeToFile(filename);
	return 0;
}
