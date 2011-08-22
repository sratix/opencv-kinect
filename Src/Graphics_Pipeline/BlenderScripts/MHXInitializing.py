##########
# Blender Script 
# To be Used with Imported MHX Mesh for exporting Coordinates for Labelling.
# Note: MHX Coordinates are different from OBJ File Coordinates hence the need for this Script.

# Inputs Needed:
# 1 - Character Name (to be used for distinguishing between differnet Characters)
# 2 - path (to be used for writing output files )

# Outputs : 
# 1 - _MHX_Mesh.coords            ( contains the Coordinates of the Mesh in T-Stance Pose) 
# 2 - _MHX_Mesh.faces             ( contains the data for which coordinates to use to make faces that draw the whole character


# Author
# Mohammad Haris Baig
# baig.haris@gmail.com

# Script August: 2011
# Revision Number : 2

## Importing Data From Blender and OS 
import bpy
import os

## Setting the Paths

# 'rootPath' refers to the Directory Where you want to output the Files
rootPath = "D:\\GSOC-Kinect\\Characters\\GirlTest"
# 'newDirectory adds a subdirectory in the Root Directory so that all the Different Files for a character can be put in the same directory yet be organized
# 'newDirectory' creates a directory called '
newDirectory = rootPath + "\\Mesh\\"
# 'characterName is what you want to name your Character. 
# all files generated come with the characterName as the prefix to their name. This allows for easy reading
characterName = 'GirlOne'

# Creating New Directory if it does not exist
if not os.path.exists(newDirectory):
    os.makedirs(newDirectory)    


## Initializations

# Initializing file writers
writeVertices = open(newDirectory +characterName + "_MHX_Mesh.coords","w")
writeFaces = open(newDirectory+characterName+"_MHX_Mesh.faces","w")


# Chosing the Mesh of the character
# Mesh 0 is cube!
characterMesh = bpy.data.meshes[1];

# Writing number of Vertices that make up this character
# It is always 14596
writeVertices.write("%d\n"%len(characterMesh.vertices))

# Writing number of Faces that make up this character
# It is always 13820
writeFaces.write("%d\n"%len(characterMesh.faces))


## Output the Data 

# Single for loop used as both have same number of elements
for aCoordinate in characterMesh.vertices:
    # The vertices are in the order of X Y Z and so are written that way.
    writeVertices.write("%f %f %f\n"%(aCoordinate.co[0],aCoordinate.co[2],-aCoordinate.co[1]))

# Closing the writer
writeVertices.close()

# Writing data for faces used for rendering the mesh                   
for aFace in characterMesh.faces:
    writeFaces.write("%d %d %d %d\n"%(aFace.vertices[0],aFace.vertices[1],aFace.vertices[2],aFace.vertices[3]))

# Closing the file as all data has been written to it
writeFaces.close()  


# Emptying out the data structures that we constructed
del characterMesh;
