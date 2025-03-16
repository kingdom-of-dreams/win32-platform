/*
   time.h -- Hyperdrive's time implementation for Windows platform.

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
#include "platform/time.h"

#include "error.h"
#include <Windows.h>

int hd_time_now(hd_time* out) {
   if (out == NULL) return HD_INVALID_ARG;

   SYSTEMTIME now = {0};
   GetLocalTime(&now);
   out->year         = now.wYear;
   out->month        = now.wMonth;
   out->day          = now.wDay;
   out->hours        = now.wHour;
   out->minutes      = now.wMinute;
   out->seconds      = now.wSecond;
   out->milliseconds = now.wMilliseconds;
   return HD_OK;
}