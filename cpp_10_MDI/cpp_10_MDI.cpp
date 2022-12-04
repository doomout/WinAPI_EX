#include <Windows.h>
#include <TCHAR.H>
#include  "resource.h"

HINSTANCE hInst;

//콜백 함수 선언
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//메인 부분 
//hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID로 메모리에서의 위치
//lpszCmdLine : 명령 라인에서 프로그램 구동시 전달할 문자열
//nCmdShow : 윈도우에 출력하는 형태
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	HACCEL hAcc;

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU7_1));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우의 크기를 변경하면 다시 그리는 형태의 윈도우를 뜻한다.
	WndClass.lpfnWndProc = FrameWndProc; //메세지 처리를 위한 함수
	WndClass.cbClsExtra = 0; //클래스를 위한 여분의 메모리를 사용하지 않음
	WndClass.cbWndExtra = 0; //윈도우를 위한 여분의 메모리를 사용하지 않음
	WndClass.hInstance = hInstance; //WinMain  첫번째 매개변수
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //아이콘
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //커서
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //바탕색
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1); //메뉴 사용
	WndClass.lpszClassName = _T("Window Class Name");
	
	RegisterClass(&WndClass);
	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Child Window Class Name");
	RegisterClass(&WndClass); //커널에 등록한다.

	hwnd = CreateWindow(
		_T("Window Class Name"),  //윈도우 클래스 이름(유니 코드로 변환 하기 위해 _T 붙임)
		_T("Main Window Title"), //윈도우 타이틀 이름(유니 코드로 변환 하기 위해 _T 붙임)
		WS_OVERLAPPEDWINDOW, //윈도우 스타일(최소, 최대화, 닫기 버튼)
		CW_USEDEFAULT, //윈도우 위치 x 좌표(기본), 기본을 쓰려면 CW_USEDEFAULT 를 쓴다.
		CW_USEDEFAULT, //윈도우 위치 y 좌표(기본)
		CW_USEDEFAULT, //윈도우 가로 크기(기본)
		CW_USEDEFAULT, //윈도우 세로 크기(기본)
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

//클라이언트 윈도우를 프레임 윈도우에 만들어 주기 위한 함수
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient;
	CLIENTCREATESTRUCT clientcreate;
	MDICREATESTRUCT mdicreate;
	HWND hwndChild;

	switch (iMsg)
	{
	case WM_CREATE:
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hwnd), 0);
		clientcreate.idFirstChild = 100;
		hwndClient = CreateWindow(
			_T("MDICLIENT"), NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0,
			hwnd,
			NULL,
			hInst,
			(LPSTR) &clientcreate
		);
		ShowWindow(hwndClient, SW_SHOW);
		return 0;

	case WM_COMMAND: //메뉴 항목 선택시 사용
		switch (LOWORD(wParam))
		{
		case ID_FILENEW: //새 창
			mdicreate.szClass = _T("Child Window Class Name");
			mdicreate.szTitle = _T("Child Window Title Name");
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;
			hwndChild = (HWND)SendMessage(hwndClient, WM_MDICREATE, 0, 
				(LPARAM)(LPMDICREATESTRUCT) &mdicreate);
			return 0;
		case ID_WINDOW_CLOSE: //창닫기
			hwndChild = (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0);
			if (SendMessage(hwndChild, WM_QUERYENDSESSION, 0, 0))
				SendMessage(hwndClient, WM_MDIDESTROY, (WPARAM)hwndChild, 0);
			return 0;
		case ID_TILE: //바둑판식 정렬
			SendMessage(hwndClient, WM_MDITILE, 0, 0);
			return 0;
		case ID_CASCADE: //계단식 정렬
			SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
			return 0;
		case ID_ARRANGE: //아이콘 정열
			SendMessage(hwndClient, WM_MDIICONARRANGE, 0, 0);
			return 0;
		case ID_EXIT:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY: //끝내기
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hwnd, hwndClient, iMsg, wParam, lParam);
}
//메세지 처리 부분, 콜백 함수 명시
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)  //메시지 번호, 처리할 메시지만 case에 나열
	{
	case WM_CREATE: //윈도우 창 시작시 사용
		break;

	case WM_COMMAND: //메뉴 항목 선택시 사용
		//switch (LOWORD(wParam))
		//{
		//
		//}
		break;

	case WM_DESTROY: //윈도우 창 종료시 사용
		PostQuitMessage(0);  //반복 종료를 위해 0 반환
		break;
	}

	//나머지는 커널이 처리하도록 메시지 전달
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
	return DefMDIChildProc(hwnd, iMsg, wParam, lParam); //자식 윈도우 출력
}