
#include <atlbase.h>
#include <atlwin.h>
#include <atltypes.h>
#include "JsonViewDlg.h"

namespace ns_simple_windowx
{
    class windowx : public CWindowImpl<windowx, CWindow>
    {
    public:
        BEGIN_MSG_MAP(windowx)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLbdown)
        MESSAGE_HANDLER(WM_DESTROY,OnDestroy)
        END_MSG_MAP()
        windowx() {}

        ~windowx() {}

        LRESULT OnLbdown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandle) {
            
            return 0;
        }
        LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandle) {
            PostQuitMessage(0);
            return 0;
        }
        void SetDlg(JsonViewDlg *x) {dlg = x;}

        void create(const int &w, const int &h)
        {
            CRect rt(0, 0, w, h);
            Create(NULL, rt, L"windowx", WS_SYSMENU|WS_CLIPCHILDREN);
            CenterWindow();
            ShowWindow(SW_NORMAL);
        }

    private:
    private:
        JsonViewDlg *dlg;
    };
    class subwind : public CWindowImpl<subwind, CWindow>
    {
    public:
        BEGIN_MSG_MAP(subwind)
        END_MSG_MAP()
        subwind() {}

        ~subwind() {}

        void create(HWND parent, const int &w, const int &h)
        {
            CRect rt(0, 0, w, h);
            Create(parent, rt, L"subwind", WS_BORDER | WS_CHILD);
            ShowWindow(SW_NORMAL);
        }

    private:
    private:
    };
}    // namespace ns_simple_windowx

const int    width = 900;
const int    height = 600;
const int    xdt = 5;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    ns_simple_windowx::windowx windx;
    windx.create(width, height);
    windx.SetIcon(LoadIcon(0, IDI_APPLICATION));

    std::shared_ptr<Setting> setting(new Setting);
    JsonViewDlg              dlg(hInstance, windx.m_hWnd, 0, setting);
    windx.SetDlg(&dlg);
    dlg.ShowDlg(true);

    auto childWind  = dlg.getHSelf();
    LONG styleValue = ::GetWindowLong(childWind, GWL_STYLE);
    styleValue |= WS_CHILD;
    styleValue &= ~WS_CAPTION;
    ::SetWindowLong(childWind, GWL_STYLE, styleValue);

    CRect rt;
    GetClientRect(windx.m_hWnd, &rt);

    auto wx = rt.Width() / 3;
    auto hx = rt.Height();

    ns_simple_windowx::subwind sw;
    sw.create(windx.m_hWnd, wx, hx);
    ::MoveWindow(sw.m_hWnd, 0, 0, wx-xdt, hx, true);
    ::SetParent(sw.m_hWnd, windx.m_hWnd);


    ns_simple_windowx::subwind swx;
    swx.create(windx.m_hWnd, wx, hx);
    ::MoveWindow(swx.m_hWnd, wx, 0, wx, hx, true);
    ::SetParent(swx.m_hWnd, windx.m_hWnd);

    
    ::MoveWindow(childWind, wx * 2 + xdt, 0, wx - xdt, hx, true);
    ::SetParent(childWind, windx.m_hWnd);

    /*InvalidateRect(swx.m_hWnd, 0, TRUE);
    UpdateWindow(swx.m_hWnd);*/
    MSG msg;
    while (GetMessage(&msg, windx.m_hWnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
