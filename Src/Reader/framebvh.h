#ifndef _FRAMEBVH_H_
#define _FRAMEBVH_H_

#include <vector>
#include <string>
#include <iostream>

class FrameBVH
{
    // This class is created to store a FrameBVH from a .bvh file

private:

    // Listed below are the variables used by this class. These variables encode all important information related to the FrameBVH.
    // Notes regarding variables used.
    // 1- rotations contains the angles for the rotation matrices in the order X Y and Z
    // 2- translationRoot contains the translation data for the entire structure
    // 3- totalChannels contain the total number of Channels the motion data must have for the FrameBVH to be valid
    // 4- totalJoints stores the total number of joints that are expected to prevent redundant computations

	std::vector< std::vector<float> > rotations;
	std::vector<float> translationRoot;

    // totalChannels and total Joints are used for keeping integrity of FrameBVH data
	int totalChannels;
	int totalJoints;

public:
    // Constructor
    FrameBVH();
	FrameBVH(int numberOfChannels);

	// Destructor
	~FrameBVH();

    // Display
	void print();

    // Mutators
	void setRotation(std::vector<float> theRotations);
	void setTranslation(std::vector<float> theTranslation);

    // Accessors
	std::vector<float> getRotationDetails(int joint);
	std::vector<float> getTranslationDetails();
};
#endif

