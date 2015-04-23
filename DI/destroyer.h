////
// @file destroy.h 
// @brief 
// the base class of destroys
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CPPINJECT_DESTROYER_H_
#define _CPPINJECT_DESTROYER_H_

namespace CppInject
{
/**
 * @internal
 * @brief Abtract functor to destroy an object in a given scope
 */
class destroyer
{
  public:
	destroyer(){};
	virtual ~destroyer(){};
	
	virtual void operator()() = 0;
};

}
  
#endif //_CPPINJECT_DESTROYER_H_
