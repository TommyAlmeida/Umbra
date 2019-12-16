#pragma once

#pragma warning( push )
#pragma warning( disable : 26454 ) //Disables VS19 Warning bug c26454

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Umbra/Io/Log.h"

#ifdef UB_PLATFORM_WINDOWS
#include <Windows.h>
#endif