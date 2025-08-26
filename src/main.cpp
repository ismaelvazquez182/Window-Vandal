#include <iostream>
#include <vector>
#include <Windows.h>

#include "Gui.h"
#include "ProcessManager.h"

ProcessManager pm;
std::vector<WindowInfo> windows;

void changeTitle(int index, std::string new_name) { SetWindowTextA(windows[index].hwnd, new_name.c_str()); }

void refresh(std::string* list_items)
{
	windows.clear();
	windows = pm.EnumerateWindows();
	for (int i = 0; i < windows.size(); i++) {
		list_items[i] = "   " + windows[i].title;
	}
}

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Gui g{};
	g.Run(refresh, changeTitle);
	return 0;
}
