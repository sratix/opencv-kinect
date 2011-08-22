#include "explore.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

int main()
{
	// sample program to demonstrate the functionalities of the module

	// make a constructor with the filePath
	Explore findVideos("E:\\OldDesktop\\UniquePosesFromEntireCMUMocap");
	
	// Obtain a list of bvh files in this directory
	std::vector<std::string> bvhFiles = findVideos.getFilesList("bvh","D:\\PathsOfFiles.txt");
	
	// show to the user the number of bvhFiles
	std::cout<<"Found Files: "<< bvhFiles.size() <<std::endl;
	
	
	
	
	

}