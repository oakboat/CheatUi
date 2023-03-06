#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class Ui
{
public:
	Ui(LPCTSTR ClassName, LPCTSTR WindowName, int WindowWidth, int WindowHeight);
	bool Init();
	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;
	static IDXGISwapChain* g_pSwapChain;
	static ID3D11RenderTargetView* g_mainRenderTargetView;
	LPCTSTR ClassName = nullptr;
	LPCTSTR WindowName = nullptr;
	int WindowWidth = 0;
	int WindowHeight = 0;
	HWND hWnd = nullptr;
};