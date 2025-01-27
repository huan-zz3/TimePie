//
// Created by huanzze on 25-1-26.
//

#ifndef PREDEFINE_H
#define PREDEFINE_H

#include <sigc++/sigc++.h>
// #include <sigc++.h>
#include <iostream>

typedef sigc::signal<void> Signal_void;
typedef sigc::signal<void(int)> Signal_int;
typedef sigc::signal<void(std::string)> Signal_string;



#endif //PREDEFINE_H
