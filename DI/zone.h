////
// @file global.h 
// @brief 
// the global object and the relation
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CPPINJECT_ZONE_H_
#define _CPPINJECT_ZONE_H_

#include <vector>

namespace CppInject
{

class destroyer;

/**
 * @brief A Hierarchical zone of control.
 */
class Zone
{
 public:
	Zone( Zone * parent);
	
	virtual ~Zone();

	void push_destroyer(destroyer* d);

	Zone *parent() const;

  private:
	std::vector<destroyer*> destroyers;
	Zone* mParent;
};

}
#endif //_CPPINJECT_ZONE_H_