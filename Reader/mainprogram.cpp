#include <iostream>
#include <cstdlib>

#include "reader.h"
#include <cv.h>
#include <highgui.h>


int main()
{
    
	// Opening a file
    Reader aReader("E:\\OldDesktop\\UniquePosesFromEntireCMUMocap\\Unique_01_01.bvh","Unique_01_01.bvh");
	// Reading the file
    aReader.readFile();
	// Obtaining a bvh file with unique poses only   
	
	aReader.uniquePoseIdentification();

	// code for visualization of a certain structure is given below
	
	// make a window
	

	for (int runView=0;runView<aReader.getTotalFrames();runView++)
	{
	// Code for applying a frame and then viewing it
	FrameBVH aFrame = aReader.getFrame(runView);		
	Pose testPose;
	Structure poseStructure = testPose.adoptPose(aReader.getStructure(),aFrame);	
	cv::Mat thePoseImage =  poseStructure.visualizeStructure();
					
	// display the image
	cv::namedWindow("The Output",CV_WINDOW_AUTOSIZE);	
	cv::imshow("The Output",thePoseImage);
	cv::waitKey(2000);
	}
	// function for visualization of the Mat
	
    system("PAUSE");

}
