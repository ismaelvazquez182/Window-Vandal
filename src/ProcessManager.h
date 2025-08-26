#pragma once

#include <windows.h>
#include <string>
#include <vector>

struct WindowInfo {
    unsigned int index;
    HWND hwnd;
    std::string title;
};

class ProcessManager {
public:
    std::vector<WindowInfo> EnumerateWindows();

    bool SetWindowTitle(HWND hwnd, const std::wstring& newTitle);

private:
    std::vector<WindowInfo> m_windows;
    unsigned int m_window_index{ 0 };

    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
};