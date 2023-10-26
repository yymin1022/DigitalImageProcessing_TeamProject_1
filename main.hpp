#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <iostream>
#include "ximage.h"

bool loadFiles(const char** files, CxImage** images);
void processImages(CxImage** images);

#endif