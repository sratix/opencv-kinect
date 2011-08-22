#include "SimpleWriter.h"

// Default constructor for the class
// Does not contain any initializations
SimpleWriter::SimpleWriter()
{
	// empty Constructor
}


// Function for writing the file containing Coordinates
// Input is a vector of a vector float type
// Output file is a with the first line containing the number of entries
// in the following lines are to coordinates one per line
// each coordinate is separated by a space
void SimpleWriter::writeFile(std::string fileName,std::vector<std::vector<float> > theData)
{
	// openining the stream
	aFileWriter.open(fileName.c_str());
	
	// writing the number of entries
	aFileWriter<<theData.size()<<std::endl;
	
	// writing the coordinates
	for (int aData = 0; aData<theData.size();aData++)
	{
		// checking if the vector float has correct number of entries
		if (theData[aData].size()==3)
		{
			aFileWriter<<theData[aData][0] <<" "<<theData[aData][1]  <<" "<< theData[aData][2] <<std::endl;
		}
		else
		{
			aFileWriter<<"Corrupted Entry\n";
		}
	}
	
	// closing the stream to the open file
	aFileWriter.close();
}

// Function for writing the file containing string data 
// Input is a vector of a string 
// Output file is a with the first line containing the number of entries
// in the following lines are the strings one per line
void SimpleWriter::writeFile(std::string fileName,std::vector<std::string> theData)
{
	// openining the stream
	aFileWriter.open(fileName.c_str());
	
	// writing the number of entries
	aFileWriter<<theData.size()<<std::endl;
	
	// writing the string
	for (int aData = 0; aData<theData.size();aData++)
	{
		aFileWriter<<theData[aData] <<std::endl;
	}
	
	// closing the stream to the open file
	aFileWriter.close();

}