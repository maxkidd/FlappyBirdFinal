#ifndef _IENTITYSYSTEM_H_
#define _IENTITYSYSTEM_H_

class IEntitySystem
{
public:
	virtual ~IEntitySystem(){}
	virtual void Process() = 0;
};

#endif