#include "pose.h"

// Default constructor contains no initialization
Pose::Pose()
{
    //
}

// Default Destructor contains no actions
Pose::~Pose()
{
    //
}

// Function designed to take an existing structure and its associated BVH File Frame
// FrameBVH variable must have the same number of channels as the total number Of Channels in the Structure
// Function will not tamper with the orignal Structure
Structure Pose::adoptPose(Structure myStructure,FrameBVH specifications)
{
    // Creating a new empty Structure
    Structure baseStructure;
   

	for (int joint=0;joint<myStructure.getTotalParts();joint++)
	{
	    // obtaining the joint offsets
		std::vector<float> jointOffset = myStructure.getSubStrcutureOffset(joint);
		// Creating a matrix to store the coordinates of the offset from the parent joint               
		cv::Mat jointCoordinate(3,1,CV_32FC1); 
		jointCoordinate.at<float>(0,0)=jointOffset[0];
		jointCoordinate.at<float>(0,1)=jointOffset[1];
		jointCoordinate.at<float>(0,2)=jointOffset[2];		

        // Creating a matrix to represt the joint rotation transform
        cv::Mat temporaryMatrix = getRotationTransform(specifications.getRotationDetails(joint));
		
		
        // multiplying Rotation Transform with the coordinates to obtain new coordinates		
		temporaryMatrix = temporaryMatrix*jointCoordinate;	
        // entering the new coordinates in a vector
		
		std::vector<float> newJointOffset;
		newJointOffset.push_back(temporaryMatrix.at<float>(0,0));
		newJointOffset.push_back(temporaryMatrix.at<float>(1,0));
		newJointOffset.push_back(temporaryMatrix.at<float>(2,0));

        // setting empty userEndsite Coordinates
        std::vector<float> userEndsiteCoordinates;
        userEndsiteCoordinates.push_back(0);
        userEndsiteCoordinates.push_back(0);
        userEndsiteCoordinates.push_back(0);

        // using most information regarding the joint from a parent joint and
		SubStructure aSubtStructure(myStructure.getPartName(joint),newJointOffset,userEndsiteCoordinates,3,myStructure.getParentJointIndex(joint));
		// adding the joint with the new coordinates to the new structure
		baseStructure.addSubStructure(aSubtStructure);
	
	}

	return baseStructure;
}

// Function made for obtaining the rotation transform
// Input must be a three sized vector
// Incase of incomplete rotations zeros will be assumed for remaining and rotations provided will be considered in the order Z,Y,X
// Rotation angles must be in degrees as conversion is done within to radians
cv::Mat Pose::getRotationTransform(std::vector<float> rotations)
{
	
	// the Z Rotation	
	rotations[0] = rotations[0]*PI/180;
	// the Y Rotation	
	rotations[1] = rotations[1]*PI/180;
	// the X Rotation
	rotations[2] = rotations[2]*PI/180;
	
	
	cv::Mat xRotation = cv::Mat(3, 3, CV_32FC1);
	xRotation.at<float>(0,0) = 1;
	xRotation.at<float>(0,1) = 0;
	xRotation.at<float>(0,2) = 0;
		
	xRotation.at<float>(1,0) = 0;
	xRotation.at<float>(1,1) = cos(rotations[2]);
	xRotation.at<float>(1,2) = -sin(rotations[2]);
		
	xRotation.at<float>(2,0) = 0;
	xRotation.at<float>(2,1) = sin(rotations[2]);
	xRotation.at<float>(2,2) = cos(rotations[2]);		
	
	cv::Mat yRotation = cv::Mat(3, 3, CV_32FC1);
	yRotation.at<float>(0,0) = cos(rotations[1]);
	yRotation.at<float>(0,1) = 0;
	yRotation.at<float>(0,2) = sin(rotations[1]);
		
	yRotation.at<float>(1,0) = 0;
	yRotation.at<float>(1,1) = 1;
	yRotation.at<float>(1,2) = 0;
		
	yRotation.at<float>(2,0) = -sin(rotations[1]);
	yRotation.at<float>(2,1) = 0;
	yRotation.at<float>(2,2) = cos(rotations[1]);
	
	
	    
	cv::Mat zRotation = cv::Mat(3, 3, CV_32FC1);
	zRotation.at<float>(0,0) = cos(rotations[0]);
	zRotation.at<float>(0,1) = -sin(rotations[0]);
	zRotation.at<float>(0,2) = 0;
		
	zRotation.at<float>(1,0) = sin(rotations[0]);
	zRotation.at<float>(1,1) = cos(rotations[0]);
	zRotation.at<float>(1,2) = 0;
		
	zRotation.at<float>(2,0) = 0;
	zRotation.at<float>(2,1) = 0;
	zRotation.at<float>(2,2) = 1;
		
	// Multiplication Order is Y*(X*Z)
    xRotation = xRotation*zRotation;
	
	yRotation = yRotation*xRotation;

		
	return yRotation;

}
