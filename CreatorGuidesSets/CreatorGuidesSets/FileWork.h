#pragma once
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <string>

class FileWork
{

public:
    int getFileSizeOutput();
    int getFileSizeOut();
    void copyFile(std::string f1);
};
