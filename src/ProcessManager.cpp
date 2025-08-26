#include "ProcessManager.h"

std::vector<WindowInfo> ProcessManager::EnumerateWindows() 
{
    m_window_index = 0;
    m_windows.clear();
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
    return m_windows;
}

bool ProcessManager::SetWindowTitle(HWND hwnd, const std::wstring& newTitle) 
{
    return SetWindowTextW(hwnd, newTitle.c_str());
}

BOOL CALLBACK ProcessManager::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    auto* self = reinterpret_cast<ProcessManager*>(lParam);

    if (!IsWindowVisible(hwnd)) return TRUE;

    char title[256];
    GetWindowTextA(hwnd, title, 256);
    if (strlen(title) == 0) return TRUE;

    self->m_windows.push_back({ self->m_window_index, hwnd, title });
    self->m_window_index++;
    return TRUE;
}