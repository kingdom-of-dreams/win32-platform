#ifndef HD_WIN32PLATFORM_WIN32WINDOW_HPP
#define HD_WIN32PLATFORM_WIN32WINDOW_HPP

#include <Windows.h>

#define NATIVE_PLATFORM_WINDOW_TYPE HWND
#include <logger.hpp>
#include <platform/window.hpp>

namespace HD::Win32 {
   class Window : public HD::Platform::Window {
      public:
         Window() : log(HD::Logger("Win32Window")) {};
         virtual ~Window() = default;

         HD::Result Initialize(const HD::String& title, int width, int height) override;

         void Show() override;
         void PeekEvent() override;

         int GetWidth() const override;

         int GetHeight() const override;

         friend LRESULT CALLBACK windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
      private:
         const HD::Logger log;
   };
}; // namespace HD::Win32

#endif // HD_WIN32PLATFORM_WIN32WINDOW_HPP