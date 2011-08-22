#include "reader.h"

// Constructor for the File Name
// The Variable filePath is the complete path to the file
// The Variable fileName is the name of the file
// Sets the default values for the Reader Variables
Reader::Reader(std::string filePath,std::string realName)
{

    // opening a ifstream to the file specified
	myInputStream.open(filePath.c_str());

    // in case of an error exit the program as none of the functions will work
	if (myInputStream.fail())
	{
	    std::cout<<"Error in Opening File\nPlease check File Path\n";
	    exit(0);
	}
    // opening a stream to the output file
	myOutputStream.open(("Unique_"+realName).c_str());

    frameRate = 0;
	numberOfJoints = 0;
	totalFrames = 0;
	currentJoint = -1;
}

// Standard Destructor for the Reader Class
// Empties all vectors
Reader::~Reader()
{
    uniquePoses.clear();
    myFrames.clear();
    
	// Cannot delete a non-class type vector like this
	//motionLines.clear();

}

// Internal Parsing function responsible for Reading the entire Heirarchy Section of the file
// Is called first when the 'readFile' function is called
// Begins on reading the term 'ROOT'
// Also outputs the Heirarchy Section to the output File as it reads it
void Reader::getObjectStructure()
{
	// variable declared to decide when the Heirarchy Section of the file has been finished
	bool continueLoop = false;

	do
	{
		// obtaining a line from the Heirarchy Sequence
		std::getline(myInputStream,currentLine);

		// Printing the output for the Structure
		myOutputStream<<currentLine<<std::endl;

		// parse line for keyWords and process accordingly
		// when the Motion Keyword is found returns false
		continueLoop = parseLineStructure();

	}while(continueLoop);

	std::cout<<"Object Structure Successfully Obtained\n";

}


// Internal parsing function responsible for Parsing any line from the heirarchy Section
bool Reader::parseLineStructure()
{
	// default answer for determining whether the 'currentLine' variable is pointing to a line from the heirarchy section
	bool answer = true;

	// the positions for the key terms that are needed for parsing a line
	// Imporant Note: the '{' symbol when encountered is just directly entered to the output file and is not used in making some sort of a decision

	// the root is the origin of the structure
	// if this is greater then or equal to 0 we will begin our search for the root joint in the subsequent lines
	int foundRoot = int(currentLine.find("ROOT"));

	// the joint will indicate a joint(bone) for the structure
	// if this is greater then or equal to 0 we will begin our search for the a joint in the subsequent lines
	int foundJoint = int(currentLine.find("JOINT"));

	// retreat refers to the fact that we are now going back towards the parent of a joint
	// if this is greater then or equal to 0 we will shift our 'currentJoint' variable to the parent of the joint being considered
	int foundRetreat = int(currentLine.find("}"));

	// endsite is the last joint in a chaing of joints
	// if this is greater then or equal to 0 we will begin our search for locating the endsite coordinates and setting them
	int foundEndSite = int(currentLine.find("End Site"));

	// the motion is the end of the heirarchy section
	// if this is greater then or equal to 0 we will set 'answer' to false and hence end the loop in the 'getObjectStructure' function and move to 'getMotion'
	int foundMotion = int(currentLine.find("MOTION"));

	// All are computed as they are only five, in case of more terms a while loop will be used which shall look through the contents of a vector

	// the ordering of the if statements is in correspondence with the most frequently occured one being at the top
	if (int(foundJoint)>=0)
	{
		// obtaining joint name present in line with the key word joint
		std::string jointName = currentLine.substr(foundJoint+6);

		// this function shall use the joint name and the information in the subsequent lines to make a SubStructure of the specified name
		SubStructure aSubStructure = getSubStructure(jointName);

		// add this joint to our current Structure
		myStructure.addSubStructure(aSubStructure);

		// Incrementing the current Joints to indicate that the new joint has been added
		numberOfJoints++;

		// cuurent joint is a variable that is used to access the 'part' array
		// number of joints is the actual number of joints in the structure
		// the array part begins from zero and hence we have subtracted one
		currentJoint = numberOfJoints-1;

	}
	else if(int(foundRoot)>=0)
	{
		// obtaining joint name present in line with the key word root
		std::string jointName = currentLine.substr(foundJoint+6);

		// this function shall use the root name and the information in the subsequent lines to make a SubStructure of the specified name
		SubStructure aSubStructure = getSubStructure(jointName);

		// add this joint to our current Structure
		myStructure.addSubStructure(aSubStructure);

		// Incrementing the current Joints to indicate that the new joint has been added
		numberOfJoints++;

		// Incrementing the current Joint which was initially set to -1 so that it now points to the root
		currentJoint++;
	}

	else if(int(foundRetreat)>=0)
	{
		// setting the parent joint of the current joint as the new current joint
		// this is due to the fact that we have encountered a closing curly bracket which means all information regarding this joint has been read
		currentJoint = myStructure.getParentJointIndex(currentJoint);
	}

	else if(int(foundEndSite)>=0)
	{
		// this line contains an opening curly bracket which we only need to write to the output file.
		std::getline(myInputStream,currentLine);
		myOutputStream<<currentLine<<std::endl;

		// this line will contain the Offset keyword and the information regarding the endsite coordinates
		std::getline(myInputStream,currentLine);
		// first we print the line to the output file
		myOutputStream<<currentLine<<std::endl;
		// now we obtain the endsite coordinates
		std::vector<float> endSiteCoordinates = readOffsets();
		// then we set them to the last joint that was set, which is the currentJoint
		myStructure.setEndPoints(currentJoint,endSiteCoordinates);

		// this line contains a closing curly bracket for the endsite section of the 'currentJoint'
		// as the currentJoint has not changed yet so we do not update the currentJoint and simply just print it to the output file
		std::getline(myInputStream,currentLine);
		myOutputStream<<currentLine<<std::endl;

	}
	else if(int(foundMotion)>=0)
	{
		// if the motion keyword has been found this means that the heirarchy section has been read
		answer = false;
	}
	return answer;
}

// Internatl Parsing function for obtainig joint information to add the joint
// All essential fields for the Substructure are obtained from here and then are applied
SubStructure Reader::getSubStructure(std::string jointName)
{


	// the line contains an opening curly bracket which we only need to print to the output file
	std::getline(myInputStream,currentLine);
	myOutputStream<<currentLine<<std::endl;

	// the line contains the offset Coordinates from the parent joint
	// we print it to the output file and then obtain value of offsets
	// the currentLine variable is used by the 'readOffsets' function
	std::getline(myInputStream,currentLine);
	myOutputStream<<currentLine<<std::endl;
	std::vector<float> myOffsets = readOffsets();

	// the number of channels variables is obtained
	// line is printed to the output file
	std::getline(myInputStream,currentLine);
	myOutputStream<<currentLine<<std::endl;
	// the position of the start of the 'CHANNELS' keyword is located
	int numberOfChannels = int(currentLine.find("CHANNELS"));
	// the value is updated to contain the exact value of the number of channels specified for the joint
	numberOfChannels = std::atoi((currentLine.substr(numberOfChannels+9,1)).c_str());

	// specifying that the endsite coordinates are not known as yet
    std::vector<float> userEndsiteCoordinates;

	//parent joint is the current joint value
	SubStructure mySubStructure(jointName,myOffsets,userEndsiteCoordinates,numberOfChannels,currentJoint);

	return mySubStructure;

}

// Internal Parsing function to obtain the offset information from the parent for a joint
// Always returns a vector for float values of size 3
// Float used to reduce memory cost and as data precision is not voilated
// The variable currentLine must be set to contain a line with the 'OFFSET' keyword
std::vector<float> Reader::readOffsets()
{
    // variable will be used to store the translation values after parsing
	std::string translations;

	std::vector<float> myOffsets;

	// variables will be used for parsing purposes
	char* tempString;
	char* myTranslations;

    // fist locating the translation values
	int translationOffsets=int(currentLine.find("OFFSET"));
	translations = currentLine.substr(translationOffsets+7);

    // copying the offset values only from the line in the string values
	myTranslations = new char [translations.size()+1];
	strcpy (myTranslations, translations.c_str());

    // standard tokenization code follows with a space ' '  being the toke used parse
	tempString = strtok(myTranslations," ");

		while (tempString != NULL)
	{
		myOffsets.push_back(atof(tempString)*2.54);			// Conversion to CentiMeters Done as data is presumed to be in inches
		tempString = strtok (NULL, " \n");
	}

    // in case data is corrupted
    // fill the offsets with 0 as default till size is 3
    // in another release in order to put in a corrupt file fixing capability, this information may be inferred once all file has been read
	if (myOffsets.size() < 3)
	{
        do
        {
            myOffsets.push_back(0);
        }while( myOffsets.size() !=3 );
	}

	// freeing the memory used by the temporary pointer varibales
	  free(myTranslations);
	  free(tempString);

      return myOffsets;
}


// Internal Parsing function responsible for Reading the entire Motion Section of the file
// Is called after the 'getObjectStructure' function when the 'readFile' function is called
// Begins on reading the term 'Frames:'
// Stores all the motion Section Data in FrameBVH objects
void Reader::getMotion()
{
    // variable declared to decide when the Motion Section of the file has been finished
	bool continueLoop = true;
	do
	{
	    // obtaining a line from the Heirarchy Sequence
		std::getline(myInputStream,currentLine);

        // parse line for keyWords and process accordingly
		// if neither of the two keywords are found it considers it the start of the frames and calls to reader for all frames
		continueLoop = parseLineMotion();

	}while(continueLoop);

    std::cout<<"Motion Section read\n";
}

// Internal parsing function responsible for Parsing any line from the motion section of the file
bool Reader::parseLineMotion()
{
    // variable to decide whether to continue parsing file or not
	bool answer = true;

	// checking for keywords in the current line which has already bee read
	int foundFrames = int(currentLine.find("Frames:"));
	int foundFrameRate = int( currentLine.find("Frame Time:"));

    // if Frames keyword is found it means that this line will specify how many frames there are in this file
	if (foundFrames >= 0 )
	{
        // locating the number of Frames in the file and assigning them to the class level variable of totalFrames
		totalFrames = atoi((currentLine.substr(foundFrames+8)).c_str());
	}
	else if( foundFrameRate >= 0 )
	{
	    // locating the frame rate from the file and storing it in the class level variable frameRate
		frameRate = atof(currentLine.substr(int(foundFrameRate)+12).c_str());
	}
	else
	{
	    // indicates that the first line for the frames has been read and now we begin adding frames
		addAllFrames();
		answer = false;
	}

	return answer;
}

// Internal Parsing function for reading all the frames and storing their contents
void Reader::addAllFrames()
{
    // the ordering of the functions is as it is because
    // the line containing the first frame has been read already and hence we are now going to parse it for details from first frame
    // if the frame data is incomplete we will augment both the frame data and the 'currentLine' variable and so it is added after the function returns
    // and then we obtain the next line
	for (int currentFrame = 0; currentFrame<totalFrames;currentFrame++)
	{
		readForFrame();
		motionLines.push_back(currentLine);
		std::getline(myInputStream,currentLine);
	}

}

// Internal parsing function for obtaining a frameBVH object from a line that contains the data
void Reader::readForFrame()
{
        // creating a FrameBVH object based on how many channels of data there should be in the frame according to number of joints in the structure
		FrameBVH myFrame(myStructure.getTotalNumberOfChannels());

        // standard parsing code
		char* tempString;
		char* myTranslations;

		// row corresponds to the frameBVH's rotation variable's row +1
		// row = 0 is used to set the translation offsets
		int row =0;

		myTranslations = new char [currentLine.size()+1];
		strcpy (myTranslations, currentLine.c_str());

        // obtaining first value
		tempString = strtok(myTranslations," ");

		while (tempString != NULL)
		{
		    // variable defined here as it will be recreated again and again
		    std::vector<float> myRotations;
			myRotations.push_back(atof(tempString));

			// obtaining second rotation value
			tempString = strtok (NULL, " ");
			myRotations.push_back(atof(tempString));

			// obtaining third rotation value
			tempString = strtok (NULL, " ");
			myRotations.push_back(atof(tempString));

            // setting the translational component
			if (row==0)
			{
				myFrame.setTranslation(myRotations);
			}
			else
			{
			    // setting the rotation components
				myFrame.setRotation(myRotations);
			}

			row++;
			// this will look for a new line or a space
			tempString = strtok (NULL, " \n");
		}

        // Correction Module for incomplete frame data
        // will fill the frame rotations with zeros if the rotations are not already present
        // may result in incorrect strucuture then expected but this is best fixing we can do for now

        if (row<myStructure.getTotalParts())
        {
            // computing how many rotation rows are missing
            int partsToAdd = (myStructure.getTotalParts()-row);
            // printing error for use Notification
            std::cout<<"Error: Incomplete Number of Channels in Frame Data\n";

                // code for filling missing Rotations
                for (int completeFrame =0;completeFrame<partsToAdd;completeFrame++)
                {
                    // entering data to the frame
                    std::vector<float> completingRotations;
                    completingRotations.push_back(0);
                    completingRotations.push_back(0);
                    completingRotations.push_back(0);
                    myFrame.setRotation(completingRotations);

                    // entering data to the currentLine so that a complete frame is entered in the New Output File
                    currentLine.append(" 0.0 0.0 0.0");

                    // incrementing the row counter to indicate that frame data is being completed
                    row++;
                }
        }

        // inserting a complete frame into the myFrames
		myFrames.push_back(myFrame);


        // removing parsing variables
        free(myTranslations);
        free(tempString);

}

// Function for comparing two Structures for similarity
// In Case of similar poses it returns true
bool Reader::comparePoses(Structure testPose, Structure existingPose)
{
    // initially setting the similarity to being similar

    // Only if there exists at least one joint with euclidean separation greater then 5cm will return false
	bool similar = true;
	// checkJoint is set to one initially as root is always at zero so no need to compare the root joint
	int checkJoint = 1;

    // running loop till a joint found
	while (checkJoint<testPose.getTotalParts() && similar==true)
	{
	    // obtaining joint offsets for both the joints after the application of 'adoptPose()'
		std::vector<float> jointNew = testPose.getSubStrcutureOffset(checkJoint);
		std::vector<float> jointOld = existingPose.getSubStrcutureOffset(checkJoint);

        // computing the euclidean distance in cm
		float distance = std::sqrt(std::pow(jointNew[0]-jointOld[0],2) + std::pow(jointNew[1]-jointOld[1],2)+ std::pow(jointNew[2]-jointOld[2],2));

		if ( distance > 5)
		{
			similar = false;
		}
			checkJoint++;
	}
	return similar;
}

// Accessor for obtaining the structure read from the BVH file
// Data only available after the 'readFile' function has been called
Structure Reader::getStructure()
{
	return myStructure;
}

// Accessor for obtaining the total Number of Frames in the file
// Data only available after the 'readFile' function has been called
int Reader::getTotalFrames()
{
	return totalFrames;

}


// Accessor for obtaining the rate at which the frames were intially captured
// Data only available after the 'readFile' function has been called
float Reader::getFrameRate()
{
	return frameRate;
}

// Accessor for obtaining a frame from the total Frames read from the file
// frame number must refer to a correct Frame or else empty frame will be retured which shall not be applicable to structure
FrameBVH Reader::getFrame(int frameNumber)
{
    if ( ( frameNumber < totalFrames ) && ( frameNumber >= 0 ))
    {
        return myFrames[frameNumber];
    }
    else
    {
        FrameBVH emptyFrame;
        return emptyFrame;
    }

}

// Function for reading the contents of the BVH file
// Generates a Structure object and reads all the frames of motion and stores them
// Input stream will be closed after this function has completed
void Reader::readFile()
{
	// reading the heirarchy section
    getObjectStructure();
	std::cout<<"Total Joints: "<<myStructure.getTotalParts()<<std::endl;
	// reading the motion section
    getMotion();
	// all reading done inputstream closed
    myInputStream.close();
	
	std::cout<<"Frames Read: "<<getTotalFrames()<<std::endl;
	
	
}

// This Function is responsible for finding the frames corresponding to Unique Poses
// Unique Poses are defined as poses having euclidean separation greater then 5cm for at least one joint
// It also writes the poses in the output File
// Please note that all translational components are set to zero in this case as a 'pose' is translation invariant
void Reader::uniquePoseIdentification()
{
    // first enter the initial Pose in the unique poses set, in most cases this is  T-Pose
	uniquePoses.push_back(myStructure);

	// Initialize a vector to store index of correc Unique Poses
	std::vector<int> correctFrames;

	for (int makeFile = 0; makeFile<myFrames.size()-1;makeFile++)
	{
	    // Apply Current Frame and obtain a Structure in that Pose
		Pose poseA;
		Structure firstStructure = poseA.adoptPose(myStructure,myFrames[makeFile]);

		// Now Comparing against all the structures in uniquePoses to verify that it is unique
		int checkMatch = uniquePoses.size()-1;
		// match initially set to false indicating that it is unique until one of the uniquePoses suggests otherwise on comparison
		bool foundMatch = false;

		while( checkMatch>=0 && foundMatch == false)
		{
		    // comparing the newly created structure from fraem to uniquePoses
			foundMatch = comparePoses(uniquePoses[checkMatch],firstStructure);
			checkMatch--;
		}

        // if none of the unique poses suggests that the structure is not unique then put the pose in uniquePoses for the next frame
        // also put the frameNumber in the correctFrames vector array
		if (foundMatch == false)
		{
			uniquePoses.push_back(firstStructure);
			correctFrames.push_back(makeFile);
		}
	}
	// Comparison for all frames has been completed

	std::cout<<"Number Of Unique Poses in File: "<<uniquePoses.size()<<std::endl;

	// Begin writing the unique Poses data to the output file
	myOutputStream<<"Frames: "<<uniquePoses.size()-1<<std::endl;
	// Custom Frame time is 1 fps as we have reduced the number of Frames without any standart subsampling rate
	myOutputStream<<"FrameBVH Time: 1"<<std::endl;
	// write the T-Pose which is contained in the first frame
    myOutputStream<<motionLines[0]<<std::endl;

    // Loop for printing the Non- T Pose information
	for (int printing = 0;printing<correctFrames.size();printing++)
	{
	    // obtaining the string data for line representing a correct Pose
		std::string theLine = motionLines[correctFrames[printing]];

        // standard code for tokenization for reading the translational component of the root and setting it to zero
		char* tempString;
		char* myTranslations;

		myTranslations = new char [theLine.size()+1];
		strcpy (myTranslations, theLine.c_str());

        tempString = strtok(myTranslations," ");
		int count = 0;
		while (tempString != NULL && count<=2)
	{
		myOutputStream<<"0.00 ";
		tempString = strtok (NULL, " \n");
		count++;
	}

        // obtaining the index of the remaining rotational components from the line
    	int findPlace=int(theLine.find(tempString));

		myOutputStream << theLine.substr(findPlace)<<std::endl;

		free(myTranslations);
        free(tempString);
	}
    myOutputStream.close();

    std::cout<<"Unique Poses Output File Written Successfully\n";
}
