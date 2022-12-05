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

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU_11));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우의 크기를 변경하면 다시 그리는 형태의 윈도우를 뜻한다.
	WndClass.lpfnWndProc = FrameWndProc; //메세지 처리를 위한 함수
	WndClass.cbClsExtra = 0; //클래스를 위한 여분의 메모리를 사용하지 않음
	WndClass.cbWndExtra = 0; //윈도우를 위한 여분의 메모리를 사용하지 않음
	WndClass.hInstance = hInstance; //WinMain  첫번째 매개변수
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //아이콘
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //커서
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //바탕색
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU_11); //메뉴 사용
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

HWND ChildHwnd[2];
//클라이언트 윈도우를 프레임 윈도우에 만들어 주기 위한 함수
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
				WS_EX_CLIENTEDGE,  // 경계가 약간 들어간 입체 형태
				_T("Child Window Class Name"), //윈도우 클래스의 이름
				NULL, //윈도우의 타이틀 바에 들어갈 이름이지만 팝업 형태가 아니기에 생략
				WS_CHILD | WS_VISIBLE, //생성되는 윈도우가 팝업이 아니고 자식 윈도우 형태
				0, //윈도우가 나타날 위치 x축
				0,  //윈도우가 나타날 위치 y축
				rectView.right, //생성될 윈도우의 너비
				rectView.bottom / 2 - 1, //생성될 윈도우의 높이로 메인 윈도우의 절반
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

		case WM_DESTROY: //끝내기
			PostQuitMessage(0);
			return 0;		
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
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