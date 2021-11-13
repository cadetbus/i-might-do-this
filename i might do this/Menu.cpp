#include "Menu.h"
#include "pch.h"


bool bHop = false;

namespace menu {
	FILE* f;
	void run()
	{
		AllocConsole();

		errno_t err;

		err = freopen_s(&f, "CONOUT$", "w", stdout);
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r);
		system("Color 0A");
		std::cout << "WELCOME TO MY CSGO HACK\n"
			<< "BHOP [F1] == " << std::boolalpha << bHop << std::endl;
		
	}

	void update(const int vKey)
	{
		if (vKey == 0x70)
			bHop = !bHop;
 		system("cls");
		std::cout << "WELCOME TO MY CSGO HACK\n"
			<< "BHOP [F1] == " << bHop;
	}

	void enable()
	{
	}

	void disable()
	{
		FreeConsole();
		fclose(f);
	}

}