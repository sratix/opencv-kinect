#include "BodyPart.h"

// Non-Standard Constructor, intializes things to Default Values
// Minima are set to high value so first entry corrects them
// Maxima are set to low value so first entry corrects them
// Means are set to zero 
BodyPart::BodyPart(std::string partName)
{
	numberOfVertices = 0;
	name = partName;
	
	minX = 10000;
	maxX = -10000;
	
	minY = 10000;
	maxY = -10000;
	
	minZ = 10000;
	maxZ = -10000;
	
	meanX = 0;
	meanY = 0;
	meanZ = 0;	
}

// Standard Destructor for the class
// Will empty out all vectors
BodyPart::~BodyPart()
{
	//std::cout<<"Clearing BodyPart : "<<name<<std::endl; 
	
	// removing each coordinate
	for (int aVertice = 0; aVertice<numberOfVertices; aVertice++)
	{
		verticeCoordinates[aVertice].clear();
	}
	// removing vertices Index
	verticesIndex.clear();
	//std::cout<<"Body Part Removed\n";
}


// Function is optimized to save repeated traversals
// Updates all Attributes
// Is used within removePoint 
void BodyPart::updateAttributes()
{
	// Initializing values to defaults
	minX = 1000;
	minY = 1000;
	minZ = 1000;
	
	maxX = -1000;
	maxY = -1000;
	maxZ = -1000;
	
	meanX = 0;
	meanY = 0;
	meanZ = 0;
	
	// Computing new values
	// If run on different threads this function should have a LOCK
	for (int aCoordinate = 0; aCoordinate< numberOfVertices; aCoordinate++)
	{
		if (verticeCoordinates[aCoordinate][0] < minX)
		{
			minX = verticeCoordinates[aCoordinate][0];
		}
		if (verticeCoordinates[aCoordinate][0] > maxX)
		{
			maxX = verticeCoordinates[aCoordinate][0];
		}
		
		// updatin the Y Coordinate Min Max Data
		if (verticeCoordinates[aCoordinate][1] < minY)
		{
			minY = verticeCoordinates[aCoordinate][1];
		}
		if (verticeCoordinates[aCoordinate][1] > maxY)
		{
			maxY = verticeCoordinates[aCoordinate][1];
		}
		
		// updatin the Z Coordinate Min Max Data
		if (verticeCoordinates[aCoordinate][2] < minZ)
		{
			minZ = verticeCoordinates[aCoordinate][2];
		}
		if (verticeCoordinates[aCoordinate][2] > maxZ)
		{
			maxZ = verticeCoordinates[aCoordinate][2];
		}

		// Simple Summation over values over here
		// Followed by single Division
		// Reduces Number of Operations performed
		meanX = meanX + verticeCoordinates[aCoordinate][0];
		meanY = meanY + verticeCoordinates[aCoordinate][1];
		meanZ = meanZ + verticeCoordinates[aCoordinate][2];
	}
	
	// Dividing to obtain the means
	meanX = meanX / numberOfVertices;
	meanY = meanY / numberOfVertices;
	meanZ = meanZ / numberOfVertices;
	
	
}

// Function for inserting a Coordinate into a BodyPart
// Will automatically update key attributes of the BodyPart
void BodyPart::insertPoint(std::vector<float> pointCoordinates, int index)
{
	// Integrity Check on data
	if (pointCoordinates.size()==3 && index >= 0)
	{
		verticeCoordinates.push_back(pointCoordinates);
		verticesIndex.push_back(index);
		
		// updatin the X Coordinate Min Max Data
		if (pointCoordinates[0] < minX)
		{
			minX = pointCoordinates[0];
		}
		if (pointCoordinates[0] > maxX)
		{
			maxX = pointCoordinates[0];
		}
		
		// updatin the Y Coordinate Min Max Data
		if (pointCoordinates[1] < minY)
		{
			minY = pointCoordinates[1];
		}
		if (pointCoordinates[1] > maxY)
		{
			maxY = pointCoordinates[1];
		}
		
		// updatin the Z Coordinate Min Max Data
		if (pointCoordinates[2] < minZ)
		{
			minZ = pointCoordinates[2];
		}
		if (pointCoordinates[2] > maxZ)
		{
			maxZ = pointCoordinates[2];
		}

		// Updating the Means
		meanX = ((meanX*numberOfVertices) + pointCoordinates[0])/(numberOfVertices+1);
		meanY = ((meanY*numberOfVertices) + pointCoordinates[1])/(numberOfVertices+1);
		meanZ = ((meanZ*numberOfVertices) + pointCoordinates[2])/(numberOfVertices+1);
		
		// Incrementing the number of Vertices
		numberOfVertices++;
	}	
		
}

// Function responsible for Removing a point from the current Body Part Mesh Description
// must provide function with a valid index
// removes the coordinate from the set of Coordinates
// removes the index from the set of Indices
// decrements the set of Vertices
// updates the means
void BodyPart::removePoint(int index)
{
	if (index>=0 && index<numberOfVertices)
	{
		verticeCoordinates.erase(verticeCoordinates.begin()+index);
		verticesIndex.erase(verticesIndex.begin()+index);
		numberOfVertices--;
		updateAttributes();
	}

}

// Function for dividing a Part along an Axis into two sub parts
// In the output Variable the index 0 contains the body part above the mean
// The variable on index 1 contains the body part below the mean
std::vector<BodyPart> BodyPart::dividePart(std::string alongAxis)
{
	// Initializing Variables
	
	// choice denotes the X Y or Z coordinate along which a split is to be done
	int choice;
	
	// mean Value is to represent the mean value along that axis
	float meanValue;

	// selecting the choice and meanValue from the stored values based on the Axis the user has specified
	if (alongAxis.compare("X") == 0 )
	{
		choice = 0;
		meanValue = meanX;
	}
	else if (alongAxis.compare("Y") == 0 )
	{
		choice = 1;
		meanValue = meanY;
		
	}
	else if (alongAxis.compare("Z") == 0 )
	{
		choice = 2;
		meanValue = meanZ;
	}

	// Initializing the two new BodyParts that will be created as a consequence of this division
	// Body parts are initialized with no name and must be given a name once recieved using the 'setName'
	BodyPart aboveMean("");
	BodyPart belowMean("");
	
	// Selecting Coordinates for for each part based on whether above mean or below mean
	for (int partPoint = 0; partPoint < numberOfVertices; partPoint++)
	{
		if (verticeCoordinates[partPoint][choice] >= meanValue)
		{
			aboveMean.insertPoint(verticeCoordinates[partPoint],verticesIndex[partPoint]);
		}
		else
		{
			belowMean.insertPoint(verticeCoordinates[partPoint],verticesIndex[partPoint]);		
		}	
	}
	
	// creating a vector to return both the BodyParts
	std::vector<BodyPart> newParts;
	
	// inserting the new Body parts
	newParts.push_back(aboveMean);
	newParts.push_back(belowMean);
	
	// returning the Vector Created
	return newParts;
}

// Standard Accessor for BodyPart Name
// Returns the string representing Body Part Name
// Will always return an answer
std::string BodyPart::getName()
{
	return name;
}

// Standard Accessor for Major Axis
// Major Axis is defined as the axis over which the object has the greatest span
// Will return X Y or Z based on which axis has the greatest Range Span
std::string BodyPart::getMajorAxis()
{
	// computing Ranges
	float zRange =  maxZ-minZ;
	float yRange = maxY-minY;
	float xRange = maxX-minX;
	
	// if Z range is th greatest
	if (zRange > yRange && zRange > xRange)
	{
		return "Z";
	}
	//  if y range is the greatest
	else if (yRange > zRange && yRange > xRange)
	{
		return "Y";
	}
	else
	{
		return "X";
	}

}

// Standard Accessor for the total number of Vertices in the Mesh
// Will always return an answer greater then zero
int BodyPart::getNumberOfVertices()
{
	return numberOfVertices;
}

// Standard Accessor for Vertex Index corresponding to the Index in the global structure
// Requires an input to the index of the coordinate in the part
// input 'coordinateNumber' must be greater then equal to zero and less then the number of Vertices
int BodyPart::getVertexIndex(int coordinateNumber)
{
	if (coordinateNumber<numberOfVertices && coordinateNumber>=0)
	{
		return verticesIndex[coordinateNumber];
	}
	else
	{
		std::cout<<"Error: Point Being referred to is out of Bounds "<<std::endl;		
		return -1;
	}
}

// Standard Accessor for Obtaining a Minimum Value along an axis
// Input axis must be from the choice of either X Y or Z
float BodyPart::getMin(std::string axis)
{
	if (axis.compare("X")==0)
	{
		return minX;
	}
	else if (axis.compare("Y")==0)
	{
		return minY;
	}
	else if(axis.compare("Z")==0)
	{
		return minZ;
	}
	else
	{
		std::cout<<"Incorrect Access Specified\n";
		return 0;
	}
}

// Standard Accessor for Obtaining a Maximum Value along an axis
// Input axis must be from the choice of either X Y or Z
float BodyPart::getMax(std::string axis)
{
	if (axis.compare("X")==0)
	{
		return maxX;
	}
	else if (axis.compare("Y")==0)
	{
		return maxY;
	}
	else if(axis.compare("Z")==0)
	{
		return maxZ;
	}
	else
	{
		std::cout<<"Incorrect Access Specified\n";
		return 0;
	}
}

// Standard Accessor for Coordinate
// Requires an input to the index of the coordinate in the part
// input 'coordinateNumber' must be greater then equal to zero and less then the number of Vertices
std::vector<float> BodyPart::getCoordinate(int coordinateNumber)
{
	if (coordinateNumber<numberOfVertices && coordinateNumber>=0)
	{
		return verticeCoordinates[coordinateNumber];
	}
	else
	{
		std::cout<<"Error: Point Being referred to is out of Bounds "<<std::endl;
		std::vector<float> emptyVector;
		return emptyVector;
	}
}

// Standard mutator for BodyPart Name
// Requires an input of a name
void BodyPart::setName(std::string newName)
{
	name = newName;
}
