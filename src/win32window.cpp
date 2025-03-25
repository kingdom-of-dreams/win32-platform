#include "win32window.hpp"

#include <array>
#include "assert.hpp"

constexpr int maxWindowTitleSize = 64;

namespace {
   bool windowClassRegistered = false;
}

LRESULT CALLBACK HD::Win32::windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
   HD::Win32::Window* subject = (HD::Win32::Window*)GetWindowLongPtr(handle, GWLP_USERDATA);
   switch (message) {
      case WM_CREATE: {
         subject = (HD::Win32::Window*)((CREATESTRUCT*)lParam)->lpCreateParams;
         SetWindowLongPtrW(handle, GWLP_USERDATA, (LONG_PTR)subject);
         return 0;
      }
      case WM_CLOSE: {
         subject->shown = false;
         return 0;
      }
      default: {
         return DefWindowProc(handle, message, wParam, lParam);
      }
   }
}

HD::Result HD::Win32::Window::Initialize(const HD::String& title, int width, int height) {
   HD_ASSERT_POSITIVE(width);
   HD_ASSERT_POSITIVE(height);

   const wchar_t* className      = L"HyperdriveWin32Window";
   HINSTANCE      currentProcess = GetModuleHandle(nullptr);
   HD_ASSERT_NOT_NULL(currentProcess);
   if (!windowClassRegistered) {
      // Register window class
      const WNDCLASSEX windowClass = {
          .cbSize        = sizeof(WNDCLASSEX),
          .style         = CS_HREDRAW | CS_VREDRAW,
          .lpfnWndProc   = HD::Win32::windowProcedure,
          .cbClsExtra    = 0,
          .cbWndExtra    = 0,
          .hInstance     = currentProcess,
          .hIcon         = nullptr,
          .hCursor       = nullptr,
          .hbrBackground = nullptr,
          .lpszMenuName  = nullptr,
          .lpszClassName = className,
          .hIconSm       = nullptr,
      };

      windowClassRegistered = (0 != RegisterClassEx(&windowClass));
   }

   std::array<wchar_t, maxWindowTitleSize> unicodeAppTitle = {};
   title.AsWideCStr(unicodeAppTitle.data(), maxWindowTitleSize);
   this->handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, className, unicodeAppTitle.data(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                 CW_USEDEFAULT, width, height, nullptr, nullptr, currentProcess, (LPVOID)this);

   return (nullptr != this->handle) ? HD::Codes::OK : HD::Codes::PLATFORM_ERROR;
}

void HD::Win32::Window::Show() {
   ShowWindow(this->handle, SW_SHOW);
   this->shown = true;
}

void HD::Win32::Window::PeekEvent() {
   MSG msg = {};
   PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE);
   TranslateMessage(&msg);
   DispatchMessage(&msg);
}

int HD::Win32::Window::GetWidth() const {
   RECT rect = {};
   GetWindowRect(this->handle, &rect);
   return rect.right - rect.left;
}

int HD::Win32::Window::GetHeight() const {
   RECT rect = {};
   GetWindowRect(this->handle, &rect);
   return rect.bottom - rect.top;
}