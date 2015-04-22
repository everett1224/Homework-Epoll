#include "GlobalObject.h"
//#include "sample_classes.h"
#include "CppInject.h"

CppInject::Zone globalZone(0);
CppInject::Zone session1( &globalZone);
CppInject::Zone session2(  &globalZone);
CppInject::Zone request1(  &session1 );
CppInject::Zone request2(  &session1 );
