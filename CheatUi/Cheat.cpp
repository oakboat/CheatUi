#include "Cheat.h"


int Cheat::Render()
{
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin(u8"Oak调试器");
            ImGui::Button(u8"选择进程");
            ImGui::SeparatorText(u8"搜索");
            static char str0[128] = "0";
            ImGui::InputText(u8"搜索值", str0, IM_ARRAYSIZE(str0));
            ImGui::Button(u8"新的搜索");
            ImGui::SameLine();
            ImGui::Button(u8"继续搜索");
            ImGui::SeparatorText(u8"结果");
            const char* items[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };
            static int item_current = 0;
            ImGui::ListBox("搜索结果", &item_current, items, IM_ARRAYSIZE(items), 4);
            ImGui::End();
        }

        ImGui::ShowDemoWindow();
        static char buffer[100];
        sprintf_s(buffer, u8"帧率 %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::GetBackgroundDrawList()->AddText({ 10, 10 }, IM_COL32_WHITE, buffer);
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        ui->g_pd3dDeviceContext->OMSetRenderTargets(1, &ui->g_mainRenderTargetView, NULL);
        ui->g_pd3dDeviceContext->ClearRenderTargetView(ui->g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        ui->g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    ui->CleanupDeviceD3D();
    ::DestroyWindow(ui->hWnd);
    ::UnregisterClassW(ui->ClassName, GetModuleHandle(nullptr));
    return 0;
}

int Cheat::Run()
{
	ui = std::make_unique<Ui>(TEXT("Cheat Ui Class"), TEXT("Cheat Ui Window"), 1600, 900);
	ui->Init();
    Render();
    return 0;
}