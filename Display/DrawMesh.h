#ifndef _DRAWMESH_H
#define _DRAWMESH_H

#include <vector>
#include <string>

// Including the GLUT Dependencies
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class DrawMesh
{
	private:		
		std::vector<std::vector<float> > theCoordinates;
		std::vector<std::vector<int> > theFaces;
		std::vector<std::string> theLabels;
		
		std::vector<std::string> theLabelling;
		
		int numberOfVertices;
		int numberOfFaces;
		
		// Internal Rendering Function
		std::vector<std::vector<float> > makeColors();
		int findLabelling(std::string aLabel);
		
	public:
		// Constructors
		DrawMesh();
	
		// Mutators
		void setAllData(std::vector<std::vector<float> > aCoordinates,std::vector<std::vector<int> > aFaces,std::vector<std::string> aLabels);		
		void setCoordinates(std::vector<std::vector<float> > aCoordinates);
		
		
		

		
		
		

};
#endif
