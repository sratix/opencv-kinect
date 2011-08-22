#ifndef _SIMPLEREADER_H
#define _SIMPLEREADER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

class SimpleReader
{
	// This class was created with the objective of performing File Reading operations on very simple files written by the python scripts.
	// Also this class aims to assist the other pieces of code by reducing time by grouping together some key operations.
	// Please use the following Procedure for Reading
	// 1- Read Coordinates File First
	// 2- Read Labels File
	// 3- Read Faces File
	
	// Possible to add Creation of Vector<BodyPart> In Labelling Code to remove redundancy
	
	private:
	
	// This class makes use of the following variables:
	// 1- aFileReader is the stream that is used to connect to any file to read it.
	// 2- completeMeanX is the mean value of the X coordinates for all mesh vertices
	// 3- completeMeanY is the mean value of the Y coordinates for all mesh vertices
	// 4- completeMeanZ is the mean value of the Z coordinates for all mesh vertices
	
		std::ifstream aFileReader;

		float completeMeanX;
		float completeMeanY;
		float completeMeanZ;
		
		int numberOfVertices;
			
	public:
	
		// Constructor
		SimpleReader();
		
		//Destructor
		~SimpleReader();
		
		// Reading Functions
		std::vector< std::vector<float> > readCoordinates(std::string filePath);
		
		std::vector< std::vector<int> > readFaces(std::string filePath);
		
		std::vector< std::string > readLabels (std::string filePath);
		std::vector< std::vector<std::string> > readMapping(std::string filePath);
		
		// Obtainin Mean for Coordinates
		std::vector<float> getMean();
		
};
#endif 