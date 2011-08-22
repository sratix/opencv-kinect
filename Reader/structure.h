#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "substructure.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>


class Structure
{
    // Class is made to store a single Structure.
    // One may augment the class with additional functions that can be performed on the structure

private:
    // Listed below are the variables used by this class. These variables encode all important information related to the Structure
    // Notes regarding variables used.
    // 1- part is an array of type 'SubStructure' which is used to store all joints of the Structure being defined in the BVH
    // 2- totalParts is used to store the total amount of parts that are present in the Structure once the file has been read

    std::vector<SubStructure> part;
	int totalParts;

    // Functions used for class implementation, but not needed for Structure as an object per say
	std::vector<float> addCoordinates(std::vector<float> coordinatesOne,std::vector<float> coordinatesTwo);
    std::vector<float> getVisualizationCoordinates(int joint);

public:

    // Constructor
	Structure();

	// Destructor
	~Structure();

    // Display to console
    void print();
	void printToFile(std::string fileName);

    // To augment the Structure with a new component related to the current structure
    void addSubStructure(SubStructure aSubStructure);

    // An image based visualization of the Structure, can be improved in subsequent release to be a camera view
	cv::Mat visualizeStructure();

	// A function to check if a joint is the End Joint in a Structure or not
	bool checkForEndJoint(int currentJoint);

    // Accessors
	std::string getPartName(int joint);
	int getParentJointIndex(int joint);
    std::vector<float> getSubStrcutureOffset(int joint);
	int getTotalNumberOfChannels();
    int getTotalParts();

    // Accessors for complete structure Data
    float getMinCoordinate(std::string term);
    float getMaxCoordinate(std::string term);


    // Mutators
	void setParent(int joint,int parentIndex);
	void setOffset(int joint,std::vector<float> offset);
	void setEndPoints(int partNumber,std::vector<float> userEndsiteCoordinates);

};

#endif
