#ifndef PREDEFINE_H
#define PREDEFINE_H

#include <sigc++/sigc++.h>
#include <iostream>
/*
 * The encapsulation of sigc++
*/
// no return Signal_type
typedef sigc::signal<void>								Signal_void;
typedef sigc::signal<void, int>             			Signal_int;
typedef sigc::signal<void, std::string>     			Signal_string;
// return Signal_type
typedef sigc::signal<void, int&> 						Signal_reint_void;
typedef sigc::signal<void, int&, int> 					Signal_reint_int;
typedef sigc::signal<void, int&, std::string> 			Signal_reint_string;
typedef sigc::signal<void, std::string&, std::string> 	Signal_restring_string;
// no return Slot_type
typedef sigc::slot<void> 								Slot_void;
typedef sigc::slot<void, int> 							Slot_int;
typedef sigc::slot<void, std::string> 					Slot_string;
// return Slot_type
typedef sigc::slot<void, int&>							Slot_reint_void;
typedef sigc::slot<void, int&, int> 					Slot_reint_int;
typedef sigc::slot<void, int&, std::string> 			Slot_reint_string;
typedef sigc::slot<void, std::string&, std::string> 	Slot_restring_string;
// package function
#define Ptr_fun(x)          							sigc::ptr_fun(&x)
#define Mem_fun(this, x)    							sigc::mem_fun(&this, &x)

SIGC_USING_STD(cout)
SIGC_USING_STD(endl)
SIGC_USING_STD(string)
/* end of sigc++ */



#endif //PREDEFINE_H
