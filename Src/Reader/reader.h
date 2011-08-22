#ifndef _READER_H_
#define _READER_H_

#include <string>
#include <vector>
#include <fstream>

#include "structure.h"
#include "substructure.h"
#include "framebvh.h"
#include "pose.h"

class Reader
{
	// Class is made to read a bvh file.

private:

	// Listed below are the variables used by this class. These variables encode all important information related to the Reader
    // Notes regarding variables used.
    // 1-  myInputStream is a stream to read the input file
    // 2-  myOutputStream is a stream to write the output file containing unique poses
	// 3-  currentLine is used to store the line that has just been read by the input stream
	// 4-  numberOfJoints indicates the total number of joints read in the Heirarchy Section of the file
	// 5-  currentJoint refers to the current Joint being processed, it is used in establishing the parent joint
	// 6-  totalFrames is the total number of frames read from the motion section
	// 7-  frameRate defines the number of Frames that are to be showin in one second when viewing the file
	// 7-  myStructure is the structure object that is created after the 'Heirarchy' section has been read
	// 8-  myFrames is a vector containing all the frames from the 'Motion' section of the file
	// 9-  motionLines contains all the strings defining the frames
	// 10- uinquePoses are the structures that have greater then 5cm separation for at least one joint.


	std::ifstream myInputStream;
	std::ofstream myOutputStream;

	std::string currentLine;

    int numberOfJoints;
    int currentJoint;
	int totalFrames;
	float frameRate;

	Structure myStructure;
    std::vector<FrameBVH> myFrames;

	std::vector<std::string> motionLines;
	std::vector<Structure> uniquePoses;

    // Internal Parsing Functions
	// Used in reading file

    // For reading Heirarchy Section
	void getObjectStructure();
    bool parseLineStructure();
    SubStructure getSubStructure(std::string jointName);
    std::vector<float> readOffsets();

    // For reading Motion Section
    void getMotion();
	bool parseLineMotion();
    void addAllFrames();
    void readForFrame();

    // For unique pose identification
	bool comparePoses(Structure testPose, Structure existingPose);

public:

    // Constructor
	Reader(std::string filePath,std::string realName);        // Constructor for Reader

	// Destructor
	~Reader();

	// ACCESSORS
    Structure getStructure();
   	int getTotalFrames();
    float getFrameRate();
	FrameBVH getFrame(int frameNumber);

    // IMPORTANT FUNCTIONS
    void readFile();                     // initiates the reading of a File
    void uniquePoseIdentification();
};
#endif
