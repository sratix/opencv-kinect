#ifndef _SUBSTRUCTURE_H_
#define _SUBSTRUCTURE_H_
// Nothing to be done for this file. 

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class SubStructure
{
    // Class is made to store the joint information.
    // One may augment the class with additional information such as Bone Density, Bone Shape, Bone Length
    // Also when we integrate with PCL (Point Cloud Library), we may begin offering 3D visualization of the bones.

private:

    // Listed below are the variables used by this class. These variables encode all important information related to the joint.
    // Notes regarding variables used.
    // 1- name contains the name of the joint specified in the BVH file.
    // 2- offsetCoordinates contain variables stored in the following order X,Y,Z
    // 3- endsiteCoordinates contain variables stored in the following order X,Y,Z
    // 4- numberOfChannels corresponds to the amount of data given in each frame for this joint.
    // 5- parentIndex is the index of the parent SubStructure in the Structure array.

	std::string name;

	std::vector<float> offsetCoordinates;
	std::vector<float> endsiteCoordinates;

	int numberOfChannels;   // this represents the information provided about this SubStructure in the Motion Section
                            // 3 number of channels indicate that each frame will contain 3 variables that contain information regarding this joint
	int indexParent;

public:

    // Constructors
	SubStructure();
	SubStructure(std::string sName,std::vector<float> userOffsetCoordinates,std::vector<float> userEndsiteCoordinates,int sNumberOfChannels,int sIndexParent);

	// Destructor
    ~SubStructure();

    // Diplay
	void print();
	void printToFile(std::ofstream& outputStream);

    // Mutators
	void setName(std::string userName);
	void setOffset(std::vector<float> theOffset);
	void setEndPoints(std::vector<float> userEndsiteCoordinates);
	void setNumberOfChannels(int userNumberOfChannels);
	void setParentIndex(int theParentIndex);

    // Accessors
    std::string getName();
	std::vector<float> getOffset();
	std::vector<float> getEndsiteCoordinates();
	int getParentIndex();
	int getNumberOfChannels();

};

#endif
