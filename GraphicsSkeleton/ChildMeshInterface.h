/******************************************************************************
Class:ChildMeshInterface
Implements:
Author:Rich Davison
Description: At the last minute, it was realised that the Mesh class as
provided in the tutorials didn't implement multiple child meshes, which OBJ
and MD5Meshes might have...oh dear. So instead, OBJMesh and MD5Mesh are both
multiple inheritors, being subclasses of Mesh and this class, which
works a bit like a Java interface, but moreso ;) It was either this, or
duplicate the code across MD5Mesh and OBJMesh. 

Not my finest hour of coding...

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////
#include "common.h"

#ifdef WEEK_2_CODE
#pragma once

#include "PS4Mesh.h"
#include <vector>

class ChildMeshInterface	{
	friend class PS4Mesh;
public:
	void AddChild(PS4Mesh* m)	{
		children.push_back(m);
	}

	virtual ~ChildMeshInterface() {
		for(unsigned int i = 0; i < children.size(); ++i) {
			delete children.at(i);
		}
	}

protected:
	//Some Meshes have children...
	std::vector<PS4Mesh*> children;
	ChildMeshInterface(void){};
};
#endif