# SubStructure #

Documentation for the Class

Explains
  * Class variables
  * public access functions

## Brief ##

_Class is made to store the joint information._
> _One may augment the class with additional information such as Bone Density, Bone Shape, Bone Length_

> _Also when we integrate with PCL (Point Cloud Library), we may begin offering 3D visualization of the bones._

## Class Variables ##

_Listed below are the variables used by this class. These variables encode all important information related to the joint._
> _Notes regarding variables used._

> _1- name contains the name of the joint specified in the BVH file._
> _2- offsetCoordinates contain variables stored in the following order X,Y,Z_

> _3- endsiteCoordinates contain variables stored in the following order X,Y,Z_

> _4- numberOfChannels corresponds to the amount of data given in each frame for this joint._

> _5- parentIndex is the index of the parent SubStructure in the Structure array._


## Public Functions ##

### Constructors and Destructors ###
_Default constructor for the class._
_Everything is set to null or default value_
```
SubStructure();
```

_User defined constructor for the class_
_User has to specify all the class variables_
```
SubStructure(std::string sName,std::vector<float> userOffsetCoordinates,std::vector<float> userEndsiteCoordinates,int sNumberOfChannels,int sIndexParent)
```

_Standard destructor for the class_
_Clears all vectors
```
~SubStructure()
```_


### Display ###
_Display function for the class data_
_Prints all attribute values to the console_
```
void print()
```

_Function for pritning a substructure to a file_
_Takes an input of the output stream you have initialized_
```
void printToFile(std::ofstream& outputStream)
```


### Mutator ###
_Mutator for specifying the name of the joint_
_Default name is an empty string_
```
void setName(std::string userName)
```

_Mutator for specifying the offset coordinates for the joint from its parent_
_Only applies coordinates if all X Y and Z coordinate are specified_
_Float type used to minimize memory wastage_
```
void setOffset(std::vector<float> theOffset)
```

_Mutator for specifying the endsite coordinates for the joint_
_Only applies coordinates if all X Y and Z coordinate are specified_
_Float type used to minimize memory wastage_
```
void setEndPoints(std::vector<float> userEndsiteCoordinates)
```

_Mutator for specifying the parent joint's index_
_For root joint please set value to -1_
```
void setParentIndex(int theParentIndex)
```


_Mutator for specifying the number of channels_
_Default number is 0_
```
void setNumberOfChannels(int userNumberOfChannels)
```


### Accessors ###
_Accessor for obtaining name of joint_
```
std::string getName()
```

_Accessor for obtaining SubStructure offsets from parent_
```
std::vector<float> getOffset()
```


_Accessor for obtaining endsite coordinates of substructure_
```
std::vector<float> getEndsiteCoordinates()
```

_Accessor for obtaining number of channels_
```
int getNumberOfChannels()
```

_Accessor for obtaining SubStructure parent joint index_
```
int getParentIndex()
```