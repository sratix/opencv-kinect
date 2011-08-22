#include "framebvh.h"

// Default constructor for the class.
// Everything is set to null or default value
// You must change the number of channels before you add rotations
FrameBVH::FrameBVH()
{
    totalChannels = 0;
    totalJoints = 0;
}

// User defined constructor for the class
// User has to specify the total number of Channels.
// In case of reading a bvh with this reader these can be obtained by 'getTotalChannels()' function of Structure class
FrameBVH::FrameBVH(int numberOfChannels)
{
    if ( ( numberOfChannels > 0 ) && ( ( numberOfChannels % 3 ) == 0 ) )
    {
        totalChannels = numberOfChannels;
        totalJoints = (numberOfChannels-3)/3;   // translations are stored separately hence the -3 term
    }
    else
    {
        std::cout<<"Error: Invalid Number Of Channels Entered\nFrame Data Set to Default\n";
        totalChannels = 0;
        totalJoints = 0;
    }

}

// Standard destructor for the class
// Clears all vectors.
// Clears vector within vector and then Clears vector
FrameBVH::~FrameBVH()
{

    for (int removeRotation=0; removeRotation<totalJoints;removeRotation++)
    {
        rotations[removeRotation].clear();
    }
    rotations.clear();
}

// Display function for the class data
// Prints all attribute values to the console
void FrameBVH::print()
{

	std::cout<<"Translation For Structure :"<<std::endl;
	std::cout<<"X : "<<translationRoot[0]<<std::endl;
	std::cout<<"Y : "<<translationRoot[1]<<std::endl;
	std::cout<<"Z : "<<translationRoot[2]<<std::endl<<std::endl;

	std::cout<<"Rotataions For Structure : \n";

	for (int loopJoint=0;loopJoint<totalJoints;loopJoint++)
	{
		std::cout<<loopJoint << " : "<<rotations[loopJoint][0]<<"  "<<rotations[loopJoint][1]<<"  "<<rotations[loopJoint][2]<<std::endl;
	}
	std::cout<<std::endl;
}

// Mutator for specifying the rotation for a particular joint
// No default value
// Only works under the assumption that the joint rotations are input in the correct order
// Rotation angles must be stored in radians
void FrameBVH::setRotation(std::vector<float> theRotations)
{
    bool allowed = ( rotations.size() < totalJoints );

    if (allowed)
    {
        int position = rotations.size();       // computing the correct position where the code must be modified

        rotations.push_back(std::vector<float>());
        rotations[position].push_back(theRotations[0]);
        rotations[position].push_back(theRotations[1]);
        rotations[position].push_back(theRotations[2]);
    }

}

// Mutator for specifying the rotation for a particular joint
// No default value
void FrameBVH::setTranslation(std::vector<float> theTranslation)
{
	translationRoot = theTranslation;
}



// Accessor for obtaining rotation angles for a particular joint
// Joint value must be greater then zero and less then the 'totalJoints' variable of this class
std::vector<float> FrameBVH::getRotationDetails(int joint)
{
    std::vector<float> myRotations;

    if ( ( joint >= 0 ) && ( joint <= totalJoints ) )
    {
        myRotations.push_back(rotations[joint][0]);
        myRotations.push_back(rotations[joint][1]);
        myRotations.push_back(rotations[joint][2]);
    }
    else
    {
        std::cout<<"Invalid Joint Specified\n";
        myRotations.push_back(0);
        myRotations.push_back(0);
        myRotations.push_back(0);
    }

	return myRotations;
}

// Accessor for obtaining translation values of the root
std::vector<float> FrameBVH::getTranslationDetails()
{
	return translationRoot;
}
