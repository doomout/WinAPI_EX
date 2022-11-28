#include <Windows.h>
#include <TCHAR.H>
#include <math.h>
#include  "resource.h"
#include <stdio.h>

//�ݹ� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//���� �κ� 
//hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID�� �޸𸮿����� ��ġ
//lpszCmdLine : ��� ���ο��� ���α׷� ������ ������ ���ڿ�
//nCmdShow : �����쿡 ����ϴ� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //�������� ũ�⸦ �����ϸ� �ٽ� �׸��� ������ �����츦 ���Ѵ�.
	WndClass.lpfnWndProc = WndProc; //�޼��� ó���� ���� �Լ�
	WndClass.cbClsExtra = 0; //Ŭ������ ���� ������ �޸𸮸� ������� ����
	WndClass.cbWndExtra = 0; //�����츦 ���� ������ �޸𸮸� ������� ����
	WndClass.hInstance = hInstance; //WinMain  ù��° �Ű�����
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);  //�������� ����ǥ�� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM); //Ŀ���� ���̺�(�빮�� I)�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //�������� �⺻���� ����
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1_2); //�޴� ���
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
		TranslateMessage(&msg); //�� �޽����� �ϳ��� ������ �� ���
		DispatchMessage(&msg); //�޽��� ó���ϴ� �Լ��� �޽��� ����
	}
	return (int)msg.wParam;
}
void OutFromFile(TCHAR filename[], HWND hwnd)
{
	FILE *fPtr;
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
		if (buffer[_tcslen(buffer)-1] == _T('\n'))
		{
			buffer[_tcslen(buffer) - 1] = NULL;
		}
		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}
	fclose(fPtr);
	ReleaseDC(hwnd, hdc);
}

//�޼��� ó�� �κ�, �ݹ� �Լ� ���
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int answer;
	OPENFILENAME OFN;
	OPENFILENAME SFN;
	HDC hdc;
	PAINTSTRUCT ps;

	TCHAR str[100], lpstrFile[100] = _T(""); //���� ��� ������ ���� �迭
	TCHAR filter[] = _T("��ü ����(*.*) \0*.*\0Text File\0*.txt; *.doc\0");
	
	CHOOSEFONT FONT; //��Ʈ ����
	static COLORREF  fColor; //��Ʈ ��
	HFONT hFont, OldFont;
	static LOGFONT LogFont;

	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	int i;

	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		//��Ʈ ���� �κ�
		hFont = CreateFontIndirect(&LogFont);
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, fColor);
		TextOut(hdc, 10, 10, _T("HelloWorld"), 10);
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);

		//���� ���� �κ�
		hBrush = CreateSolidBrush(color);
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, 30, 50, 200, 200); //�� ��ġ, ũ��
		SelectObject(hdc, OldBrush);
		DeleteObject(hBrush);

		EndPaint(hwnd, &ps);
		break;

	case WM_COMMAND: //�޴� �׸� ���ý� ���
		switch (LOWORD(wParam)) //� �޴� �׸��� ���� �Ǿ����� �Ǵ�.
		{
		case ID_FILENEW: //�� ����
			MessageBox(hwnd,  _T("�� ������ ���ڽ��ϱ�?"),  _T("�� ���� ����"),  MB_OKCANCEL);
			break;

		case ID_COLORDLG: //���� �����ϱ�
			for (i = 0; i < 16; i++)
				tmp[i] = RGB(rand()%256, rand()%256, rand()%256);
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.lpCustColors = tmp;
			COLOR.Flags = CC_FULLOPEN;
			if (ChooseColor(&COLOR) != 0)
			{
				color = COLOR.rgbResult;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			break;

		case ID_FONTDLG: //��Ʈ �����ϱ�
			memset(&FONT, 0, sizeof(CHOOSEFONT));
			FONT.lStructSize = sizeof(CHOOSEFONT);
			FONT.hwndOwner = hwnd;
			FONT.lpLogFont = &LogFont;
			FONT.Flags = CF_EFFECTS | CF_SCREENFONTS;
			if (ChooseFont(&FONT) != 0)
			{
				fColor = FONT.rgbColors;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
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
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}