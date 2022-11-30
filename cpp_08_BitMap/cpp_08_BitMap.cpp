#include <Windows.h>
#include <TCHAR.H>
#include <math.h>
#include  "resource.h"
#include <stdio.h>
#include <iostream>
#define BSIZE 40
double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}

//�ݹ� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//��Ʈ��
HINSTANCE hInst;


//���� �κ� 
//hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID�� �޸𸮿����� ��ġ
//lpszCmdLine : ��� ���ο��� ���α׷� ������ ������ ���ڿ�
//nCmdShow : �����쿡 ����ϴ� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	HACCEL hAcc;

	hInst = hInstance;
	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR5_1));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //�������� ũ�⸦ �����ϸ� �ٽ� �׸��� ������ �����츦 ���Ѵ�.
	WndClass.lpfnWndProc = WndProc; //�޼��� ó���� ���� �Լ�
	WndClass.cbClsExtra = 0; //Ŭ������ ���� ������ �޸𸮸� ������� ����
	WndClass.cbWndExtra = 0; //�����츦 ���� ������ �޸𸮸� ������� ����
	WndClass.hInstance = hInstance; //WinMain  ù��° �Ű�����
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);  //�������� ����ǥ�� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM); //Ŀ���� ���̺�(�빮�� I)�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //�������� �⺻���� ����
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //�޴� ���
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass); //Ŀ�ο� ����Ѵ�.
	hwnd = CreateWindow(
		_T("Window Class Name"),  //������ Ŭ���� �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		_T("���� �޽��� ó�� �ϱ�"), //������ Ÿ��Ʋ �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		WS_OVERLAPPEDWINDOW, //������ ��Ÿ��(�ּ�, �ִ�ȭ, �ݱ� ��ư)
		200, //������ ��ġ x ��ǥ(200), �⺻�� ������ CW_USEDEFAULT �� ����.
		300, //������ ��ġ y ��ǥ(300)
		600, //������ ���� ũ��(600)
		400, //������ ���� ũ��(400)
		NULL, //�θ� ������ �ڵ�
		NULL, //�޴� �ڵ�
		hInstance, //���� ���α׷� �ν��Ͻ�
		NULL //���� ������ ����
	);
	ShowWindow(hwnd, nCmdShow); //������ ȭ�� ǥ��(��Ÿ�� ������ �ڵ� ��, ������ ȭ�鿡 ��Ÿ���� �溡���� ����� ����)
	UpdateWindow(hwnd); //�����쿡 �޼����� ������ ������ ȭ�鿡 �⺻ ��� �ϵ��� �Ѵ�.

	//�޽��� ����
	//&msg : �޼����� ����� MSG ����ü�� ���� ������
	//NULL : �޽����� �߻��� ������ �ڵ�
	//0 : ���� �޽����� �������� �ּ� ������
	//0 : ���� �޽����� �������� �ִ� ������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hwnd, hAcc, &msg)) //����Ű �˻�
		{
			TranslateMessage(&msg); //�� �޽����� �ϳ��� ������ �� ���
			DispatchMessage(&msg); //�޽��� ó���ϴ� �Լ��� �޽��� ����
		}
	}
	return (int)msg.wParam;
}
void OutFromFile(TCHAR filename[], HWND hwnd)
{
	FILE* fPtr;
	HDC hdc;
	int line;
	TCHAR buffer[500];
	line = 0;
	hdc = GetDC(hwnd);
#ifdef _UNICODE
	_tfopen_s(&fPtr, filename, _T("r, ccs=UNICODE"));
#else
	_tfopen_s(&fPtr, filename, _T("r"));
#endif
	while (_fgetts(buffer, 100, fPtr) != NULL)
	{
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
		{
			buffer[_tcslen(buffer) - 1] = NULL;
		}
		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}
	fclose(fPtr);
	ReleaseDC(hwnd, hdc);
}

void TextPrint(HDC hdc, int x, int y, TCHAR text[])
{
	int i, j;
	SetTextColor(hdc, RGB(255, 255, 255));
	for ( i = -1; i <= 1;  i++)
	{
		for ( j = -1; j < 1; j++)
		{
			TextOut(hdc, x+i, y+j, text, _tcslen(text));
		}
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, x, y, text, _tcslen(text));
	}
}

//�޼��� ó�� �κ�, �ݹ� �Լ� ���
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int answer;
	OPENFILENAME OFN;
	OPENFILENAME SFN;
	HDC hdc, mem1dc, mem2dc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap, hBit1, hBit2, oldBit1, oldBit2;
	static RECT rectView;
	static int yPos;
	TCHAR word[] = _T("�����~~ >.<");

	TCHAR str[100], lpstrFile[100] = _T(""); //���� ��� ������ ���� �迭
	TCHAR filter[] = _T("��ü ����(*.*) \0*.*\0Text File\0*.txt; *.doc\0");

	//��Ʈ ���� ����
	CHOOSEFONT FONT;
	static COLORREF  fColor;
	HFONT hFont, OldFont;
	static LOGFONT LogFont;

	//�÷� ���� ���� ����
	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	int i;

	//�� ���� ���� ����
	static HMENU hMenu, hSubMenu;
	int mx, my;
	static BOOL Select; //�� Ŭ�� ���� �� ���� ���� ����
	static BOOL Copy;
	static int x, y;

	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		yPos = -30;
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1, 70, NULL);
		hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		break;

	case WM_TIMER:
		yPos += 1;
		if (yPos > rectView.bottom)
		{
			yPos = -30;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rectView);
		hdc = BeginPaint(hwnd, &ps);

		//mem2dc -> mem1dc -> hdc
		mem1dc = CreateCompatibleDC(hdc);
		mem2dc = CreateCompatibleDC(mem1dc);

		// ����(hBit1)�� �� ������� hdc�� ȣȯ �ǵ��� �����.
		if (hBit1 == NULL)
			hBit1 = CreateCompatibleBitmap(hdc, 1200, 900);

		oldBit1 = (HBITMAP)SelectObject(mem1dc, hBit1);
		oldBit2 = (HBITMAP)SelectObject(mem2dc, hBit2);

		BitBlt(mem1dc, 0, 0, 1200, 900, mem2dc, 0, 0, SRCCOPY);
		SetBkMode(mem1dc, TRANSPARENT);
		TextPrint(mem1dc, 200, yPos, word);
		BitBlt(hdc, 0, 0, 1200, 900, mem1dc, 0, 0, SRCCOPY);

		SelectObject(mem1dc, oldBit1);
		SelectObject(mem2dc, oldBit2);
		DeleteDC(mem2dc);
		DeleteDC(mem1dc);
		TextOut(hdc, 200, yPos, word, _tcslen(word));


		EndPaint(hwnd, &ps);
		break;


	case WM_COMMAND: //�޴� �׸� ���ý� ���
		if (LOWORD(wParam) == ID_EDITCOPY)
		{
			Copy = TRUE;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;

		switch (LOWORD(wParam)) //� �޴� �׸��� ���� �Ǿ����� �Ǵ�.
		{
		case ID_FILENEW: //�� ����
			MessageBox(hwnd, _T("�� ������ ���ڽ��ϱ�?"), _T("�� ���� ����"), MB_OKCANCEL);
			break;

		case ID_FILEOPEN: //���� ����
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 100;
			OFN.lpstrInitialDir = _T(".");
			if (GetOpenFileName(&OFN) != 0)
			{
				OutFromFile(OFN.lpstrFile, hwnd);
			}
			break;

		case ID_FILESAVE:
			memset(&SFN, 0, sizeof(OPENFILENAME));
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hwnd;
			SFN.lpstrFilter = filter;
			SFN.lpstrFile = lpstrFile;
			SFN.nMaxFile = 256;
			SFN.lpstrInitialDir = _T(".");
			if (GetSaveFileName(&SFN) != 0)
			{
				_stprintf_s(str, _T("%s ���Ϸ� �����ϰڽ��ϱ�?"), SFN.lpstrFile);
				MessageBox(hwnd, str, _T("�����ϱ� ����"), MB_OK);
			}
			break;

		case ID_EXIT:
			answer = MessageBox(hwnd, _T("������ �����ϰ� �����ڽ��ϱ�?"), _T("������ ����"), MB_YESNOCANCEL);
			if (answer == IDYES || answer == IDNO)
			{
				PostQuitMessage(0);
			}
			break;
		}
		break;

	case WM_DESTROY: //������ â ����� ���
		if (hBit1) DeleteObject(hBit1);
		DeleteObject(hBit2);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}