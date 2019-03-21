#include <Windows.h>
#include "res.h"


HINSTANCE hInst;
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  hInst = hinstance;
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
 
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////










INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_CREATE: //tworzenie okna
    break;
  case WM_PAINT: //rysowanie okna
    HDC hDC;
    hDC = GetDC(hwndDlg);

    HBITMAP hBitmap;
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(BITMAP_0));
    // hBitmap = LoadImage(hInst, MAKEINTRESOURCE("C:\\Users\\Albercik\\Desktop\\lenna"));
    HDC hDCBitmap;
    hDCBitmap = CreateCompatibleDC(hDC);
    SelectObject(hDCBitmap, hBitmap);
    BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY); //pobranie kontekstu ekranu
   // DeleteDC(hDCBitmap);
   // DeleteObject(hBitmap);

    ////////////// DZIEKS
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(BITMAP_BACKGROUND));
    hDCBitmap = CreateCompatibleDC(hDC);
    SelectObject(hDCBitmap, hBitmap);
    BitBlt(hDC, 0, 0, 4000, 3000, hDCBitmap, 0, 0, SRCCOPY); //pobranie kontekstu ekranu
    DeleteDC(hDCBitmap);
    DeleteObject(hBitmap);

    /////////////

    //SelectObject(hDC, GetStockObject(ANSI_VAR_FONT)); //podranie i aktywacja czcionki
    //SetTextColor(hDC, RGB(255, 0, 0)); //ustawianie koloru

    //TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27); //27 to iloœæ znaków, które ma wyœwietliæ
    ReleaseDC(hwndDlg, hDC);
    break;

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED: //zdarzenie klikniêcia na UI
      switch (LOWORD(wParam))
      {
      case BUTON_EASY: //klikniêcie na naszym przycisku
        MessageBox(hwndDlg, TEXT("Test"), TEXT("Klikniecie"), MB_OK);
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); //pobieranie uchwytu kontrolki IDC_EDIT1
        int iTextLength = GetWindowTextLength(hwndEditBox); //pobranie d³ugoœci tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1); //pobieranie tekstu

        SetWindowText((HWND)lParam, szText); //przypisanie go do przycisku
        return TRUE;
      }
    }
    return FALSE;
  case WM_LBUTTONDOWN:
    CHAR szText[200];
    wsprintf(szText, "Kiknales myszka x=%d, y=%d", LOWORD(lParam), HIWORD(lParam));
    MessageBox(hwndDlg, szText, TEXT("Klikniecie"), MB_OK);
    return TRUE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg); //niszczenie okienka
    PostQuitMessage(0); //umieszczanie w pêtli komnikatów polecenia zakoñczenia aplikacji
    return TRUE;
  }
  return FALSE;
}