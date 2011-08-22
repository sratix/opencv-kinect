#ifndef _EXPLORE_H_
#define _EXPLORE_H_

#include <string>
#include <vector>

#include <fstream>
#include <dirent.h>
#include <cstring>

#include <iostream>

#include "simplewriter.h"


class Explore
{
	// Class is designed to explore all the subdirectories of any parent directory for files
	// Is very useful in obtaining list of different files of same type to be used for batch processing a datasets
	private: 
		// Variables used by the class include
		// 1- initialPath denotes the root directory whose contents we would like to search
		// 2- directoryMap is a container of all the directories that are contained in the parent directory and its subdirectories
		// 3- fileMap is a container for all the files that are contained within  this directory and all its subdirectories
		// 4- numberOfFiles read is a container of the number of Files in the directory and all its sub directories
		// 5- fileWriter is a writer for simple files used to output details to a file for later reading
		
		std::string initialPath;	

		std::vector<std::string> fileMap;
		std::vector<std::string> directoryMap;
		
		int numberOfFilesRead;
		int numberOfDirectoriesRead;
		
		SimpleWriter fileWriter;
		
		// Internal functions
		
		// Main function for reading
		void readDirectory(std::string currentDirectoryPath);
		
		// Determines if the current entry being read is a directory or not
		bool isDirectory(std::string directoryPath);
		
		
	public:
	
		// Constructor
		Explore(std::string rootDirectory);
		
		// Destructor
		~Explore();
		
		// Obtain List Methods
		std::vector<std::string> getFilesList(std::string extension,std::string writePath = "");
		std::vector<std::string> getDirectoriesList(std::string writePath = "");
		
		// Read another Directory
		void readNewDirectory(std::string newPath);
		
		
};
#endif
