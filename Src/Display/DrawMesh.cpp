#include "DrawMesh.h"
// Standard Constructor for a Mesh
// Everything set to Null or default
DrawMesh::DrawMesh()
{
	numberOfVertices = 0;
	numberOfFaces = 0;
}

//  Standard Mutator for all Data
// Specifies All parameters needed to sketch
void DrawMesh::setAllData(std::vector<std::vector<float> > aCoordinates,std::vector<std::vector<int> > aFaces,std::vector<std::string> aLabels)
{
	
	theCoordinates = aCoordinates;
	theFaces = aFaces;
	theLabels = aLabels;
	
	numberOfVertices = theCoordinates.size();
	numberOfFaces = theFaces.size();
	
	
	for (int makeColor = 0; makeColor<numberOfVertices;makeColor++)
	{

		if (findLabelling(theLabels[makeColor]) == -1)
		{
			theLabelling.push_back(theLabels[makeColor]);
		
		}		
	}
}

//  Standard Mutator for Coordinates
// Specifies Coordinates of the Mesh
void DrawMesh::setCoordinates(std::vector<std::vector<float> > aCoordinates)
{
	theCoordinates.clear();
	theCoordinates = aCoordinates;
	numberOfVertices = theCoordinates.size();
}

// Defines 31 Colors
// Colors are defined to be bright
// Attempt is to make them distinguishable
// Making Colors is hard
std::vector<std::vector<float> > DrawMesh::makeColors()
{
	std::vector<std::vector<float> > theColors;
	
	std::vector<float > aColor;
	
	// Color 1
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 2
	aColor.push_back(0);
	aColor.push_back(1);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 3
	aColor.push_back(0);
	aColor.push_back(1);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 4
	aColor.push_back(1);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 5
	aColor.push_back(1);
	aColor.push_back(0);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 6
	aColor.push_back(1);
	aColor.push_back(1);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 7
	aColor.push_back(1);
	aColor.push_back(0.6);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 8
	aColor.push_back(0.5);
	aColor.push_back(0);
	aColor.push_back(0.9);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 9
	aColor.push_back(0.5);
	aColor.push_back(0);
	aColor.push_back(0.6);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 10
	aColor.push_back(0.7);
	aColor.push_back(0.5);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 11
	aColor.push_back(0.5);
	aColor.push_back(0.55);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 12
	aColor.push_back(0.2);
	aColor.push_back(0.4);
	aColor.push_back(0.3);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 13
	aColor.push_back(0);
	aColor.push_back(0.5);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 14
	aColor.push_back(0.4);
	aColor.push_back(0);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 15
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 16
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 17
	aColor.push_back(0.25);
	aColor.push_back(0.35);
	aColor.push_back(0.15);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 18
	aColor.push_back(0.75);
	aColor.push_back(0.75);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 19
	aColor.push_back(0);
	aColor.push_back(0.75);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 20
	aColor.push_back(0);
	aColor.push_back(0.75);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 21
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(0.75);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 22
	aColor.push_back(0.25);
	aColor.push_back(0);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 23
	aColor.push_back(0.85);
	aColor.push_back(0);
	aColor.push_back(0.35);	
	theColors.push_back(aColor);
	aColor.clear();

	// Color 24
	aColor.push_back(0.65);
	aColor.push_back(0.35);
	aColor.push_back(0);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 25
	aColor.push_back(0.25);
	aColor.push_back(0.5);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 26
	aColor.push_back(0);
	aColor.push_back(0.25);
	aColor.push_back(1);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 27
	aColor.push_back(1);
	aColor.push_back(0.25);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 28
	aColor.push_back(0);
	aColor.push_back(0);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 29
	aColor.push_back(0.75);
	aColor.push_back(0);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	
	// Color 30
	aColor.push_back(0);
	aColor.push_back(0.5);
	aColor.push_back(0.25);	
	theColors.push_back(aColor);
	aColor.clear();
	
	// Color 31
	aColor.push_back(0.25);
	aColor.push_back(0);
	aColor.push_back(0.5);	
	theColors.push_back(aColor);
	aColor.clear();
	
	return theColors;
}

// Internal Function used to locate the Mesh Labels Index
// Is Helpful in determining which color to assign 
int DrawMesh::findLabelling(std::string aLabel)
{
	int counter = 0;	
	bool found= false;
	
	while (counter< theLabelling.size() && found==false)
	{
		if (theLabelling[counter].compare(aLabel)==0)
		{
			return counter;
		}
		counter++;
	}
	return -1;
}

// Internal Function for Deciding what color a face is going to be
// Decision is made based on vertice Labels
// Color decision is the vector of the
int getPatchColor(std::vector<int> colorDecision)
{
	
	std::vector<int> values;
	std::vector<int> counters;
	bool found = false;
	
	// Code to get Counters and values stack set
	for (int check=0; check<colorDecision.size();check++)
	{
		for (int find=0; find<values.size();find++)
		{
			if (values[find] == colorDecision[check])
			{
				found = true;
				counters[find] = counters[find]+1;
				
				//std::cout<<"Value: "<<values[find]<<" contains " << counters[find]<<" at "<<find<<std::endl;				
			}
		}
		
		if (found==false)
		{
			values.push_back(colorDecision[check]);
			counters.push_back(1);
		}
		
		found= false;
	}
	
	//std::cout<<"values Size: "<<values.size()<<std::endl;
	

	if (values.size()==1)
	{		
		//std::cout<<"Returning: "<<values[0]<<std::endl;	
		return values[0];
	}
	else if (values.size()== 2)
	{		
		if (counters[0] ==3)
		{
			return values[0];
		}
		else if (counters[1]==3)
		{
			return values[1];			
		}
		else
		{
			// its a tie
			std::cout<<"Its a tie between two colors with equal counters\n";
			return values[1];
		}
	}
	else if (values.size()==3)
	{
		if (counters[0]==2)
		{
			return values[0];
		}
		else if (counters[1]==2)
		{
			return values[1];
		}
		else if (counters[2]==2)
		{
			return values[2];
		}
	}
	else
	{
		std::cout<<"All Four vertices have different Labels so Im Screwed\n";
		return values[3];
	}
	return 1;
	
}