# SubStructure #

Documentation for the Class

Explains
  * Class variables
  * public access functions

## Brief ##

_This class is created to store a FrameBVH from a .bvh file_

## Class Variables ##

> _Listed below are the variables used by this class. These variables encode all important information related to the FrameBVH._

> _Notes regarding variables used._

> _1- rotations contains the angles for the rotation matrices in the order X Y and Z_

> _2- translationRoot contains the translation data for the entire structure_

> _3- totalChannels contain the total number of Channels the motion data must have for the FrameBVH to be valid_

> _4- totalJoints stores the total number of joints that are expected to prevent redundant computations_

## Public Functions ##

### Constructors and Destructors ###
_Default constructor for the class._

_Everything is set to null or default value_

_You must change the number of channels before you add rotations_

```
FrameBVH();
```

_User defined constructor for the class_

_User has to specify the total number of Channels._

_In case of reading a bvh with this reader these can be obtained by 'getTotalChannels()' function of Structure class_

```
FrameBVH(int numberOfChannels);
```


_Standard destructor for the class_

_Clears all vectors._

_Clears vector within vector and then Clears vector_

```
~FrameBVH();
```

### Display ###
_Display function for the class data_

_Prints all attribute values to the console_

```
void print();
```

### Mutator ###
_Mutator for specifying the rotation for a particular joint_

_No default value_

_Only works under the assumption that the joint rotations are input in the correct order_

_Rotation angles must be stored in radians_

```
void setRotation(std::vector<float> theRotations);
```

_Mutator for specifying the rotation for a particular joint_

_No default value_

```
void setTranslation(std::vector<float> theTranslation);
```

### Accessors ###
_Accessor for obtaining rotation angles for a particular joint_

_Joint value must be greater then zero and less then the 'totalJoints' variable of this class_

```
std::vector<float> getRotationDetails(int joint);
```

_Accessor for obtaining translation values of the root_

```
std::vector<float> getTranslationDetails(); 
```