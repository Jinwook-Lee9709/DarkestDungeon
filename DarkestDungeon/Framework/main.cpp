#include "stdafx.h"
#include <nlohmann/json.hpp>
#include <fstream>



int main()
{
    FRAMEWORK.Init(1920, 1080, "SFML!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}