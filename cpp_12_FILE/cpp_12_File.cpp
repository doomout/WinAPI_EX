#include <windows.h>
#include <TCHAR.H>
#include "resource.h"

//�ݹ� �Լ� ����
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
void  ReadFromFile(int WndIndex, TCHAR filename[]);

HWND  hwndChild[100];
TCHAR  WinBuff[100][1000];
int   WndCount;
HINSTANCE  hInst;

//���� �κ� 
//hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID�� �޸𸮿����� ��ġ
//lpszCmdLine : ��� ���ο��� ���α׷� ������ ������ ���ڿ�
//nCmdShow : �����쿡 ����ϴ� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;

	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;  //�������� ũ�⸦ �����ϸ� �ٽ� �׸��� ������ �����츦 ���Ѵ�.
	WndClass.lpfnWndProc = FrameWndProc; //�޼��� ó���� ���� �Լ�		
	WndClass.cbClsExtra = 0;	//Ŭ������ ���� ������ �޸𸮸� ������� ����	

	WndClass.cbWndExtra = 0;	//�����츦 ���� ������ �޸𸮸� ������� ����	
	WndClass.hInstance = hInstance;	 //WinMain  ù��° �Ű�����	
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������	 
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU12);	//�޴� ��� 	
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Child Window Class Name");
	RegisterClass(&WndClass); //Ŀ�ο� ����Ѵ�.

	hwnd = CreateWindow(
		_T("Window Class Name"),  //������ Ŭ���� �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		_T("Main Window Title"), //������ Ÿ��Ʋ �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		WS_OVERLAPPEDWINDOW, //������ ��Ÿ��(�ּ�, �ִ�ȭ, �ݱ� ��ư)
		CW_USEDEFAULT, //������ ��ġ x ��ǥ(�⺻), �⺻�� ������ CW_USEDEFAULT �� ����.	
		CW_USEDEFAULT, //������ ��ġ y ��ǥ(�⺻)	
		CW_USEDEFAULT, //������ ���� ũ��(�⺻)	
		CW_USEDEFAULT,  //������ ���� ũ��(�⺻)	
		NULL,	 //�θ� ������ �ڵ�
		NULL,	 //�޴� �ڵ�
		hInstance,	//���� ���α׷� �ν��Ͻ�
		NULL	 //���� ������ ����
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
		TranslateMessage(&msg);	//�� �޽����� �ϳ��� ������ �� ���
		DispatchMessage(&msg);	//�޽��� ó���ϴ� �Լ��� �޽��� ����
	}
	return (int)msg.wParam;
}

//Ŭ���̾�Ʈ �����츦 ������ �����쿡 ����� �ֱ� ���� �Լ�
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND   hwndClient;
	CLIENTCREATESTRUCT  clientcreate;
	MDICREATESTRUCT  mdicreate;
	static TCHAR filepath[1000], folder[100], filename[100];
	TCHAR filter[] = _T("�ؽ�Ʈ ���� (*.txt)\0*.txt\0��� ���� (*.*)\0*.*\0");
	OPENFILENAME OFN;

	switch (iMsg)
	{
	case WM_CREATE:
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hwnd), 0);
		clientcreate.idFirstChild = 100;
		hwndClient = CreateWindow(
			_T("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0,
			hwnd,
			NULL,
			hInst,
			(LPSTR)&clientcreate
		);
		ShowWindow(hwndClient, SW_SHOW);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILEOPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFile = filepath;
			OFN.nMaxFileTitle = 100;
			OFN.lpstrFileTitle = filename;
			OFN.nMaxFile = 1000;
			OFN.lpstrFilter = filter;
			OFN.Flags = OFN_EXPLORER;
			GetOpenFileName(&OFN);
			WndCount++;
			ReadFromFile(WndCount, filepath);
			mdicreate.szClass = _T("Child Window Class Name");
			mdicreate.szTitle = filepath;
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;
			hwndChild[WndCount] = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			return 0;
		}
		break;
	case WM_DESTROY: //�������α׷� ����
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hwnd, hwndClient, iMsg, wParam, lParam);
}

void ReadFromFile(int WndIndex, TCHAR filename[])
{
	HANDLE hFile;
	DWORD size = 1000;
	hFile = CreateFile(
		filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, 0
	);
	ReadFile(hFile, WinBuff[WndIndex], size * sizeof(TCHAR), &size, NULL);
	WinBuff[WndIndex][size] = NULL;
	CloseHandle(hFile);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int i, SelectWnd;
	HDC hdc;
	RECT rt;
	PAINTSTRUCT ps;

	for (i = 1; i <= WndCount; i++)
		if (hwnd == hwndChild[i])
		{
			SelectWnd = i;
			break;
		}

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rt);
		DrawText(hdc, WinBuff[SelectWnd], (int)_tcslen(WinBuff[SelectWnd]), &rt, DT_TOP | DT_LEFT);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		return 0;
	}
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam); //�ڽ� ������ ���
}
