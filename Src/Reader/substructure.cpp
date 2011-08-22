#include "substructure.h"

// Default constructor for the class.
// Everything is set to null or default value
SubStructure::SubStructure()
{
	name="";

	offsetCoordinates.push_back(0);
	offsetCoordinates.push_back(0);
	offsetCoordinates.push_back(0);

	endsiteCoordinates.push_back(0);
	endsiteCoordinates.push_back(0);
	endsiteCoordinates.push_back(0);

	numberOfChannels = 0;
	indexParent = -1;

}

// User defined constructor for the class
// User has to specify all the class variables
SubStructure::SubStructure(std::string sName,std::vector<float> userOffsetCoordinates,std::vector<float> userEndsiteCoordinates,int sNumberOfChannels,int sIndexParent)
{
	name = sName;

	offsetCoordinates = userOffsetCoordinates;
    endsiteCoordinates = userEndsiteCoordinates;

	numberOfChannels = sNumberOfChannels;
	indexParent = sIndexParent;

}

// Standard destructor for the class
// Clears all vectors
SubStructure::~SubStructure()
{
     offsetCoordinates.clear();
     endsiteCoordinates.clear();
}

// Display function for the class data
// Prints all attribute values to the console
void SubStructure::print()
{
	std::cout<<"Joint Name: " << name<<std::endl;

	std::cout<<"X-Offset-Start: "<<offsetCoordinates[0]<<std::endl;
	std::cout<<"Y-Offset-Start: "<<offsetCoordinates[1]<<std::endl;
	std::cout<<"Z-Offset-Start: "<<offsetCoordinates[2]<<std::endl;

	if (endsiteCoordinates.size()==3)
	{
		std::cout<<"X-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
		std::cout<<"Z-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
		std::cout<<"Z-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
	}
	else
	{
		std::cout<<"Endsite Not Defined\n";
	}	
	
	std::cout<<"Number of Channels: "<<numberOfChannels<<std::endl;
	std::cout<<"Parent Joint Index: "<<indexParent<<std::endl<<std::endl;

}

void SubStructure::printToFile(std::ofstream& outputStream)
{
	outputStream<<"Joint Name: " << name<<std::endl;

	outputStream<<"X-Offset-Start: "<<offsetCoordinates[0]<<std::endl;
	outputStream<<"Y-Offset-Start: "<<offsetCoordinates[1]<<std::endl;
	outputStream<<"Z-Offset-Start: "<<offsetCoordinates[2]<<std::endl;

	if (endsiteCoordinates.size()==3)
	{
		outputStream<<"X-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
		outputStream<<"Z-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
		outputStream<<"Z-Offset-End: "<<endsiteCoordinates[0]<<std::endl;
	}
	else
	{
		outputStream<<"Endsite Not Defined\n";
	}	
	
	outputStream<<"Number of Channels: "<<numberOfChannels<<std::endl;
	outputStream<<"Parent Joint Index: "<<indexParent<<std::endl<<std::endl;

}


// Mutator for specifying the name of the joint
// Default name is an empty string
void SubStructure::setName(std::string userName)
{
    name = userName;
}

// Mutator for specifying the offset coordinates for the joint from its parent
// Only applies coordinates if all X Y and Z coordinate are specified
// Float type used to minimize memory wastage
void SubStructure::setOffset(std::vector<float> theOffset)
{
    if (theOffset.size()==3)
    {
        offsetCoordinates = theOffset;
    }

}

// Mutator for specifying the endsite coordinates for the joint
// Only applies coordinates if all X Y and Z coordinate are specified
// Float type used to minimize memory wastage
void SubStructure::setEndPoints(std::vector<float> userEndsiteCoordinates)
{
    if (userEndsiteCoordinates.size()==3)
    {
        endsiteCoordinates = userEndsiteCoordinates;
    }
}


// Mutator for specifying the parent joint's index
// For root joint please set value to -1
void SubStructure::setParentIndex(int theParentIndex)
{
	indexParent = theParentIndex;
}


// Mutator for specifying the number of channels
// Default number is 0
void SubStructure::setNumberOfChannels(int userNumberOfChannels)
{
    numberOfChannels = userNumberOfChannels;
}

// Accessor for obtaining name of joint
std::string SubStructure::getName()
{
	return name;
}

// Accessor for obtaining SubStructure offsets from parent
std::vector<float> SubStructure::getOffset()
{
	return offsetCoordinates;
}

// Accessor for obtaining endsite coordinates of substructure
std::vector<float> SubStructure::getEndsiteCoordinates()
{
    return endsiteCoordinates;
}

// Accessor for obtaining number of channels
int SubStructure::getNumberOfChannels()
{
    return numberOfChannels;
}

// Accessor for obtaining SubStructure parent joint index
int SubStructure::getParentIndex()
{
	if (indexParent == -1)
	{
		
		return 0;   // to prevent error regarding unavailble region of memory access.
	}
	else
	{
        return indexParent;
	}
}
