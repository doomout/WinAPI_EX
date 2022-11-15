#include <Windows.h>
#include <TCHAR.H>
//�ݹ� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//�ڽ� �� ���ڿ� ��� �Լ�
wchar_t t_DrawText(HDC hdc);
//���ڿ� ��� �Լ�
wchar_t t_TextOut(HDC hdc);

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //�������� �������� ����
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
//�޼��� ó�� �κ�, �ݹ� �Լ� ���
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[100];
	static int count, yPos;
	RECT rt = { 0, 0, 1000, 1000 };
	 
	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		count = 0;
		break;	

	case WM_PAINT: //������ â ��½� ���
		hdc = BeginPaint(hwnd, &ps);
		DrawText(hdc, str, _tcslen(str), &rt, DT_TOP | DT_LEFT);

		//t_DrawText(hdc); //�ڽ� �� ���ڿ� ��� �Լ�
		//t_TextOut(hdc); //���ڿ� ��� �Լ�
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR: //Ű���� �Է½� ���
		if (wParam == VK_BACK && count > 0) //�齺���̽��� ����ϸ� ����(VK_BACK)
			count--;
		else
			str[count++] = wParam;
			
		str[count] = NULL;
		InvalidateRgn(hwnd, NULL, TRUE); //ȭ�� ���� ���� �Լ�
		break;

	case WM_DESTROY : //������ â ����� ���
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	default:
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

wchar_t t_TextOut(HDC hdc)
{
	//���ڿ� ��� �Լ� (ȭ�鿵�� | x ��ǥ | y ��ǥ | ����� �ؽ�Ʈ ���ڿ�, ��Ƽ����Ʈ, �����ڵ� �� ����� �� �ִ� _tcslen() �Լ� ���)
	return TextOut(hdc, 100, 100, _T("Hello �ȳ�"), _tcslen(_T("Hello �ȳ�")));
}

wchar_t t_DrawText(HDC hdc)
{
	RECT rect;
	// �ڽ� ��ǥ ����
	rect.left = 50;
	rect.top = 40;
	rect.right = 600;
	rect.bottom = 320;
	//�ؽ�Ʈ ��� �Լ�(ȭ�鿵�� ���� | ����� ���ڿ� | ���ڿ� ���� | �ڽ� ������ ��ǥ�� ����� �ּҰ�, ���� ��� ��ġ�� ������� �˷��� ��)
	return DrawText(hdc, _T("HelloWord"), 10, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}