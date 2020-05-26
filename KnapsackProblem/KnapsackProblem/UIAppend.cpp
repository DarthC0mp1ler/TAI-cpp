#include "appendui.h"
#include "filechoser.h"
#include <sstream>
#include <ctime>



void UIAppend::AddMenu(HWND& hwnd)
{
	HMENU menu = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	AppendMenu(hFileMenu, MF_STRING, SELECT_NEW_FILE, L"NEW FILE");
	AppendMenu(hFileMenu, MF_STRING, EXIT_MENU, L"EXIT");

	AppendMenu(menu, MF_POPUP, (UINT_PTR)hFileMenu, L"FILE");
	AppendMenu(menu, MF_STRING, HELP_MENU, L"HELP");

	SetMenu(hwnd, menu);
}

std::string UIAppend::OnCommand(HWND& hwnd, WPARAM wParam)
{
	switch (wParam)
	{
	case FILE_MENU:
		MessageBeep(MB_OK);
		return "";
	case EXIT_MENU:
		MessageBeep(MB_OK);
		exit(0);
		return "";
	case HELP_MENU:
		MessageBox(NULL, L"info", L"Information", MB_OK);
		return "";
	case INITIALIZE:
		if (path.empty()) return "";
		OnInitialize();
		init = true;
		return "";
		break;
	case CALC_ONE:
		if (init == false) return "";
		OnCalc(hwnd);
		return "";
		break;
	case SELECT_NEW_FILE:
		init = false;
		std::string s = GetFilePath();
		std::wstring res(s.begin(), s.end());
		SetWindowTextW(filePath, res.c_str());
		path = s;
		return s;
		break;

	}
}

void UIAppend::AddUI(HWND& hwnd)
{
	filePath = CreateWindow(L"static", L"",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		10, 10, 1000, 30,
		hwnd, NULL,
		NULL, NULL);
	SetWindowTextW(filePath, L"---file path ---");

	CreateWindow(
		L"BUTTON",
		L"INITIALIZE",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 70, 100, 30,
		hwnd,
		(HMENU)INITIALIZE, NULL, NULL);

	datasetLength = CreateWindow(L"static", L"",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		10, 120, 150, 30,
		hwnd, NULL,
		NULL, NULL);
	SetWindowTextW(datasetLength, L"data set length");

	datasetCapacity = CreateWindow(L"static", L"",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		10, 150, 150, 30,
		hwnd, NULL,
		NULL, NULL);
	SetWindowTextW(datasetCapacity, L"data set capacity");

	CreateWindow(
		L"BUTTON",
		L"CALC RAND",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 190, 100, 30,
		hwnd,
		(HMENU)CALC_ONE, NULL, NULL);

	//SetWindowTextW(output, L"--output will be here--");
}

void UIAppend::OnInitialize()
{

	alg = new Algorithm(path);
	std::wstringstream wss;
	wss << "Length: " << alg->getLength();
	SetWindowTextW(datasetLength, wss.str().c_str());

	wss = std::wstringstream();
	wss << "Capacity: " << alg->getCapacity();
	SetWindowTextW(datasetCapacity, wss.str().c_str());

}

void UIAppend::OnCalc(HWND& hwnd)
{
	if (cases.size() != 0)
	{
		for (auto w : cases) {
			DestroyWindow(w);
		}
	}
	std::srand(std::time(nullptr));
	int random = 1 + std::rand() % alg->getDatasetQuantity();
	int tm = 0;
	SYSTEMTIME time;
	GetLocalTime(&time);
	tm += time.wMilliseconds + time.wSecond * 1000 + time.wMinute * 60000;

	std::vector<Algorithm::Attribute> vec;

	alg->getKnapsack(random, vec);

	GetLocalTime(&time);
	tm = (time.wMilliseconds + time.wSecond * 1000 + time.wMinute * 60000) - tm;

	int cap = 0, val = 0;
	for (auto attr : vec)
	{
		cap += attr.size;
		val += attr.value;
	}


	std::wstringstream ss;
	ss << "Finished in: " << tm << " milliseconds;" << std::endl << " Capacity reached: " << cap << ";" << std::endl << " Value: " << val;

	CreateWindow(L"static", ss.str().c_str(),
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		200, 50, 300, 70,
		hwnd, NULL,
		NULL, NULL);


	int x = 200, y = 120;

	for (size_t i = 0; i < vec.size(); i++, y += 30)
	{
		std::wstringstream str;
		str << "[ " << vec.at(i).number << ", " << vec.at(i).size << ", " << vec.at(i).value << " ]";
		cases.push_back(
			CreateWindow(L"static", str.str().c_str(),
				WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				x, y, 100, 30,
				hwnd, NULL,
				NULL, NULL)
		);

		//y += 30;
		i++;
		if (i < vec.size()) {
			str = std::wstringstream();
			str << "[ " << vec.at(i).number << ", " << vec.at(i).size << ", " << vec.at(i).value << " ]";
			cases.push_back(
				CreateWindow(L"static", str.str().c_str(),
					WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					x + 100, y, 100, 30,
					hwnd, NULL,
					NULL, NULL)
			);
		}

	}
}