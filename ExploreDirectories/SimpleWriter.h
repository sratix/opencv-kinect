#ifndef _SIMPLEWRITER_H
#define _SIMPLEWRITER_H

#include <fstream>
#include <string>
#include <vector>


class SimpleWriter
{
	// Class created to do file writing of simple structured files
	
	private:
		// Contains Variabels
		// 1- aFileWriter is an output stream to connect to the file you want to write
		
		std::ofstream aFileWriter;
		
	public:
		// Constructor
		SimpleWriter();
		
		// the write function is over-ridden for different data types
		
		void writeFile(std::string fileName,std::vector<std::vector<float> > theData);		
		void writeFile(std::string fileName,std::vector<std::string> theData);
		
		
};
#endif