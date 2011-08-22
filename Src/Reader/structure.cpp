#include "structure.h"

// Default constructor for the class.
// Contains no parts and other variables initialized to default or null
Structure::Structure()
{
	totalParts = 0;
}

// Standard destructor for the class
// Clears all vectors used to free allocated space
Structure::~Structure()
{
    part.clear();
}

// Display function for the class data
// Prints the complete Structure with all the joints to the console
void Structure::print()
{
	for (int loop=0;loop<totalParts;loop++)
	{
		std::cout<<"Printing Joint: "<<loop+1<<std::endl;
		part[loop].print();
		std::cout<<std::endl;
	}
}

// Adds a component to the current Structure
// Also increments the counter for commulative parts of the structure
void Structure::addSubStructure(SubStructure aSubStructure)
{
		part.push_back(aSubStructure);
		totalParts++;
}


// A 2D orthographic Visualization of the entire Structure as described by its current Offsets
// Visualization may be improved by using PCL (Point Cloud Library)
// Centers the Structure
// does not make use of Translation
cv::Mat Structure::visualizeStructure()
{
	int sizeX = 600;    // default Picture size in X
	int sizeY = 600;    // default Picture size in Y

	cv::Mat myVisualization(sizeX, sizeY, CV_8UC1,cv::Scalar(0));

    // Correction is computed and applied to centre the structure in the Image
	int correctionX = sizeX/2;
	int correctionY = sizeY/2;

	int correctScalingFactor = 4;

	for (int joint = 0;joint<totalParts;joint++)
	{		
	    // Visualization coordinates are the coordinates of a point defined from origin, not the parent joint
		std::vector<float> coordinates = getVisualizationCoordinates(joint);
		std::vector<float> coordinatesParent = getVisualizationCoordinates(part[joint].getParentIndex());
		
        // Scaling the Skeleton to make it an appropriate size where pose is visible
		coordinates[0]= int( correctionX - ( coordinates[0]*correctScalingFactor ) );
		coordinates[1]= int( correctionY - ( coordinates[1]*correctScalingFactor ) );
		

		coordinatesParent[0]= int( correctionX - ( coordinatesParent[0]*correctScalingFactor ) );
		coordinatesParent[1]= int( correctionY - ( coordinatesParent[1]*correctScalingFactor ) );
		
		
        // Convert both of the above coordinates to homogenous form
        // Multiply with matrix containing camera calibration to get different view.
        // Not implemented in this version, This version only provides an orthographic projection
        // Camera parameters are set to identitiy

        // Displaying a circle to denote the exact location of a joint
        // Displaying a line to indicate linkages between joints
		cv::circle(myVisualization, cv::Point(coordinates[0],coordinates[1]), 5, cv::Scalar(255, 255, 255));
		
		cv::line(myVisualization, cv::Point(coordinates[0],coordinates[1]), cv::Point(coordinatesParent[0],coordinatesParent[1]), cv::Scalar(255, 255, 255));
		
		
	}	

	return myVisualization;
}


// Private function for checking if the joint mentioned has any children or not
// Returns true if it has no children joints
bool Structure::checkForEndJoint(int partNumber)
{
    if ( ( partNumber >= 0 ) && ( partNumber <= totalParts ) )
    {
        int counter = 0;
        bool found = true;
        while ( ( counter < totalParts ) && found==true)
        {
            found = ( part[counter].getParentIndex() != partNumber);
            counter++;
        }
    return found;
	}
}

// Accessor for obtaining the name of a specific part
// The variable joint must refer to a valid joint number
std::string Structure::getPartName(int joint)
{
    if (( joint >= 0 ) && ( joint<= totalParts ) )
    {
        return part[joint].getName();
    }
    else
    {
        return "";
    }
}

// Accessor for obtaining the name of a specific part
// The variable joint must refer to a valid joint number
// In case of invalid Joint entry the function will return -2
int Structure::getParentJointIndex(int joint)
{
    if (( joint >= 0 ) && ( joint<= totalParts ) )
    {
        return part[joint].getParentIndex();
    }
    else
    {
        std::cout<<"Invalid Joint Specified\n";
        return -2;
    }
}


void Structure::printToFile(std::string fileName)
{
	std::ofstream outputFile;
	outputFile.open(fileName.c_str());
	
	for (int joint =0; joint < totalParts;joint++)
	{
		part[joint].printToFile(outputFile);
	}

}


// Accessor for obtaining SubStructure offsets from parent of a particular joint
// the variable partNumber must have indicate a valid part ( non negative and within the parts defined )
std::vector<float> Structure::getSubStrcutureOffset(int joint)
{
    std::vector<float> myOffset;

    if ( ( joint < totalParts) && ( joint >= 0 ) )
    {
         myOffset = part[joint].getOffset();
    }
    else
    {
        std::cout<<"Invalid Joint Reference\nDefault Value Returned\n";
        myOffset.push_back(0);
        myOffset.push_back(0);
        myOffset.push_back(0);
    }

	return myOffset;

}

// Accessor for obtaining the total Number of Channels for the data in the structure
int Structure::getTotalNumberOfChannels()
{
    int totalSum= 0;
    for (int sumJoints = 0; sumJoints<totalParts; sumJoints++)
    {
        totalSum = totalSum+part[sumJoints].getNumberOfChannels();
    }
    return totalSum;
}

// Accessor for obtaining the total parts in the structure
// Mostly used in making loops over all joints in the structure
int Structure::getTotalParts()
{
	return totalParts;
}

// Function for obtaining the Min Coordinate in either of X Y or Z Direction for the entire structure
// The term varibale must contain only 'X' 'Y' or 'Z'
// Any other value of term Variable will return 0.0
float Structure::getMinCoordinate(std::string term)
{
    int location = -1;

    if (term.compare("X"))
    {
        location = 0;
    }
    else if (term.compare("Y"))
    {
        location = 1;
    }
    else if (term.compare("Z"))
    {
        location = 2;
    }
    else
    {
        std::cout<<"Incorrect Term Specified\n";
        return 0.0;
    }

    float minValue = 1000; // artifical incorrect value

    for (int checkParts = 0; checkParts<totalParts; checkParts++)
    {
        std::vector<float> partCoordinates = getVisualizationCoordinates(checkParts);
        if (partCoordinates[location] < minValue)
        {
			minValue = partCoordinates[location];
        }
    }

}

// Function for obtaining the Max Coordinate in either of X Y or Z Direction for the entire structure
// The term varibale must contain only 'X' 'Y' or 'Z'
// Any other value of term Variable will return 0.0
float Structure::getMaxCoordinate(std::string term)
{
    int location = -1;

    if (term.compare("X"))
    {
        location = 0;
    }
    else if (term.compare("Y"))
    {
        location = 1;
    }
    else if (term.compare("Z"))
    {
        location = 2;
    }
    else
    {
        std::cout<<"Incorrect Term Specified\n";
        return 0.0;
    }

    float maxValue = -1000; // artifical incorrect value
    for (int checkParts = 0; checkParts<totalParts; checkParts++)
    {
        std::vector<float> partCoordinates = getVisualizationCoordinates(checkParts);
        if (partCoordinates[location] > maxValue)
        {
			maxValue = partCoordinates[location];
        }
    }

}

// Mutator for specifying the parent joint of a current Joint
// Joint to whom a parent is being assigned must exist
// The variable parentIndex must be a valid joint or -1 indicating it is the root joint
void Structure::setParent(int joint,int parentIndex)
{
    if ( ( joint >= 0 ) && ( joint <= totalParts ) && ( parentIndex >= -1 ) && ( parentIndex <= totalParts )  && ( joint != parentIndex) )
    {
        part[joint].setParentIndex(parentIndex);
    }
    else
    {
        std::cout<<"Joint Specified or Parent Index is incorrect\n";
    }
}

// Mutator for specifying the offset for a joint
// Joint to whom a offset is being assigned must exist
// Offset being assigned must have three values
void Structure::setOffset(int joint,std::vector<float> offset)
{
    if ( ( joint >= 0 ) && ( joint<= totalParts ) && ( offset.size() ==3 ) )
    {
        part[joint].setOffset(offset);
        offset.clear();
    }
    else
    {
        std::cout<<"Offset Contains Incorrect Entries or Joint Specified is incorrect\n";
    }


}

// Mutator for specifying the end points of the joints which are the last in a chain
// The variable userEndsiteCoordinates must have 3 float values to maintain integrity of data
// the variable partNumber must have indicate a valid part ( non negative and within the parts defined )
// The variable partNumber must not point to a part that is the parent of another Part.
void Structure::setEndPoints(int partNumber,std::vector<float> userEndsiteCoordinates)
{
    bool isEndSite = checkForEndJoint(partNumber);

	if ( ( partNumber <= totalParts ) && ( partNumber >= 0 ) && ( userEndsiteCoordinates.size()==3 ) && isEndSite)
	{
        part[partNumber].setEndPoints(userEndsiteCoordinates);
	}

}


// Private function to be used to sum coordinates and get resultant positions
std::vector<float> Structure::addCoordinates(std::vector<float> coordinatesOne,std::vector<float> coordinatesTwo)
{
    if (coordinatesOne.size()== coordinatesTwo.size())
    {
        coordinatesOne[0] = coordinatesOne[0]+coordinatesTwo[0];
        coordinatesOne[1] = coordinatesOne[1]+coordinatesTwo[1];
        coordinatesOne[2] = coordinatesOne[2]+coordinatesTwo[2];
    }

	return coordinatesOne;
}


// Function returns true coordinates for a Structure, not offset Coordinates
// The Variable joint must be valid joint for the function to work
// Incorrect joint value will result in a three length zero vector
std::vector<float> Structure::getVisualizationCoordinates(int joint)
{
	if (joint==0)
	{
		return part[0].getOffset();
	}
	else
	{
		std::vector<float> myCoordinates = part[joint].getOffset();
		return addCoordinates(myCoordinates,getVisualizationCoordinates(part[joint].getParentIndex()));
	}
}

