////
// @file global.h 
// @brief 
// the global object and the relation
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include "globalobject.h"
#include "cppinject.h"

CppInject::Zone globalZone( 0 );
CppInject::Zone session1( &globalZone );
CppInject::Zone session2( &globalZone );
CppInject::Zone request1( &session1 );
CppInject::Zone request2( &session1 );
