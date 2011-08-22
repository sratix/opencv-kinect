#include "Mesh.h"

// Standard Constructor
// Initializes everything to a default value
// To be used for constructing a mesh without any arguments avaliable
Mesh::Mesh()
{
	numberOfVertices = 0;
	numberOfFaces = 0;
	
	completeMeanX = 0;
	completeMeanY = 0;
	completeMeanZ = 0;
	
	pathCoordinatesFile = "";
	pathLabelsFile = "";
	pathFacesFile ="";
	
}

// Non- Standard Constructor for making a Mesh
// Assigns the value specified for the paths
// each path must point to a valid file name
Mesh::Mesh(std::string pathCoordinates, std::string pathFaces, std::string pathLabels)
{	
	// intializing a variable that specifies that pathLabels is present and not empty
	bool checkLabels = true;
	
	// reading the vertice coordinates and storing them in their respective container from the mesh class
	verticeCoordinates = initializer.readCoordinates(pathCoordinates);	
		
	// reading the vertice labels and storing them in their respective container from the mesh class
	verticeLabels = initializer.readLabels(pathLabels);
	
	// verifying that the verticeLabels is not empty for future decisions
	if (verticeLabels.size()==0)
	{
		// notifying user that the file is missing
		std::cout<<"LabelFileMissing"<<std::endl;
		
		// setting the flag to false so that body parts are not constructed as data is missing
		checkLabels = false;
		
		// create an empty labels file that attaches the label 'none' to all vertices as it has no vertice
		for (int createEmpty = 0; createEmpty<verticeCoordinates.size();createEmpty++)
		{
			verticeLabels.push_back("None");
		}
	}
	
	// informing the user that the vertice data has been read
	std::cout<<"Vertices Data Read\n";
	
	// reading the faces data
	faces = initializer.readFaces(pathFaces);
	
	// informing the user of the data has been read
	std::cout<<"Faces Data Read\n";
	
	// setting the number of vertices that were read	
	numberOfVertices = verticeCoordinates.size();
	
	// setting the number of faces that were read
	numberOfFaces = faces.size();
	
	// obtaining the mean from the reader 
	std::vector<float> theMeans  = initializer.getMean();
	
	// load the means in their corresponding variable
	completeMeanX = theMeans[0];
	completeMeanY = theMeans[1];
	completeMeanZ = theMeans[2];
	
	// mean subtract Coordinates
	meanSubtractCoordinates();
	
	// if labels were updated then form body parts as all data is avaliable for forming body parts
	if (checkLabels==true)
	{	
		// forms body parts from 
		formBodyParts();
	}
	// informing the used of the status
	std::cout<<"Body Parts Formation Complete \n";
	std::cout<<"Mesh Loading Complete\n";
	
	
	// storing path names for future data output
	pathCoordinatesFile = pathCoordinates;
	pathLabelsFile = pathLabels;
	pathFacesFile = pathFaces;
}

// standard Destructor for the Mesh object
// Empties the containers so no memory is left reserved
Mesh::~Mesh()
{

	// update the verticesLabels so that the update form can be output 
	// probably should have  flag which if checked leads to updating	
	updateMeshLabels();
	
	// initializing a name for labels file in case we read labels from an external mesh
	std::string nameFileLabels = "";
	
	// obtaining the path of the directory to which we are going to write the updated information
	std::string pathDirectory = pathCoordinatesFile.substr(0,int(pathCoordinatesFile.find_last_of("\\")));
	
	// obtaining the file name that was used to load the coordinates
	std::string nameFileCoordinates = pathCoordinatesFile.substr(int(pathCoordinatesFile.find_last_of("\\"))+1);
	
	// checking if labels file was loaded from an external mesh
	if (pathLabelsFile.compare("")!=0)
	{
		// if labels were loaded from a file then use that file name to write the new file
		nameFileLabels = "New"+pathLabelsFile.substr(int(pathLabelsFile.find_last_of("\\"))+1);
	}
	else
	{
		// else set the file name as defined
		nameFileLabels = "New_MHX_Mesh.labels";
	}
	
	// writing the newly updated files as a safety precaution
	finalizer.writeFile(pathDirectory+"New"+nameFileCoordinates,verticeCoordinates);
	finalizer.writeFile(pathDirectory+"New"+nameFileLabels,verticeLabels);
	
}

// function written to load a new mesh to save recreating a variable if needed
// paths must point to valid files
// first file must have the extension of .coords
// second file must have the extension of .faces
// third file must have the extension of .labels
void Mesh::loadMesh(std::string pathCoordinates, std::string pathFaces, std::string pathLabels)
{
	// clearing all existing data for mesh
	verticeCoordinates.clear();
	faces.clear();
	verticeLabels.clear();

	// loading new data
	verticeCoordinates = initializer.readCoordinates(pathCoordinates);
	faces = initializer.readFaces(pathFaces);
	verticeLabels = initializer.readLabels(pathLabels);
	
	// loading new data attributes
	numberOfVertices = verticeCoordinates.size();
	numberOfFaces = faces.size();
	
	// re forming body parts based on new data
	formBodyParts();
	
	// informing the user
	std::cout<<"New Mesh Loading Complete\n";
}

// One of the Key Functions of this module
// Performs the reduction of body part labels
// pathMapping is the path to Mapping.reduce file
// performs a renamin of the body parts
// performs any divison of parts specified
// performs updating of the mesh labels 
void Mesh::remapMesh(std::string pathMapping)
{
	// loading the Mapping that contains the instructions for re-grouping
	std::vector<std::vector<std::string> > theMapping = initializer.readMapping(pathMapping);	
	
		
	// Code Below gets the Data in a state that is ready to be applied to existing labels.	
	for (int swapLabel = 0; swapLabel < theMapping.size(); swapLabel++)
	{
		// if the mapping simply defines a renaming of the names of the Body Part then do that
		if (theMapping[swapLabel].size()==3)
		{
			// obtain index to part that is being re mapped
			int partIndex = getLocalPart(theMapping[swapLabel][0]);
			
			// set the new part name for the variable as specified
			theBody[partIndex].setName(theMapping[swapLabel][1]);			
		}
		// if the mapping defines that the body part be divided
		else
		{		
			// find the body part index being referred to
			int partIndex = getLocalPart(theMapping[swapLabel][0]);
			
			// load the part into a new variable
			BodyPart currentPart = theBody[partIndex];
			
			// divide in just left and right
			
			// the index 1 of the mapping in this case defines the axis along which to divide the mesh
			// it may have one or two characters
			// always divide along first character
			std::vector<BodyPart> newParts = currentPart.dividePart(theMapping[swapLabel][1].substr(0,1));
			
			// assumption is that it will be divided into left and right first
			
			// assigning the newly made parts to the right part
			BodyPart rightPart = newParts[0];
			
			// assigning the newly made parts to a left part
			BodyPart leftPart = newParts[1];
			
			// setting names for the parts
			// the third entry in the mapping contains a reference to the base name for this part
			
			// the right and left is decided based on whether it is above mean or below mean
			rightPart.setName("Right-"+theMapping[swapLabel][2]);
			leftPart.setName("Left-"+theMapping[swapLabel][2]);
			
			// specifying that two new parts have been added
			int checkAdd = 2;
			
			// checking if therer is a second division of the part to be done
			// if the 1st index of the vector entry in theMapping contains two variables then it is specifying two axis along which the part will be divided
			if (theMapping[swapLabel][1].size()==2)
			{
				// specifying that the main body part was divided into four subparts
				checkAdd = 4;
				
				// dividing each left and right part based on new division axis specified in the mapping
				std::vector<BodyPart> newPartsL = leftPart.dividePart(theMapping[swapLabel][1].substr(1));
				std::vector<BodyPart> newPartsR = rightPart.dividePart(theMapping[swapLabel][1].substr(1));
				
				// craeting new body parts and storing the parts divided from the right part into them
				BodyPart rightUpper = newPartsR[0];
				BodyPart rightLower = newPartsR[1];
				
				// craeting new body parts and storing the parts divided from the left part into them
				BodyPart leftUpper = newPartsL[0];
				BodyPart leftLower = newPartsL[1];
				
				// setting names for the right divided parts
				rightUpper.setName("Right-"+theMapping[swapLabel][2]+"-Upper");
				rightLower.setName("Right-"+theMapping[swapLabel][2]+"-Lower");
				
				// setting names for the left divided parts
				leftUpper.setName("Left-"+theMapping[swapLabel][2]+"-Upper");
				leftLower.setName("Left-"+theMapping[swapLabel][2]+"-Lower");
				
				// inserting the new parts
				theBody.push_back(leftUpper);
				theBody.push_back(leftLower);
				theBody.push_back(rightUpper);
				theBody.push_back(rightLower);
				
				// emptying all the vectors
				newPartsL.clear();
				newPartsR.clear();
				newParts.clear();
			}
			
			// Deleting the original part which was dividede
			theBody.erase(theBody.begin()+partIndex);
			
			// if only 2 parts were created
			if (checkAdd == 2)
			{
				// inserting the new parts into the body structure
				theBody.push_back(leftPart);
				theBody.push_back(rightPart);
				
				// emptying the vector
				newParts.clear();
			}
						
		}
			
	}
	
	// Code for grouping existing body into a new body to remove redudancies in labelling and aggregating body parts
	
	// creating a new BodyPart Collection
	std::vector<BodyPart> newBody;
	
	// Traversing each part in the new body
	for (int makeNewBody = 0; makeNewBody < theBody.size(); makeNewBody++)
	{
		// obtaining the index of the part in the new Body 
		int partIndex = findBodyPart(theBody[makeNewBody].getName(),newBody);
		// if part exists and then group the part that exists with the one presented		
		if ( partIndex >=0 )
		{			
			
			for (int addCoordinate =0; addCoordinate < theBody[makeNewBody].getNumberOfVertices(); addCoordinate++)
			{
				newBody[partIndex].insertPoint( theBody[makeNewBody].getCoordinate(addCoordinate),theBody[makeNewBody].getVertexIndex(addCoordinate) );			
			}
			
		}
		// if part does not exist insert this into the new Body
		else
		{
			BodyPart aPart = theBody[makeNewBody];
			newBody.push_back(aPart);
			
		}		
	}
	
	// empty out the existing old body
	theBody.clear();
	
	// assign the new body to the official body for the mesh
	theBody = newBody;
	
	// empty out the new body
	newBody.clear();
	
	// update mesh labelling based on this 
	updateMeshLabels();
	
	
}

// Function made to group together vertices into body parts
// Will read the labels of the vertices and decide which body part to put this vertice into
// Will result in the variable 'theBody' being populated with BodyPart entries
void Mesh::formBodyParts()
{
	// empty theBody if it is not empty
	theBody.clear();
	
	//	read over all the vertices that are present
	for (int aCoordinate = 0; aCoordinate<numberOfVertices; aCoordinate++)
	{
		
		// locate the index of the part if there is a part in the body corresponding to the label of vertice
		int partIndex = getLocalPart(verticeLabels[aCoordinate]);
		
		// if part exists in the body then insert this point into that part
		if (partIndex >= 0 )
		{
			
			theBody[partIndex].insertPoint(verticeCoordinates[aCoordinate],aCoordinate);		
		}
		// otherwise make a new body part that has the label of this vertice
		else
		{
			BodyPart newPart(verticeLabels[aCoordinate]);
			
			std::cout<<"Creating: "<<verticeLabels[aCoordinate]<<std::endl;
			
			// insert the vertice into the part
			newPart.insertPoint(verticeCoordinates[aCoordinate],aCoordinate);
			
			// insert the part into the body
			theBody.push_back(newPart);
		}
	
	}


}


// Function for locating the index of a BodyPart in the container specified for the BodyPart type object
int Mesh::findBodyPart(std::string partName,std::vector<BodyPart> aBody) 
{
	int currentPart = 0;
	bool found = false;
	
	// removed for loop and replaced with while to speed up 
	while (currentPart< aBody.size() && found==false)
	{
		if (aBody[currentPart].getName() == partName)
		{
			return currentPart;
		}
		currentPart++;
	}
	
	return -1;
}


// Default printing function for Mesh
// Will print based on Body Parts
// Can be modified to give more details
// Can be associate with existing file writer to write a file on the mesh
// Will output the name
// Will output the number of Vertices in this Part
void Mesh::print()
{
	std::cout<<"Mesh Body Parts: "<<theBody.size()<<std::endl;
	
	for (int aPart = 0; aPart<theBody.size();aPart++)
	{
		std::cout<<"Name: "<<theBody[aPart].getName()<<std::endl;
		std::cout<<"Total Vertices: "<<theBody[aPart].getNumberOfVertices()<<std::endl<<std::endl;
		
	}

}


// One of the Key Contributions of this module
// Corrects incorrect labelling of joint
// if joint is not completely labelled e.g. knee joint inital labelling
// this can correct it and make cylinderical labels for a surface label
// joint axis denotes the axis along which this joint is located as a surface (biggest axis it spans?)
void Mesh::fixJoint(std::string jointName, std::string jointAxis)
{
	// obtaining BodyPart Index
	int partIndex = getLocalPart(jointName);
	
	if (partIndex>=0)
	{
		// choice represents the axis along which this joint will be made cylinderical
		int choice = getChoice(jointAxis);
		
		// obtaining the min and max along which this is present as a surface
		
		float minJoint = theBody[partIndex].getMin(jointAxis);
		float maxJoint = theBody[partIndex].getMax(jointAxis);
		
		// Figuring out if it is a left joint or a right joint 
		// this is so only relevant parts are compared
		std::string jointSide =  jointName.substr(0,int(jointName.find_first_of("-"))-1);
				
		
		// is a counter of the number of parts added
		int counterFixed = 0;
		
		// reading based on part
		for (int aPart = 0; aPart < theBody.size(); aPart++)
		{
			// if the part is on the correct side (left or right based on what side the joint is on)
			if (int(theBody[aPart].getName().find(jointSide)) >=0)
			{
				// obtaining the part
				BodyPart currentPart = theBody[aPart];
				
				// storing the parts that will be removed from this part
				std::vector<int>  toRemove;
				
				// reading all the vertices of this part to see which coordinates to add
				for (int aPoint = 0; aPoint < currentPart.getNumberOfVertices();aPoint++)
				{
					// if the coordinates lies within the limit that we obtained for min and max
					if (currentPart.getCoordinate(aPoint)[choice]>=minJoint && currentPart.getCoordinate(aPoint)[choice]<=maxJoint)
					{
						// then insert it into the part
						theBody[partIndex].insertPoint(currentPart.getCoordinate(aPoint),currentPart.getVertexIndex(aPoint));
						
						// add the vertex index from this part (local index)
						toRemove.push_back(aPoint);
						
						// update the counter
						counterFixed++;
						
					}
					
				}
				// remove counter is used to adjust the local indices of the verticec
				int removeCounter = 0;
				
				// erasing the points from the currentPart that were added to the joint that is being fixed
				for (int eraseData = 0; eraseData<toRemove.size();eraseData++)
				{
					// removeCounter is indicating that once a vertex has been removed all other vertice indices decrease too
					theBody[aPart].removePoint(toRemove[eraseData]-removeCounter);
					// remove counter incremented once part is removed
					removeCounter++;
				}
				
			}
		}
		// indcates the total number of Vertices that are now in this part
		std::cout<<"Points Fixed: "<<counterFixed<<std::endl;
		
		//  update the global mesh array
		updateMeshLabels();
	}
	else
	{
		std::cout<<"Incorrectly Specified Mesh\n";
	}
}


// Key function for this module
// Is used to add a joint between any two specified joints
// joint above name is the name of the joint that is closer to the body
// joint below name is the name of the joint that is farther from the body
// weightage corresponds to how much part of each joint as it is should become part of new joint (decimal number between 0 and 1)
// new joint name is the name to be given to the new joint
// a joint can only be added if both joints lie along the same major axis
void Mesh::addJoint(std::string jointAboveName,std::string jointBelowName, float weightage,std::string newJointName)
{
		// locating the index of the joint above
		int firstJoint = getLocalPart(jointAboveName);
		
		// locating the major axis
		std::string firstJointAxis = theBody[firstJoint].getMajorAxis();
				
		// locating the index of the joint below
		int secondJoint = getLocalPart(jointBelowName);					
		
		// locating the major axis
		std::string secondJointAxis = theBody[firstJoint].getMajorAxis();
		
		// if both the joints lie along the same major axis then proceed
		if (firstJointAxis.compare(secondJointAxis)==0)
		{
			// Parts are a match for joint addition
			
			// first joint defines the joint that is closer to the body and less close to the extreme ends
			// second joint defines the joint that is closer to the extreme ends of the character but less close to the body.
			
			// obtain minima and maxima for jointAbove
			float firstJointMin = theBody[firstJoint].getMin(firstJointAxis);
			float firstJointMax = theBody[firstJoint].getMax(firstJointAxis);
			
			// obtain minima and maxima for jointBelow
			float secondJointMin = theBody[secondJoint].getMin(secondJointAxis);
			float secondJointMax = theBody[secondJoint].getMax(secondJointAxis);
			
			// Obtain the length of each joint
			float firstJointLength = firstJointMax-firstJointMin;
			float secondJointLength = secondJointMax - secondJointMin;
			
			// Determining new Joint min and max values along the major axis
			float newJointMin = 0;
			float newJointMax = 0;
			
			// direction specifies which side of the body are the body parts to be looked at for updating this joint
			std::string direction="";
			
			if (int(newJointName.find("Left"))>=0)
			{
				// if it is on the left side. The first joint minimum corresponds to the end of the first joint, that is adjacent to the beginning of the second joint.
				// also since it has a negative value (left side) then we add the weightage to bring the minima of the first joint closer to the body to leave room for the new joint
			
				// if it is on the left side. The second joint maximum corresponds to the beginning of the second joint, that is adjacent to the end of the first joint.
				// also since it has a negative value (left side) then we subtract the weightage to bring the maxima of the second joint farther from the body to leave room for the new joint
				
				// determining the new joint based on weightages given
				newJointMax = firstJointMin + weightage*firstJointLength;
				newJointMin = secondJointMax - weightage*secondJointLength;

			
				direction = "Left";
			}
			else if (int(newJointName.find("Right"))>=0)
			{
				// if it is on the right side. The first joint maximum corresponds to end of the first joint, the joint that is adjeacent to the beginning of the second joint
				// also since it has a postive value (right side) then we subtract the weightage to bring the maxima of the first joint closer to the body to leave room for the new joint
			
				// if it is on the right side. The second joint minima corresponds to the beginning of the second joint, that is adjacent to the end of the first joint.
				// also since it has a positive value (right side) then we add the weightage to bring the minima of the second joint farther from the body to leave room for the new joint
				
				newJointMin = firstJointMax -  weightage*firstJointLength;
				newJointMax = secondJointMin + weightage*secondJointLength;
			
				direction = "Right";
			}
			
			int choice = getChoice(firstJointAxis);
			// get the choice value for search
			
			int counterPoint = 0;
			BodyPart newJoint(newJointName);
			
			std::cout<<"Direction: "<<direction<<std::endl<<"Choice: "<<choice<<std::endl;
			
			for (int checkPart = 0; checkPart< theBody.size(); checkPart++ )
			{
				// if the part to be considered is on the correct side of the mesh				
				if (int(theBody[checkPart].getName().find(direction))>=0)
				{
					// making a container to contain the points to remove from the current body part
					std::vector<int> toRemove;
					
					// identifying the new joint direction to base computations on
					if (direction.compare("Left")==0)
					{
						// begin checking for all coordinates of this joint and see if any of them belong to this new joint
						for (int checkCoordinate =0;checkCoordinate<theBody[checkPart].getNumberOfVertices();checkCoordinate++)
						{
							// condition based on which a point can be part of the new joint
							// condition is dependant on whether this is a right side joint or left side joint
							if (theBody[checkPart].getCoordinate(checkCoordinate)[choice] <newJointMax && theBody[checkPart].getCoordinate(checkCoordinate)[choice] > newJointMin)
							{
								// inserting the point into the new joint
								newJoint.insertPoint(theBody[checkPart].getCoordinate(checkCoordinate),theBody[checkPart].getVertexIndex(checkCoordinate));
								
								// incrementing the counter for the new joint
								counterPoint++;
								
								// adding the local index of the joint in the current part to the toRemove container so that it can be removed from this part
								toRemove.push_back(checkCoordinate);
							}
						}
					}
					// identifying the new joint direction to base computations on	
					else if (direction.compare("Right")==0)
					{
						// begin checking for all coordinates of this joint and see if any of them belong to this new joint
						for (int checkCoordinate =0;checkCoordinate<theBody[checkPart].getNumberOfVertices();checkCoordinate++)
						{
							// condition based on which a point can be part of the new joint
							// condition is dependant on whether this is a right side joint or left side joint
							if (theBody[checkPart].getCoordinate(checkCoordinate)[choice] >newJointMin && theBody[checkPart].getCoordinate(checkCoordinate)[choice] < newJointMax)
							{
								// inserting the point into the new joint
								newJoint.insertPoint(theBody[checkPart].getCoordinate(checkCoordinate),theBody[checkPart].getVertexIndex(checkCoordinate));
								
								// incrementing the counter for the new joint
								counterPoint++;
								
								// adding the local index of the joint in the current part to the toRemove container so that it can be removed from this part
								toRemove.push_back(checkCoordinate);
							}
						}
					}
					
					// variable to update the local vertice indexes upon removal
					int counterErased= 0;
					// begin removing the vertices that no longer belong to the current part
					for (int eraseOld = 0; eraseOld<toRemove.size();eraseOld++)
					{
						// counterErased indicaes the factor to decrease the index by based on prior vertice removals in this session
						theBody[checkPart].removePoint(toRemove[eraseOld]-counterErased);
						
						// incrementing the counter erased because another point was just removed
						counterErased++;
					}					
					// emptying the remove container so this operation can be repeated with this same variable for another BodyPart
					toRemove.clear();
					
				}
			
			}
			
			// inserting the new body part into theBody
			theBody.push_back(newJoint);
			
			// informing the user of the status of this part
			std::cout<<"New Joint Name: "<<newJoint.getName()<<std::endl<<"New Joint Vertices: "<<newJoint.getNumberOfVertices()<<std::endl;
			
		}
		
		// updating the mesh labels to correspond to the changes that have just been made
		updateMeshLabels();
}

// An internal function to be used for obtaining the choice of coordiantes based on axis specifiication
// input must refer to axis X Y or Z
// in case of incorrect input will return -1 which will result in memory error
int Mesh::getChoice(std::string axis)
{
	if (axis.compare("X")==0)
	{
		return 0;
	}
	else if (axis.compare("Y")==0)
	{
		return 1;
	}
	else if (axis.compare("Z")== 0)
	{
		return 2;
	}
	else
	{
		std::cout<<"Incorrectly Specified axis\n";
		return -1;
	}
}

// a local function that is used to center the entired mesh
// means for the mesh must be set before this can be called
// means can be obtained from the simple instance reader that is part of this class after a reading of coordinates
// results in a structure centered about (0,0,0)
void Mesh::meanSubtractCoordinates()
{
	for (int aCoordinate = 0; aCoordinate < numberOfVertices;aCoordinate++)
	{
		verticeCoordinates[aCoordinate][0] = verticeCoordinates[aCoordinate][0] - completeMeanX;
		verticeCoordinates[aCoordinate][1] = verticeCoordinates[aCoordinate][1] - completeMeanY;
		verticeCoordinates[aCoordinate][2] = verticeCoordinates[aCoordinate][2] - completeMeanZ;
	}
}

// A Key contribution of this module
// Allows us to label meshes of same scale and orientation with labels based on labelling of another mesh
// must be provided the coordinates of the external mesh 
// must be provided the labelling of the external mesh
void Mesh::loadLabels(std::vector< std::vector<float> > externalMeshCoordinates, std::vector<std::string> externalMeshLabels)
{	
	std::cout<<"Commencing Loading Labels\n";
	std::cout<<"Matching Coordinates, This may take a few minutes\n";
	// this is the distance of a point in this mesh from another point on the external mesh
	// minimality of this point is used to determine the label of the current point being considered
	float newDistance = 0;
	
	// testing the coordinates from  the current mesh for finding their correct labels
	for (int aCoordinate = 0;aCoordinate<numberOfVertices; aCoordinate++)
	{
		// assigning a huge minimum distance so any real point to point distance over rides it
		float minDistance = 1000;
		
		// defining a container for the minimum index
		int minIndex = 0;
		
		// looping over all the external coordinates to see which one corresponds to the correct coordinate
		for (int externalCoordinate = 0; externalCoordinate < externalMeshCoordinates.size(); externalCoordinate++)
		{
			
			// computing the distance for this particular set of points
			 newDistance = computeDistance(externalMeshCoordinates[externalCoordinate],verticeCoordinates[aCoordinate]);
			 
			
			 // comparing with the existing minimum to see if a better match has been found for the point
			if (minDistance > newDistance )
			{
				// updating the distance and the index of the best match from the external mesh
				minDistance = newDistance;
				minIndex = externalCoordinate;
			}
		
		}
		
		// informing the user of the matching that is being performed
		//std::cout<<aCoordinate<<"  Of  " << numberOfVertices <<" matches to " << minIndex<<std::endl;
		
		// adding the correct label to this mesh's structure based on the one the best match has in the external
		verticeLabels[aCoordinate] = externalMeshLabels[minIndex];
	}
	
	// emptying out the external mesh data
	externalMeshCoordinates.clear();
	externalMeshLabels.clear();
	
	// forming body parts based on newly assigned labels
	formBodyParts();

}


// function for computing the euclidean distance between two points
// both points must have three dimensions
// distance is always positive
// if invalid coordinate dimensions given then result is a -1
float Mesh::computeDistance(std::vector< float> coordinateA, std::vector< float> coordinateB)
{

	if (coordinateA.size()==3 && coordinateB.size()==3)
	{
		float distance = sqrt(pow(coordinateA[0]-coordinateB[0],2) + pow(coordinateA[1]-coordinateB[1],2) + pow(coordinateA[2]-coordinateB[2],2));
		return distance;
	}
	else
	{
		std::cout<<"Invalid coordinate Dimensions\n";
		return -1;
	}
}

// Standard accessor to obtaining mesh coordinates
// will return mesh coordinates as mean subtracted
// mean subtraction is done initially on loading
std::vector< std::vector<float> > Mesh::getCoordinates()
{
	return verticeCoordinates;
}

// Standard Accessor for obtaining Labels for all ther vertices of the mesh
// will return labels mimicking any fixes to joints and addition of joints
std::vector<std::string> Mesh::getLabels()
{
	return verticeLabels;
}

// Function for loading coordinates to a mesh created through the standard Constructor
// will load coordinates and set other coordinate related attributes
void Mesh::loadCoordinates(std::string pathCoordinates)
{
	// emptying any existing coordinates that existed so that fresh coordinates can be loaded with correct indexing
	verticeCoordinates.clear();
	
	// loading new coordinates
	verticeCoordinates = initializer.readCoordinates(pathCoordinates);
	
	// loading the new means
	std::vector<float> theMeans  = initializer.getMean();
	completeMeanX = theMeans[0];
	completeMeanY = theMeans[1];
	completeMeanZ = theMeans[2];
	
	// loading the new value of number Of coordiantes
	numberOfVertices = verticeCoordinates.size();
	
	pathCoordinatesFile = pathCoordinates;
	
	// emptying the container
	theMeans.clear();
}

// Fucntion for loading the faces
// empties the existing faces data
// also sets related atttributes
void Mesh::loadFaces(std::string pathFaces)
{
	// emptying the faces data
	faces.clear();
	
	// reading the faces
	faces = initializer.readFaces(pathFaces);
	
	// setting the number of faces
	numberOfFaces = faces.size();
	
	// setting the path to the file used for reading
	pathFacesFile = pathFaces;
}

// funny function name
// Obtains the mean for the entire mesh
// for the axis specified
// if axis is not correct returns error on promt and zero
float Mesh::getMean(std::string axis)
{
	// comparing axis specidied to obtain the correct mean
	if (axis.compare("X")==0)
	{
		return completeMeanX;
	}
	if (axis.compare("Y")==0)
	{
		return completeMeanY;
	}
	if (axis.compare("Z")==0)
	{
		return completeMeanZ;
	}
	else
	{
		std::cout<<"Error in axis specification \n";
		return 0;
	}
}

// Standard accessor for the faces data of the mesh
// will return the faces with any modifications that you made
std::vector< std::vector<int> > Mesh::getFaces()
{
	return faces;
}

// Standard Accessor for the path names for the files used to load data
// Index zero contains path to coordinates file
// Index one contains path to labels file
// Index two  contains path to faces file
std::vector<std::string> Mesh::getPaths()
{
	std::vector<std::string> thePaths;
	thePaths.push_back(pathCoordinatesFile);
	thePaths.push_back(pathLabelsFile);
	thePaths.push_back(pathFacesFile);
	
	return thePaths;	
}

// Standard Accessor for the BodyPart based definition of the mesh
// Returns the current BodyPart repesentation of the mesh
// All changes made through add joint and fix joint are present in the BodyPart vector returned
std::vector<BodyPart> Mesh::getBody()
{
	return theBody;
}

// Internal function for mimicking the changes in the global mesh labels corresponding to any BodyPart based changes
// used internally after modifications to any BodyPart lables to update the changes in the global mesh labels
void Mesh::updateMeshLabels()
{
	// read a BodyPart
	for (int writePart = 0; writePart<theBody.size();writePart++)
	{
		// obtain its name
		std::string currentPartName = theBody[writePart].getName();
		
		// commence writing the name on every location corresponding to the global Mesh Index for the Body Part Vertices
		for (int aPoint = 0; aPoint < theBody[writePart].getNumberOfVertices();aPoint++)
		{		
			verticeLabels[theBody[writePart].getVertexIndex(aPoint)] = currentPartName;
		}
		
	}

	std::cout<<"Mesh Updated\n";
}

// standard function for looking up the index of a BodyPart in 'theBody' container
// will return -1 and an error on the prompt
// no for loop to speed up process 
int Mesh::getLocalPart(std::string partName)
{
	int currentPart = 0;
	bool found = false;
	
	// removed for loop and replaced with while to speed up 
	while (currentPart< theBody.size() && found==false)
	{
		if (theBody[currentPart].getName() == partName)
		{
			return currentPart;
		}
		currentPart++;
	}
	
	return -1;

}