/*
   time.hpp -- Hyperdrive's time implementation for Windows platform.

   Copyright 2025 by Sylvain Nieuwlandt (for Kingdom of Dreams)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <platform/time.hpp>

#include "constants.hpp"
#include <Windows.h>

HD::Result HD::Platform::Time::Now() {
   SYSTEMTIME now = {0};
   GetLocalTime(&now);
   this->year         = now.wYear;
   this->month        = now.wMonth;
   this->day          = now.wDay;
   this->hours        = now.wHour;
   this->minutes      = now.wMinute;
   this->seconds      = now.wSecond;
   this->milliseconds = now.wMilliseconds;
   return HD::Codes::OK;
}