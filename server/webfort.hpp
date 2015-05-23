#ifndef __WF_WEBFORT_HPP__
#define __WF_WEBFORT_HPP__

/*
 * webfort.hpp
 * Part of Web Fortress
 *
 * Copyright (c) 2014 mifki, ISC license.
 */

#include "Console.h"

void deify(DFHack::color_ostream* raw_out, std::string nick);
void quicksave(DFHack::color_ostream* out);

extern unsigned char sc[256*256*5];
extern int newwidth, newheight;
extern volatile bool needsresize;

bool is_safe_to_escape();
void show_announcement(std::string announcement);

#endif
