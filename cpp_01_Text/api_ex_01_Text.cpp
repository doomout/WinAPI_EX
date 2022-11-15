#include <Windows.h>
#include <TCHAR.H>
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�������� ������� ����
	WndClass.lpszMenuName = NULL; //�޴� ��� ����
	WndClass.lpszClassName = _T("Window Class Name"); 
	RegisterClass(&WndClass); //Ŀ�ο� ����Ѵ�.
	hwnd = CreateWindow(
				_T("Window Class Name"),  //������ Ŭ���� �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
				_T("������� ù ��° ������"), //������ Ÿ��Ʋ �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
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
/*
   10����� �Է� ���� �� �ִ� �޸��� ����
   1�࿡�� �ִ� 20�ڱ��� ���� �ִ� 10����� �Է� ���� �� ����
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[10][20]; //���ڿ��� ������ ����(�ִ� 20����, 10��)
	static int count, yPos; //���ڿ�, y��
	
	RECT rt = { 0, 0, 1000, 1000 };
	static SIZE size;
	 
	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		CreateCaret(hwnd, NULL, 5, 15); 
		ShowCaret(hwnd);
		yPos = 0;
		count = 0;
		break;	

	case WM_PAINT: //������ â ���
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < yPos+1; i++)
		{
			GetTextExtentPoint(hdc, str[i], _tcslen(str[i]), &size); //����� ȭ�� | ũ�⸦ �����ϴ� ���ڿ� | �� ��° ���ڱ��� ũ�⸦ �������� | ���ڿ� ��
			TextOut(hdc, 0, i*20, str[i], _tcslen(str[i])); //  i* 20���� y��
			SetCaretPos(size.cx, i*20); //Ŀ�� �ڸ���
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR: //Ű���� �Է�
		if (count > 20) //���ٿ� 20���̻� ��ħ
		{
			count--;
		}
		else if ((wParam == VK_BACK) && (count > 0)) //���ڰ� 0�� �̻��ְ�, �齺���̽��� ����ϸ� ����(VK_BACK)
		{
			count--;
		}
		else if (wParam == VK_RETURN) //���͸� ġ��~
		{
			if (yPos < 9) //10 �ٱ�����  ���
			{
				count = 0;
				yPos++; //y���� �����Ͽ� ��ĭ ������
			}
		}
		else //����, �齺���̽� ������ ������ Ű ���� ��
			str[yPos][count++] = wParam;
	

		str[yPos][count] = '\0'; //���ڿ��� ��

		InvalidateRgn(hwnd, NULL, TRUE); //ȭ�� ���� ���� �Լ�
		break;

	case WM_DESTROY : //������ â ����� ���
		HideCaret(hwnd); //ĳ�� ����
		DestroyCaret(); 
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	default:
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}