#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
HINSTANCE hInst;

class Punto
{   public:
    double x, y;
};

double productoCruz(Punto& A, Punto& B, Punto& P)
{   return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

bool intersecan(Punto& A, Punto& B, Punto& C, Punto& D)
{
    double a,b,c,d;
    a=productoCruz(A,B,C);
    b=productoCruz(A,B,D);
    c=productoCruz(C,D,A);
    d=productoCruz(C,D,B);
    if(((a<0&&b>0) || (b<0&&a>0)) && ((c<0&&d>0) || (d<0&&c>0)))
        return true;
    else return false;
}

bool superponen(Punto& A, Punto& B, Punto& C, Punto& D)
{
    double a,b,c,d;
    a=productoCruz(A,B,C);
    b=productoCruz(A,B,D);
    c=productoCruz(C,D,A);
    d=productoCruz(C,D,B);
    if((a==0&&b==0) && (c==0&&d==0))
        return true;
    else return false;
}

bool paralelas(Punto& A, Punto& B, Punto& C, Punto& D)
{
    double mAB = (B.y - A.y) / (B.x - A.x);
    double mCD = (D.y - C.y) / (D.x - C.x);
    if(mAB==mCD)
        return true;
    else return false;
}

long activo, activo2;

Punto A,B,P,C,D,Q;
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_PAINT:
        {   PAINTSTRUCT ps;
            HDC hdc;
            hdc=BeginPaint(hwndDlg,&ps);
            MoveToEx(hdc,A.x,A.y,NULL);
            LineTo(hdc,B.x,B.y);
            Ellipse(hdc,A.x-10,A.y-10,A.x+10,A.y+10);
            Ellipse(hdc,B.x-10,B.y-10,B.x+10,B.y+10);

            MoveToEx(hdc,C.x,C.y,NULL);
            LineTo(hdc,D.x,D.y);
            Ellipse(hdc,C.x-10,C.y-10,C.x+10,C.y+10);
            Ellipse(hdc,D.x-10,D.y-10,D.x+10,D.y+10);


            EndPaint(hwndDlg,&ps);
        }
        return TRUE;

        case WM_RBUTTONDOWN:
        {
            long x2Pos = GET_X_LPARAM(lParam);
            long y2Pos = GET_Y_LPARAM(lParam);
            activo2=1;
            C.x=D.x=x2Pos;
            C.y=D.y=y2Pos;
            InvalidateRect(hwndDlg,NULL,true);
        }
        return TRUE;
        case WM_RBUTTONUP:
        {   long x2Pos = GET_X_LPARAM(lParam);
            long y2Pos = GET_Y_LPARAM(lParam);
            activo2 = 0;
            long deltaX = x2Pos - C.x;
            long deltaY = y2Pos - C.y;
            D.x = C.x + deltaX;
            D.y = C.y + deltaY;
            InvalidateRect(hwndDlg, NULL, true);
        }
        return TRUE;

        case WM_LBUTTONDOWN:
        {   long xPos = GET_X_LPARAM(lParam);
            long yPos = GET_Y_LPARAM(lParam);
            activo=1;
            A.x=B.x=xPos;
            A.y=B.y=yPos;
            InvalidateRect(hwndDlg,NULL,true);
        }
        return TRUE;
        case WM_LBUTTONUP:
        {   long xPos = GET_X_LPARAM(lParam);
            long yPos = GET_Y_LPARAM(lParam);
            activo=0;
            B.x=xPos;
            B.y=yPos;
            InvalidateRect(hwndDlg,NULL,true);
        }
        return TRUE;
        case WM_MOUSEMOVE:
        {

            long xPos = GET_X_LPARAM(lParam);
            long yPos = GET_Y_LPARAM(lParam);

            long x2Pos = GET_X_LPARAM(lParam);
            long y2Pos = GET_Y_LPARAM(lParam);

            SetDlgItemInt(hwndDlg,EDITX,(int)xPos,FALSE);
            SetDlgItemInt(hwndDlg,EDITY,(int)yPos,FALSE);

            SetDlgItemInt(hwndDlg,EDITX2,(int)x2Pos,FALSE);
            SetDlgItemInt(hwndDlg,EDITY2,(int)y2Pos,FALSE);
            if(activo!=1 && activo2!=1)
            {
                if(intersecan(A,B,C,D))
                {
                    SetDlgItemText(hwndDlg,INTER,"Si se intersecan");
                }
                if(intersecan(A,B,C,D)==false)
                {
                    SetDlgItemText(hwndDlg,INTER,"No se intersecan");
                }
                if(superponen(A,B,C,D))
                {
                    SetDlgItemText(hwndDlg,SUPER,"Se superponen");
                }
                if(superponen(A,B,C,D)==false)
                {
                    SetDlgItemText(hwndDlg,SUPER,"No se superponen");
                }
                if(paralelas(A,B,C,D))
                {
                    SetDlgItemText(hwndDlg,PARAL,"Son paralelas");
                }
                if(paralelas(A,B,C,D)==false)
                {
                    SetDlgItemText(hwndDlg,PARAL,"No son paralelas");
                }
            }
            if(activo==1)
            {   B.x=xPos;
                B.y=yPos;
                InvalidateRect(hwndDlg,NULL,true);
            }
            if(activo!=1)
            {   P.x=xPos;
                P.y=yPos;
                double val=productoCruz(A, B, P);
                char cadena[50];
                sprintf(cadena, "%.2f", val);
                SetDlgItemText(hwndDlg,POSX,cadena);

            }
            if(activo2==1)
            {
                D.x=x2Pos;
                D.y=y2Pos;
                InvalidateRect(hwndDlg,NULL,true);
            }
            if(activo2!=1)
            {
                Q.x=x2Pos;
                Q.y=y2Pos;
                double val2=productoCruz(C, D, Q);
                char cadena2[50];
                sprintf(cadena2, "%.2f", val2);
                SetDlgItemText(hwndDlg,POSX2,cadena2);
            }
        }
        return TRUE;


        case WM_INITDIALOG:
        {   activo2=0;
            activo=0;

        }
        return TRUE;

        case WM_CLOSE:
        {

            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {

            }
        }
        return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
