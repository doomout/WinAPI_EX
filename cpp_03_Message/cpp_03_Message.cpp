﻿#include <Windows.h>
#include <TCHAR.H>
//콜백 함수 선언
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//메인 부분 
//hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID로 메모리에서의 위치
//lpszCmdLine : 명령 라인에서 프로그램 구동시 전달할 문자열
//nCmdShow : 윈도우에 출력하는 형태
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우의 크기를 변경하면 다시 그리는 형태의 윈도우를 뜻한다.
	WndClass.lpfnWndProc = WndProc; //메세지 처리를 위한 함수
	WndClass.cbClsExtra = 0; //클래스를 위한 여분의 메모리를 사용하지 않음
	WndClass.cbWndExtra = 0; //윈도우를 위한 여분의 메모리를 사용하지 않음
	WndClass.hInstance = hInstance; //WinMain  첫번째 매개변수
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);  //아이콘은 물음표료 변경
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM); //커서를 아이빔(대문자 I)로 변경
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //바탕색은 검정으로 변경
	WndClass.lpszMenuName = NULL; //메뉴 사용 안함
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass); //커널에 등록한다.
	hwnd = CreateWindow(
		_T("Window Class Name"),  //윈도우 클래스 이름(유니 코드로 변환 하기 위해 _T 붙임)
		_T("제어 메시지 처리 하기"), //윈도우 타이틀 이름(유니 코드로 변환 하기 위해 _T 붙임)
		WS_OVERLAPPEDWINDOW, //윈도우 스타일(최소, 최대화, 닫기 버튼)
		200, //윈도우 위치 x 좌표(200), 기본을 쓰려면 CW_USEDEFAULT 를 쓴다.
		300, //윈도우 위치 y 좌표(300)
		600, //윈도우 가로 크기(600)
		400, //윈도우 세로 크기(400)
		NULL, //부모 윈도우 핸들
		NULL, //메뉴 핸들
		hInstance, //응용 프로그램 인스턴스
		NULL //생성 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow); //윈도우 화면 표시(나타낼 윈도우 핸들 값, 윈도우 화면에 나타내는 방벙으로 상수값 제공)
	UpdateWindow(hwnd); //윈도우에 메세지를 보내서 윈도우 화면에 기본 출력 하도록 한다.

	//메시지 전송
	//&msg : 메세지가 저장된 MSG 구조체에 대한 포인터
	//NULL : 메시지가 발생한 윈도우 핸들
	//0 : 얻어올 메시지의 범위에서 최소 정수값
	//0 : 얻어올 메시지의 범위에서 최대 정수값
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //두 메시지를 하나로 변형할 때 사용
		DispatchMessage(&msg); //메시지 처리하는 함수에 메시지 보냄
	}
	return (int)msg.wParam;
}
//메세지 처리 부분, 콜백 함수 명시
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT rectView; //윈도우 핸들과 크기를 저장할 변수
	static bool flag;

	switch (iMsg)  //메시지 번호, 처리할 메시지만 case에 나열
	{
	case WM_CREATE: //윈도우 창 시작시 사용
		//윈도우 창의 크기를 얻는 함수
		GetClientRect(hwnd, &rectView);
		//원 중심점 시작 좌표
		x = 20; y = 20;

		break;

	case WM_PAINT: //윈도우 창 출력시 사용
		hdc = BeginPaint(hwnd, &ps);
		if (flag) //키가 눌리면 flag 가 true
		{
			SelectObject(hdc, GetStockObject(GRAY_BRUSH)); //회색으로 칠해라~
		}
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYUP: //키가 올라가면 
		flag = false;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_KEYDOWN: //키가 내려가면
		if (wParam == VK_RIGHT ) //오른쪽 키
		{
			flag = true;
			x += 40;
			if (x + 20 > rectView.right) x -= 40; //오른쪽 경계를 만나면 더이상 이동 안함
		}
		else if (wParam == VK_LEFT) //왼쪽 키
		{
			flag = true;
			x -= 40;
			if (x < rectView.left) x = 20; //왼쪽 경계를 만나면 더이상 이동 안함
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY: //윈도우 창 종료시 사용
		PostQuitMessage(0);  //반복 종료를 위해 0 반환
		break;
	default:
		break;
	}

	//나머지는 커널이 처리하도록 메시지 전달
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}