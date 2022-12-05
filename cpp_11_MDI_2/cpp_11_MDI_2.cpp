#include <Windows.h>
#include <TCHAR.H>
#include  "resource.h"

HINSTANCE hInst;

//�ݹ� �Լ� ����
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

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

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU_11));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //�������� ũ�⸦ �����ϸ� �ٽ� �׸��� ������ �����츦 ���Ѵ�.
	WndClass.lpfnWndProc = FrameWndProc; //�޼��� ó���� ���� �Լ�
	WndClass.cbClsExtra = 0; //Ŭ������ ���� ������ �޸𸮸� ������� ����
	WndClass.cbWndExtra = 0; //�����츦 ���� ������ �޸𸮸� ������� ����
	WndClass.hInstance = hInstance; //WinMain  ù��° �Ű�����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU_11); //�޴� ���
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
		CW_USEDEFAULT, //������ ���� ũ��(�⺻)
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

HWND ChildHwnd[2];
//Ŭ���̾�Ʈ �����츦 ������ �����쿡 ����� �ֱ� ���� �Լ�
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rectView;
	static BOOL split;

	switch (iMsg)
	{
	case WM_CREATE:
		split = FALSE;
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SPLIT_2x1:
			if (split == TRUE) break;
			GetClientRect(hwnd, &rectView);
			ChildHwnd[0] = CreateWindowEx(
				WS_EX_CLIENTEDGE,  // ��谡 �ణ �� ��ü ����
				_T("Child Window Class Name"), //������ Ŭ������ �̸�
				NULL, //�������� Ÿ��Ʋ �ٿ� �� �̸������� �˾� ���°� �ƴϱ⿡ ����
				WS_CHILD | WS_VISIBLE, //�����Ǵ� �����찡 �˾��� �ƴϰ� �ڽ� ������ ����
				0, //�����찡 ��Ÿ�� ��ġ x��
				0,  //�����찡 ��Ÿ�� ��ġ y��
				rectView.right, //������ �������� �ʺ�
				rectView.bottom / 2 - 1, //������ �������� ���̷� ���� �������� ����
				hwnd,
				NULL,
				hInst,
				NULL
			);

			ChildHwnd[1] = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				_T("Child Window Class Name"),
				NULL,
				WS_CHILD | WS_VISIBLE,
				0,
				rectView.bottom / 2 + 1,
				rectView.right,
				rectView.bottom / 2 - 1,
				hwnd,
				NULL,
				hInst,
				NULL
			);
			return 0;

		case ID_EXIT:
			PostQuitMessage(0);
			return 0;
		}
		return 0;
		
		case WM_SIZE:
			if (split == TRUE)
			{
				GetClientRect(hwnd, &rectView);
				MoveWindow(ChildHwnd[0], 0, 0, rectView.right, rectView.bottom/2-1, TRUE);
				MoveWindow(ChildHwnd[1], 0, rectView.bottom/2+1, rectView.right, rectView.bottom/2-1, TRUE);
			}
			return 0;

		case WM_DESTROY: //������
			PostQuitMessage(0);
			return 0;		
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
//�޼��� ó�� �κ�, �ݹ� �Լ� ���
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		break;

	case WM_COMMAND: //�޴� �׸� ���ý� ���
		//switch (LOWORD(wParam))
		//{
		//
		//}
		break;

	case WM_DESTROY: //������ â ����� ���
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		return 0;
	}
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam); //�ڽ� ������ ���
}