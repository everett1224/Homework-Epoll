////
// @file sigfunc.h 
// @brief 
// this is the signal callback functions,
// here is the SIGINT call back function. 
// you can add new signal callback here. 
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _SINGAL_H_
#define _SINGAL_H_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

//callback for the SIGINT
void signalINTConfg(void(*foo)(int));

#ifdef __cplusplus	
}
#endif //__cplusplus

#endif //_SINGAL_H_

