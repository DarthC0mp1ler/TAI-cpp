#include <windows.h>
#include "consts.h"
#include <string>
#include "algorithm.h"

#ifndef _APPENDUI_H_
#define _APPENDUI_H_

class UIAppend {

	std::string path;
	HWND filePath;
	Algorithm* alg;
	HWND datasetLength;
	HWND datasetCapacity;
	HWND output;

	bool init = false;;

	std::vector<HWND> cases;

public:

	UIAppend() {}

	std::string OnCommand(HWND& hwnd,WPARAM wParam);

	void OnInitialize();
	
	void AddMenu(HWND& hwnd);

	void AddUI(HWND& hwnd);

	void OnCalc(HWND& hwnd);

};


#endif // !_APPENDUI_H_





