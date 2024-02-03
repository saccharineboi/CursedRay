// CursedRay: Hardware-accelerated path tracer
// Copyright (C) 2024 Omar Huseynov
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "Log.hpp"
#include "Constants.hpp"

#include <ctime>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <fstream>

namespace CursedRay
{
    ////////////////////////////////////////
    static std::ofstream logFile{};

    ////////////////////////////////////////
    void Log(const char* args, ...)
    {
        std::time_t timer;
        std::time(&timer);
        std::tm timeInfo{};

        if (!logFile.is_open()) {
            logFile = std::ofstream{DEFAULT_LOGFILE_NAME, std::ios_base::out | std::ios_base::ate};
        }

#ifdef __unix__
        localtime_r(&timer, &timeInfo);
#elif defined(_MSC_VER)
        localtime_s(&timeInfo, &timer);
#else
#error "CursedRay is not supported on this platform"
#endif

        std::va_list ap;
        va_start(ap, args);
        char processedOutput[250], finalOutput[500];
        std::vsnprintf(processedOutput, 250, args, ap);
        int charsWritten{ std::snprintf(finalOutput, 500, "[%02d:%02d:%02d %02d:%02d:%02d] %s\n", timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_year + 1900, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, processedOutput) };
        logFile.write(finalOutput, charsWritten);
        logFile.flush();
        va_end(ap);
    }
}
