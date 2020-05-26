
#include <windows.h>
#include <shobjidl.h>
#include <string>

#ifndef _FILECHOOSER_H_
#define _FILECHOOSER_H_

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

std::string Wchar_2_String(wchar_t* str)
{
	std::string res;
	while (*str)
		res += (char)*str++;
	return res;
}

std::string GetFilePath()
{
	wchar_t* pszFilePath = new wchar_t[500];
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
		    IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);


					SafeRelease(&pItem);
				}
			}
			SafeRelease(&pFileOpen);
		}
		CoUninitialize();
	}
	
	
	if (SUCCEEDED(hr))
	{
		std::string result;
		result = Wchar_2_String(pszFilePath);
		CoTaskMemFree(static_cast<void*>(pszFilePath));
		return result;
	}
	return "";
}

#endif // !_FILECHOOSER_H_

