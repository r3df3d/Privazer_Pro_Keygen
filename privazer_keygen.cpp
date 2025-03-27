#include <windows.h>
#include <string>
#include <vector>
#include <commctrl.h>

// Include resource header
#include "resource.h"

// Explicitly link to required libraries
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_EDIT_EMAIL 101
#define ID_BUTTON_GENERATE 102
#define ID_EDIT_LICENSE 103
#define ID_BUTTON_COPY 104

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string generatePrivaZerLicense(const std::string& email);

// Fonts and controls
HFONT g_hTitleFont = NULL;
HFONT g_hNormalFont = NULL;
HFONT g_hLicenseFont = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize common controls
    InitCommonControls();
    
    const char CLASS_NAME[] = "PrivaZer Keygen Window";

    // Load icon directly from file - simplest approach
    HICON hIcon = (HICON)LoadImage(
        NULL,
        "icon.ico",
        IMAGE_ICON,
        0, 0,
        LR_LOADFROMFILE | LR_DEFAULTSIZE
    );

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    // Use the loaded icon if available, otherwise use default application icon
    wc.hIcon = hIcon ? hIcon : LoadIcon(NULL, IDI_APPLICATION);

    RegisterClass(&wc);

    // Create a larger window with a better size
    HWND hwnd = CreateWindow(
        CLASS_NAME,
        "PrivaZer Pro Keygen [by redfed]",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 350, 280,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) return 0;

    // Also set the window's icon (for taskbar)
    if (hIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }

    // Center the window on screen
    RECT rc;
    GetWindowRect(hwnd, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    SetWindowPos(hwnd, NULL, 
        (screenWidth - width) / 2, 
        (screenHeight - height) / 2,
        width, height, SWP_NOZORDER);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // Clean up fonts
    if (g_hTitleFont) DeleteObject(g_hTitleFont);
    if (g_hNormalFont) DeleteObject(g_hNormalFont);
    if (g_hLicenseFont) DeleteObject(g_hLicenseFont);
    
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create fonts
            g_hTitleFont = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
                
            g_hNormalFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
                
            // Create a larger, bold, red font for license display
            g_hLicenseFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
                
            // Create a bold font for labels
            HFONT hBoldFont = CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");

            // Title - centered
            HWND hTitle = CreateWindow("STATIC", "PrivaZer Pro Keygen",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                0, 15, 350, 30,  // Full width for better centering
                hwnd, NULL, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)g_hTitleFont, TRUE);

            // Email label - NOW BOLD
            HWND hEmailLabel = CreateWindow("STATIC", "Enter Email:",
                WS_VISIBLE | WS_CHILD,
                30, 60, 150, 20,
                hwnd, NULL, NULL, NULL);
            SendMessage(hEmailLabel, WM_SETFONT, (WPARAM)hBoldFont, TRUE);

            // Email input field - INCREASED HEIGHT AND WIDTH
            HWND hEmailEdit = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                30, 85, 300, 25,  // Increased width to 300 and height to 25
                hwnd, (HMENU)ID_EDIT_EMAIL, NULL, NULL);
            SendMessage(hEmailEdit, WM_SETFONT, (WPARAM)g_hNormalFont, TRUE);
            
            // License Key label - BOLD
            HWND hLicenseLabel = CreateWindow("STATIC", "License Key:",
                WS_VISIBLE | WS_CHILD,
                30, 125, 100, 20,
                hwnd, NULL, NULL, NULL);
            SendMessage(hLicenseLabel, WM_SETFONT, (WPARAM)hBoldFont, TRUE);

            // License Output - as a static text label with center alignment
            HWND hLicenseDisplay = CreateWindow("STATIC", "",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                0, 150, 350, 25,  // Full width for perfect centering
                hwnd, (HMENU)ID_EDIT_LICENSE, NULL, NULL);
            SendMessage(hLicenseDisplay, WM_SETFONT, (WPARAM)g_hLicenseFont, TRUE);

            // Generate Button - on the left side of bottom area
            HWND hGenerateBtn = CreateWindow(
                "BUTTON", "Generate",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                60, 195, 110, 30,
                hwnd, (HMENU)ID_BUTTON_GENERATE, NULL, NULL);
            SendMessage(hGenerateBtn, WM_SETFONT, (WPARAM)g_hNormalFont, TRUE);
            
            // Copy Button - on the right side of bottom area
            HWND hCopyBtn = CreateWindow(
                "BUTTON", "Copy",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                180, 195, 110, 30,
                hwnd, (HMENU)ID_BUTTON_COPY, NULL, NULL);
            SendMessage(hCopyBtn, WM_SETFONT, (WPARAM)g_hNormalFont, TRUE);

            // Set focus to email field
            SetFocus(hEmailEdit);
            return 0;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            HWND hStatic = (HWND)lParam;
            
            if (GetDlgCtrlID(hStatic) == ID_EDIT_LICENSE) {
                // Set the license text to bold red
                SetTextColor(hdcStatic, RGB(204, 0, 0));  // Red color
                SetBkColor(hdcStatic, GetSysColor(COLOR_WINDOW));
                return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
            }
            
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            SetBkColor(hdcStatic, GetSysColor(COLOR_WINDOW));
            return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BUTTON_GENERATE) {
                char email[256];
                GetDlgItemText(hwnd, ID_EDIT_EMAIL, email, 256);
                
                std::string license = generatePrivaZerLicense(email);
                SetDlgItemText(hwnd, ID_EDIT_LICENSE, license.c_str());
            }
            else if (LOWORD(wParam) == ID_BUTTON_COPY) {
                // Get the license key text
                char licenseKey[256];
                GetDlgItemText(hwnd, ID_EDIT_LICENSE, licenseKey, 256);
                
                // Copy to clipboard if not empty
                if (strlen(licenseKey) > 0) {
                    // Open clipboard
                    if (OpenClipboard(hwnd)) {
                        // Clear clipboard
                        EmptyClipboard();
                        
                        // Allocate global memory for text
                        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(licenseKey) + 1);
                        
                        if (hMem) {
                            // Copy text to global memory
                            char* pMem = (char*)GlobalLock(hMem);
                            strcpy(pMem, licenseKey);
                            GlobalUnlock(hMem);
                            
                            // Set clipboard data
                            SetClipboardData(CF_TEXT, hMem);
                        }
                        
                        // Close clipboard
                        CloseClipboard();
                    }
                }
            }
            return 0;
        }

        case WM_DESTROY: {
            // Clean up fonts
            if (g_hTitleFont) DeleteObject(g_hTitleFont);
            if (g_hNormalFont) DeleteObject(g_hNormalFont);
            if (g_hLicenseFont) DeleteObject(g_hLicenseFont);
            
            PostQuitMessage(0);
            return 0;
        }

        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

std::string generatePrivaZerLicense(const std::string& email) {
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || email.find('@', atPos + 1) != std::string::npos) {
        return "Invalid email format";
    }

    std::string prefix = email.substr(0, atPos);
    std::vector<char> licenseDigits;

    for (char c : prefix) {
        std::string asciiStr = std::to_string((int)c);
        for (char digit : asciiStr) {
            licenseDigits.push_back(digit);
            if (licenseDigits.size() >= 10) break;
        }
        if (licenseDigits.size() >= 10) break;
    }

    if (licenseDigits.size() < 10) {
        return "Email prefix too short";
    }

    return std::string(licenseDigits.begin(), licenseDigits.begin() + 10);
}