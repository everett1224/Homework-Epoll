////
// @file zone.cc 
// @brief 
// the zone class 
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include "zone.h"
#include "destroyer.h"
#include <stdio.h>

namespace CppInject
{

Zone::Zone( Zone * parent) : mParent(parent){}

Zone::~Zone()
{
	printf("ZONE is deleted %p\n", this);
	for( std::vector<destroyer*>::iterator itr = destroyers.begin(); itr != destroyers.end(); ++itr )
	{
		destroyer* destroy = *itr;
		(*destroy)();
		delete destroy;
	}
}

void Zone::push_destroyer(destroyer* d)
{
	destroyers.push_back(d);
}

Zone *Zone::parent() const
{
	return mParent;
}


}