#ifndef HD_WIN32PLATFORM_WIN32WINDOW_HPP
#define HD_WIN32PLATFORM_WIN32WINDOW_HPP

#include <Windows.h>

#define NATIVE_PLATFORM_WINDOW_TYPE HWND
#include <platform/window.hpp>

namespace HD::Win32 {
   class Window : public HD::Platform::Window {
      public:
         Window()          = default;
         virtual ~Window() = default;

         HD::Result Initialize(const HD::String& title, int width, int height);

         void Show();
         void PeekEvent();

         int GetWidth() const;

         int GetHeight() const;

         friend LRESULT CALLBACK windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
   };
}; // namespace HD::Win32

#endif // HD_WIN32PLATFORM_WIN32WINDOW_HPP