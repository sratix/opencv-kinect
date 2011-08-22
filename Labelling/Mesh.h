#ifndef _MESH_H
#define _MESH_H

#include <string>
#include <fstream>
#include <vector>
#include "SimpleReader.h"
#include "SimpleWriter.h"
#include "BodyPart.h"
#include <math.h>
#include <cstdlib>


class Mesh
{
	// This class is intended to serve as a representative of a mesh in a particular pose
	// Contains all mesh attributes
	
	
	private:
		// Variables in this class are
		// 1- numberOfVertices denotes the number of vertices in the complete mesh
		// 2- numberOfFaces denotes the number of Faces in the mesh rendering
		// 3- initializer is a file reader for simple files made using the provided python scripts
		// 4- finalizer is a file writer for simple files of the form made by the provided python scripts
		// 5- pathCoordinatesFile is the name and the path of the file containing the coordinates for the mesh, it has the extension .coords
		// 6- pathLabelsFile is the name and the path of the file containing the labels for the vertices of the mesh, it has the extension .labels
		// 7- pathFacesFile is the name and the path of the file containing the faces that make up the mesh, it has the extension .faces
		// 8- verticeCoordinates contains the coordinates for the all the vertices of the mesh.
		// 9- faces contains the details of all the faces that make up a character
		// 10- verticeLabels contains the labels corresponding to each coordinate which denote which part it belongs to
		// 11- completeMeanX is the mean for all the X coordinates of the Mesh
		// 12- completeMeanY is the mean for all the Y coordinates of the Mesh
		// 13- completeMeanZ is the mean for all the Z coordinates of the Mesh
		// 14- theBody is a grouped definition of all the components of the Body
		// It describes the association of the vertices to BodyParts
		
		int numberOfVertices;
		int numberOfFaces;
		
		SimpleReader initializer;
		SimpleWriter finalizer;
		
		std::string pathCoordinatesFile;
		std::string pathLabelsFile;
		std::string pathFacesFile;
		
		std::vector< std::vector<float> > verticeCoordinates;
		std::vector< std::vector<int> > faces;
		std::vector< std::string > verticeLabels;
		
		float completeMeanX;
		float completeMeanY;
		float completeMeanZ;
		
		std::vector<BodyPart> theBody;
		
		void formBodyParts();
		
		int findBodyPart(std::string partName,std::vector<BodyPart> aBody);
		int getLocalPart(std::string partName);
		
		
	
	public:
	
		// Constructors
		Mesh();
		Mesh(std::string pathCoordinates, std::string pathFaces, std::string pathLabels);
		
		// Destructors
		~Mesh();

		
		// Loading Function
		void loadMesh(std::string pathCoordinates, std::string pathFaces, std::string pathLabels);
		void loadCoordinates(std::string pathCoordinates);		
		void loadFaces(std::string pathFaces);
		
		// Key Functions 
		
		// Reduction for Number of Groups Body is Divided into
		void remapMesh(std::string pathMapping);
		
		// Printing Function
		void print();
		
		// Fix a badly labelled joint
		void fixJoint(std::string jointName, std::string jointAxis);
		
		// Add a joint between two other joints
		void addJoint(std::string jointAboveName,std::string jointBelowName, float weightage,std::string axis);
		
		// Accesssors
		int getChoice(std::string axis);		
		float getMean(std::string axis);		
		std::vector<BodyPart> getBody();
		std::vector<std::string> getPaths();		
		std::vector<std::string> getLabels();
		std::vector< std::vector<int> > getFaces();				
		std::vector< std::vector<float> > getCoordinates();
		
		// Internal Function for aligning two meshes
		void meanSubtractCoordinates();
		
		// Loading labels from external mesh
		void loadLabels(std::vector< std::vector<float> > externalMeshCoordinates, std::vector<std::string> externalMeshLabels);
		
		// Compute distance between two points		
		float computeDistance(std::vector< float> coordinateA, std::vector< float> coordinateB);
		
		// Function for updating mesh labels called after modifying labels from the parts in the body.
		void updateMeshLabels();
		
		// make a functioin for rendering the data
		
		// make function for rendering a z buffer representation
		
};
#endif 