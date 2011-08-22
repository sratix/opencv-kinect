#ifndef _BODYPART_H
#define _BODYPART_H

#include <string>
#include <vector>
#include <iostream>


class BodyPart
{
	// Class Created to represent the Mesh for a Body Part
	// Contains detailed Mesh Description
	// Seems to have potential for use in a lot of studying of Poses
	private:
		// Class contains Variables
		// 1- numberOfVertices refers to the total number of Vertices in this body part
		// 2- name is . umm, well, the name.
		// 3- minX is the minimum Vertice Coordinate along the X Axis
		// 4- maxX is the maximum Vertice Coordinate along the X Axis
		// 5- minY is the minimum Vertice Coordinate along the Y Axis
		// 6- maxY is the maximum Vertice Coordinate along the Y Axis
		// 7- minZ is the minimum Vertice Coordinate along the Z Axis
		// 8- maxZ is the maximum Vertice Coordinate along the Z Axis
		// 9- meanX represents the mean of all the X Coordinates
		// 10- meanY represents the mean of all the Y Coordinates
		// 11- meanZ represents the mean of all the Z Coordinates
		// 12- verticeCoordinates contains coordinates of all the vertices representing the body part in the order X Y Z
		// 13- verticesIndex contains the global index for the coordinates of the vertices in the mesh
		
		int numberOfVertices;		
		std::string name;
		
		float minX;
		float maxX;
		
		float minY;
		float maxY;
		
		float minZ;
		float maxZ;
		
		float meanX;
		float meanY;
		float meanZ;
		
		std::vector< std::vector<float> > verticeCoordinates;		
		std::vector< int > verticesIndex;
		
		// Internal Updating Function
		void updateAttributes();
	
	public:
		// Constructor
		BodyPart(std::string partName);
		
		// Destructor
		~BodyPart();
		
		// Function for inserting coordinate
		void insertPoint(std::vector<float> pointCoordinates, int index);
		
		// Function for Removing Point
		void removePoint(int index);
		
		// Function for Divison of a Part
		std::vector<BodyPart> dividePart(std::string alongAxis);
		
		
		// Accessors		
		std::string getName();
		std::string getMajorAxis();		
		int getNumberOfVertices();
		int getVertexIndex(int coordinateNumber);
		float getMin(std::string axis);
		float getMax(std::string axis);
		std::vector<float> getCoordinate(int coordinateNumber);
		
		// Mutator		
		void setName(std::string newName);

		
};
#endif 