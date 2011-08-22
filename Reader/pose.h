#ifndef _POSE_H_
#define _POSE_H_


#define PI 3.14159265

#include <vector>
#include <cv.h>
#include <highgui.h>

#include "structure.h"
#include "framebvh.h"



class Pose
{
    // Class is made to reflect a 'Pose'
    // No internal Variables were used however this class was deemed important in the design
    // Future expansions for this class may require creating additional variables

private:

    // Internal Function used in creating rotation matrices on being given data in Angles
	//CvMat* getRotataionMatrix(vector<float> rotataions);
	cv::Mat getRotationTransform(std::vector<float> rotations);

public:
    // Constructor
	Pose();
	// Destructor
	~Pose();

    // Important Function used in adopting a Structure to a Pose
	//Structure adoptPose(Structure myStructure,FrameBVH specifications);
	Structure adoptPose(Structure myStructure,FrameBVH specifications);
};
#endif
