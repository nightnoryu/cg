#include "../libgl/GdiPlusInitializer.h"
#include "MyApplication.h"
#include "common_inc.h"

MyApplication app("Unbothered", 800, 600);
CGdiPlusInitializer gdiplusInitializer;

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	glewInit();

	app.MainLoop();
	return 0;
}