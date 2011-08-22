#include "SimpleReader.h"

// Default constructor for the class.
// Everything is set to zero
SimpleReader::SimpleReader()
{
	// The Means are all set to Zero
	completeMeanX = 0;
	completeMeanY = 0;
	completeMeanZ = 0;
	
	numberOfVertices = 0;
}


// Standard destructor for the class
// Closes any open streams
SimpleReader::~SimpleReader()
{
	aFileReader.close();
}

// Reader function for reading Coordinates
// Input variable is used to define the complete path and file name to the file containing the Coordinates.
// Should have the extension .coords
// Is a file output by the Python Scripts 
std::vector<std::vector<float> > SimpleReader::readCoordinates(std::string filePath)
{
	// ensuring no prior mean is present
	completeMeanX = 0;
	completeMeanY = 0;
	completeMeanZ = 0;

	// ensuring number of vertices are zero so no prior bias in mean
	numberOfVertices = 0;
	
	// Initializing the container for storing the coordinates
	// All Entries are of type vector<float>
	std::vector< std::vector <float > > theCoordinates;
	
	if ( filePath.substr( int( filePath.find_last_of(".") ) ).compare(".coords") ==0)
	{
		
		// Opening the file to be read
		aFileReader.open(filePath.c_str());
		
		if (aFileReader.is_open())
		{	
			// Current Line read from the file
			// Default initialized to empty string
			std::string currentLine = "";
			
			// The first reading of a Line is for obtaining the number of entries in the file 
			getline(aFileReader,currentLine);
			numberOfVertices = atoi(currentLine.c_str());
			
			std::cout<<"Number of Coordinates to Read: "<<numberOfVertices<<std::endl;
			
			// Initializing the container for storing a single Coordinate
			// All Entries must be of type float
			std::vector<float> aCoordinate;
			
			// Standard Variables for tokenization	
			char* tokens;
			char* theLine;	
			
			// Commencing Reading for the Vertices
			for (int aVertex = 0 ; aVertex < numberOfVertices; aVertex ++)
			{
				// Reading a Line containing the Coordinates
				// Coordinates are separated by Spaces
				getline(aFileReader,currentLine);			
						
				// Copying the Line into a character pointer so that it can be tokenized
				theLine = new char [currentLine.size()+1];
				strcpy (theLine, currentLine.c_str());
							
				// Creating tokens based on space
				tokens = strtok (theLine," ");
				
				// Standard code for tokenization
				while (tokens != NULL)
				{
					aCoordinate.push_back(atof(tokens));
					tokens = strtok (NULL, " ");
				}
				
				// Uncomment these lines to see what the stream is reading if there is some bug in reading
				//std::cout<<"Reading: "<<aCoordinate[0]<<" "<<aCoordinate[1]<<" "<<aCoordinate[2]<<" on vertex "<<aVertex<<std::endl;
				
				// Inserting coordinates
				theCoordinates.push_back(aCoordinate);
				
				
				// Updating Mean
				// aVetex is used to adjust weightages (standard procedure)		
				completeMeanX = ((completeMeanX*aVertex )+ aCoordinate[0])/(aVertex+1);
				completeMeanY = ((completeMeanY*aVertex )+ aCoordinate[1])/(aVertex+1);
				completeMeanZ = ((completeMeanZ*aVertex )+ aCoordinate[2])/(aVertex+1);
				
				// Clearing the aCoordiante (Vital otherwise values will be added to existing coordinates and we will read same values over and over again)
				aCoordinate.clear();
			
				// De allocating memory space allocated to character pointers
				free(tokens);
				free(theLine);
			
			}			
			// Closing the open Stream
			aFileReader.close();
			
		}
		else
		{
			std::cout<<"Incorrect Path Entered!\n";
		}	
	}
	else
	{
		std::cout<<"Incorrect File Type!\n";
	}
	// returning the coordinates
	return theCoordinates;	
}

// Reader function for reading Labels for the Vertices
// Input variable is used to define the complete path and file name to the file containing the Labels.
// File must have exactly same number of lables as there are coordintes
// Should have the extension .labels
// Is a file output by the Python Scripts 
// The output Variable is a Vector of Strings
std::vector< std::string > SimpleReader::readLabels (std::string filePath)
{
	std::cout<<"Reading Labels\n";
	
	// Initializing the container for storing the vertex Labels
	// All Entries are of type string
	std::vector< std::string > theLabels;		
		
	// verifying to make sure that the file type is correct
	if (filePath.size()!=0 && filePath.substr( int( filePath.find_last_of(".") ) ).compare(".labels") == 0 )
	{
	
		// Opening Input Stream with the path given for the file
		aFileReader.open(filePath.c_str());
		
		// Verifying if the file is open or not
		if (aFileReader.is_open())
		{
			// Current Line read from the file
			// Default initialized to empty string
			std::string currentLine = "";
		
			// The first reading of a Line is for obtaining the number of entries in the file 
			getline(aFileReader,currentLine);
			
			// Verifying that the there is a label corresponding to every Vertex read
			if (numberOfVertices== atoi(currentLine.c_str()) )
			{
				// Informing User of commencing reading
				std::cout<<"Will Read Labels: "<<numberOfVertices<<std::endl;

				// Commencing Reading of file Labels
				for (int aVertex = 0 ; aVertex < numberOfVertices; aVertex ++)
				{
					// Reading a Line containing the Coordinates
					// Coordinates are separated by Spaces
					getline(aFileReader,currentLine);				
					
					// Entering the labels in the container for them
					theLabels.push_back(currentLine);		
				}
			}
			else			
			{
				std::cout<<"The File opened does not contain the correct Number Of Labels\n";
			}
		
		// Closing the input stream
		aFileReader.close();
		}
		else
		{
			std::cout<<"File entered does not exist\n";
		}				
	}
	else
	{
		std::cout<<"Incorrect File Type\n";
	}
	
	// return the required variable
	return theLabels;	
}

// Reader function for reading Faces for the Vertices
// Input variable is used to define the complete path and file name to the file containing the Faces
// Should have the extension .faces
// Is a file output by the Python Scripts 
// Output Variable is a Vector of Vector Integeres
// The Inner Vector Integers will be of size 4
std::vector< std::vector<int> > SimpleReader::readFaces(std::string filePath)
{
	// Initializing the container for storing the vertex Labels
	// All Entries are of type vector<int>
	std::vector< std::vector <int > > theFaces;	
	
	if ( filePath.substr( int( filePath.find_last_of(".") ) ).compare(".faces") ==0)
	{
		// Opening Input Stream with the path given for the file
		aFileReader.open(filePath.c_str());
		
		// Verifying if the file is open or not
		if(aFileReader.is_open())
		{	
			// Current Line read from the file
			// Default initialized to empty string
			std::string currentLine = "";
						
			// The first reading of a Line is for obtaining the number of entries in the file 
			getline(aFileReader,currentLine);
			
			// This is not stored in the class variabls as there is no neeed for a comparison
			int totalFaces = atoi(currentLine.c_str());
			
			std::cout<<"Will Read Faces: "<<totalFaces <<std::endl;
			
			// Standard Variables for tokenization	
			char* tokens;
			char* theLine;			
			
			// The container for a Face
			// Contains 4 entries of type int as meshes are made of quadilaterals		
			std::vector<int> aFace;
			
			// Commencing Reading for file
			for (int  currentFace = 0 ; currentFace < totalFaces; currentFace ++)
			{
				// Reading a Line containing the Faace
				// Indices are separated by Spaces
				getline(aFileReader,currentLine);			
			
				
				// Standard Tokenization Procedure
				// Convert the Line to a 
				theLine = new char [currentLine.size()+1];
				strcpy (theLine, currentLine.c_str());
				
				// toeknization is done on basis of space character
				tokens = strtok (theLine," ");
				while (tokens != NULL)
				{
					// Inserting the face index in the Face
					aFace.push_back(atoi(tokens));
					tokens = strtok (NULL, " ");
				}
				
				// Uncomment Code to see what the faces reader is picking up
				// Will be useful in debugging
				//std::cout<<"Face "<<currentFace<<" : "<<aFace[0]<<" "<<aFace[1]<<" "<<aFace[2]<<" "<<aFace[3]<<std::endl;
				
				// Inserting a face into the container for all the faces
				// Should Only be a face of size 4
				
				theFaces.push_back(aFace);
				
				// emptying aFace container so that it can be used again without redeclaration of variable.
				aFace.clear();
				
				// releasing Variables allocated memory for tokenization
				free(tokens);
				free(theLine);
			
			}
			
			// Closing the open Stream 
			aFileReader.close();
		}
		else
		{
			std::cout<<"Incorrect File Name or Path\n";
		}
	}
	else
	{
		std::cout<<"Incorrect File type\n";
	}
	
	// Returning the Faces
	return theFaces;
	
}

// Reader function for reading Mapping
// A Mapping is a file that is used to reduce the number of labels by defining the constituents of a group.
// Input variable is used to define the complete path and file name to the file containing the Mapping File
// Should have the extension .reduce
// Is a file Written by the User or modified over the template provided
// Output is a vector of Vector Strings
// The Inner Vector Strings can be of variable size
std::vector< std::vector<std::string> > SimpleReader::readMapping(std::string filePath)
{
	// Variable defined to store the mapping
	std::vector< std::vector <std::string > > theMapping;	
	
	// checking if file type is valid or not
	if ( filePath.substr( int( filePath.find_last_of(".") ) ).compare(".reduce") ==0)
	{
		// Opening Stream to file
		aFileReader.open(filePath.c_str());
		
		// Verifying if the file is correcct or not
		if (aFileReader.is_open())
		{
			// Current Line read from the file
			// Default initialized to empty string
			std::string currentLine = "";
			
			// The first reading of a Line is for obtaining the number of entries in the file 
			getline(aFileReader,currentLine);
			
			// Not stored in class variables as there is no future need for this data.
			int totalMaps = atoi(currentLine.c_str());
			
			std::cout<<"Will Read: "<<totalMaps<<std::endl;
			
			// Standard Variables to be used for tokenization
			char* tokens;
			char* theLine;
			
			// Container defined to hold the reduction commands
			// input entries must be of type string and can be 3 or 4
			std::vector<std::string> aMapping;
			
			for (int currentMapping = 0 ; currentMapping < totalMaps; currentMapping ++)
			{
				getline(aFileReader,currentLine);			
			
				
			
				theLine = new char [currentLine.size()+1];
				strcpy (theLine, currentLine.c_str());
				
				// Standard tokenization code based on comma character
				tokens = strtok (theLine,", ");
				while (tokens != NULL)
				{
					// inserting mapping 
					aMapping.push_back(tokens);
					tokens = strtok (NULL, ", ");
				}
				
				// Inserting aMapping into the vector
				// aMapping is a variable sized command / mapping definition
				// May have size 3 or 4 depending on direct or divided mapping
				theMapping.push_back(aMapping);
				
				// emptying the container aMapping that was used to insert a Mapping into the file
				aMapping.clear();
			
				// Releasing the memory assiged to the variables during tokenization
				free(tokens);
				free(theLine);
			}
			
			
			// Closing the open input stream
			aFileReader.close();
		}
		else
		{
			std::cout<<"File Specified does not Exist\n";
		}
	}
	else
	{
		std::cout<<"Incorrect File Extension\n";
	}
	return theMapping;	
}

// Function Defined to obtain the mean of the Coordinates that were read
// means are returned in the following order X Y Z
std::vector<float> SimpleReader::getMean()
{
	// create a container for the means
	std::vector<float> means;
		
	means.push_back(completeMeanX);
	means.push_back(completeMeanY);
	means.push_back(completeMeanZ);
	
	return means;
	

}