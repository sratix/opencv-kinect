#include "explore.h"

// Non-Standard Constructor for the class
// Input Argument is the path to the root directory
// Sets initial values
// Performs a read on Initalization
Explore::Explore(std::string rootDirectory)
{
		initialPath = rootDirectory;
		numberOfFilesRead = 0;
		numberOfDirectoriesRead = 0;
		readDirectory(initialPath);
}

// standard Destructor for class
Explore::~Explore()
{
	std::cout<<"Clearing Memory Allocated\n";
	directoryMap.clear();
	fileMap.clear();
}

// Function for verifying that the path given does not belong to a file
// Based on assumption that all files have an extension
// input is the complete path to a directory
// function returns True if path provided does not contain a file extension
bool Explore::isDirectory(std::string directoryPath)
{
	// Obtaining the location of the directory name
	int locationDirectoryName = int(directoryPath.find_last_of("\\"));
	
	// Obtaining the directory Name
	std::string directoryName = directoryPath.substr(locationDirectoryName+1);
	
	// obtaining location of Extension in Directory Name
	int findExtension = int(directoryName.find("."));
	
	if (findExtension >= 0 )
	{
		// if location found within the string return false
		return false;
	}
	else
	{
		// else return true
		return true;
	}
	
}

// Function for using same reader to read a different directory
// path to new directory is to be provided
// will update all storage structures
void Explore::readNewDirectory(std::string newPath)
{
	directoryMap.clear();
	fileMap.clear();
	numberOfFilesRead = 0;
	numberOfDirectoriesRead = 0;
	
	initialPath = newPath;
	
	readDirectory(newPath);
}


// Function for obtaining a list of files with a specific extension
// Is provided with an extension of the form of 'exe' or 'bvh' or 'coords'
// Returns a vector of strings containing paths to the files with that extension in the specified directory
std::vector<std::string> Explore::getFilesList(std::string extension,std::string writePath)
{

	// will contain the finalised paths list
	std::vector<std::string> requiredFile;

	if (extension.compare("*")!=0)
	{
		// Variables defined at start to prevent re declaration of Variables and save memory reads
		
		// Initialization of filePath for every Consequent file to be analyzed as empty string
		// to be set  for each string in the for loop
		std::string filePath = "";
		
		// Initialization of location 
		// Set to -1 to indicate no location exists at start
		int location = -1;
		
		// Initialization of fileExtension for every Consequent file to be analyzed as empty string
		// to be set  for each string in the for loop
		std::string fileExtension = "";
		
		// commencing search for required files
		for (int findFiles = 0; findFiles<numberOfFilesRead; findFiles++)
		{
			// code for finding correct extension is in here
			
			// obtain filePath
			 filePath = fileMap[findFiles];
			
			// locate file Extension 
			 location = int(filePath.find_last_of("."));
			
			// read extension		
			 fileExtension = filePath.substr(location+1);			
			
			// compare extension
			if ( fileExtension.compare(extension) == 0)
			{			
				requiredFile.push_back(filePath);
			}
		}
	}
	else
	{
		requiredFile = fileMap;
	}
	
	if (writePath.compare("")!=0)
	{
		fileWriter.writeFile(writePath,requiredFile);
	}
	
	// returning the required files.
	return requiredFile;
}

// Function for obtaining the list of all sub folders in the folder specified
// will return a vector for strings
// if write path is specified it will write the directoryMap to the path specified
// write path must contain a file name
std::vector<std::string> Explore::getDirectoriesList(std::string writePath)
{
	if (writePath.compare("")==0)
	{
		return directoryMap;
	}
	else
	{
		fileWriter.writeFile(writePath,directoryMap);
		return directoryMap;
	}
}

// Main Function defined for reading the contents of a directory
// Uses dirent and DIR* as they are cross platform compatible
// Input is the path to the parent folder that needs to be read for content
// Data read is stored in directoryMap (a class variable)
void Explore::readDirectory(std::string currentDirectoryPath)	
{		
	if (isDirectory(currentDirectoryPath))
	{
	
		// Defining the Variables that will be used in reading
	
		// a Pointer to the current Directory
		DIR *currentDirectory;	
	
		// a Pointer to the current File
		struct dirent *currentFile;	
    
		// opening a Directory, this is the parent directory specified
		currentDirectory =opendir (currentDirectoryPath.c_str());	
		
		// if this is not a directory but just a file then back out right from here
       	if (currentDirectory != NULL)	
        {
		
			// Assigning an Entry by Reading an instance of some object in the directory
			while ( currentFile = readdir (currentDirectory) )	
			{                  
				// storing the current File entries name
				std::string fileName = currentFile->d_name;
				
				// testing if the new instance read is a directory or not by constructing a fileName with this
				std::string newDirectoryPath = currentDirectoryPath+"\\"+fileName;
				
				// making sure non existent directories are not entered
				if ( ( strcmp(currentFile->d_name,".") ) && ( strcmp (currentFile->d_name,"..") ) ) 	
				{					
					// If the new instance read is a directory then enter it and read its contents first
					if (isDirectory(newDirectoryPath))
					{	
						// Recursive Call
						directoryMap.push_back(newDirectoryPath);
						numberOfDirectoriesRead++;
						readDirectory(newDirectoryPath);			
					}
					else
					{
						// if new instance is afile, just enter it in the File Map
						fileMap.push_back(newDirectoryPath);
						numberOfFilesRead++;					
					}
					
                }
				
			// continues with the reading of other instances of this Folder
            }
			
		// closing the current open Directory after all its contents have been read
        (void) closedir (currentDirectory);		
        }	
		
	}
	else
	{
		std::cout<<"Path given points to a file not a directory\n";
	}
}	
