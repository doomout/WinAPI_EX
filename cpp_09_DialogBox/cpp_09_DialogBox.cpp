#include <Windows.h>
#include <TCHAR.H>
#include  "resource.h"
#include <stdio.h>

//콜백 함수 선언
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//대화 상자
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_6Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

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

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우의 크기를 변경하면 다시 그리는 형태의 윈도우를 뜻한다.
	WndClass.lpfnWndProc = WndProc; //메세지 처리를 위한 함수
	WndClass.cbClsExtra = 0; //클래스를 위한 여분의 메모리를 사용하지 않음
	WndClass.cbWndExtra = 0; //윈도우를 위한 여분의 메모리를 사용하지 않음
	WndClass.hInstance = hInstance; //WinMain  첫번째 매개변수
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);  //아이콘은 물음표료 변경
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM); //커서를 아이빔(대문자 I)로 변경
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //바탕색은 기본으로 변경
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //메뉴 사용
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass); //커널에 등록한다.
	hwnd = CreateWindow(
		_T("Window Class Name"),  //윈도우 클래스 이름(유니 코드로 변환 하기 위해 _T 붙임)
		_T("대화상자"), //윈도우 타이틀 이름(유니 코드로 변환 하기 위해 _T 붙임)
		WS_OVERLAPPEDWINDOW, //윈도우 스타일(최소, 최대화, 닫기 버튼)
		600, //윈도우 위치 x 좌표(기본), 기본을 쓰려면 CW_USEDEFAULT 를 쓴다.
		200, //윈도우 위치 y 좌표(기본)
		500, //윈도우 가로 크기(기본)
		300, //윈도우 세로 크기(기본)
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
	switch (iMsg)  //메시지 번호, 처리할 메시지만 case에 나열
	{
	case WM_CREATE: //윈도우 창 시작시 사용
		break;

	case WM_COMMAND: //메뉴 항목 선택시 사용
		switch (LOWORD(wParam))
		{
		case ID_6_3_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_3), hwnd, (DLGPROC)&Dlg6_3Proc);
			break;
		case ID_6_4_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_4), hwnd, (DLGPROC)&Dlg6_4Proc);
			break;
		case ID_6_5_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_5), hwnd, (DLGPROC)&Dlg6_5Proc);
			break;
		case ID_6_6_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_6), hwnd, (DLGPROC)&Dlg6_6Proc);
			break;
		}
		break;

	case WM_DESTROY: //윈도우 창 종료시 사용
		PostQuitMessage(0);  //반복 종료를 위해 0 반환
		break;
	}

	//나머지는 커널이 처리하도록 메시지 전달
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

//6-3 대화 상자(버튼)
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hButton;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		hButton = GetDlgItem(hDlg, ID_PAUSE);
		EnableWindow(hButton, FALSE);
		return 1;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_START:
			hButton = GetDlgItem(hDlg, ID_START);
			EnableWindow(hButton, FALSE);
			hButton = GetDlgItem(hDlg, ID_PAUSE);
			EnableWindow(hButton, TRUE);
			break;

		case ID_PAUSE:
			hButton = GetDlgItem(hDlg, ID_START);
			EnableWindow(hButton, TRUE);
			hButton = GetDlgItem(hDlg, ID_PAUSE);
			EnableWindow(hButton, FALSE);
			break;

		case ID_CLOSE:
			EndDialog(hDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

//6-4 대화 상자(에디트)
BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR word[100];
	
	switch (iMsg)
	{
	case WM_INITDIALOG:
		return 1;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_COPY:
			GetDlgItemText(hDlg, IDC_EDIT_SOURCE, word, 100); //여기서 받아서 get
			SetDlgItemText(hDlg, IDC_EDIT_COPY, word); //여기에 그대로 복사 set
			break;

		case ID_BUTTON_CLEAR:
			SetDlgItemText(hDlg, IDC_EDIT_SOURCE, _T("")); 
			SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
			break;

		case ID_BUTTON_END:
			EndDialog(hDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

//6-5 대화 상자 (체크박스, 라디오 버튼)
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int Check[3], Radio;
	TCHAR hobby[][30] = { _T("독서"), _T("음악감상"), _T("인터넷") };
	TCHAR sex[][30] = { _T("여자"), _T("남자") };
	TCHAR output[200];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE); //기본으로 여자로 선택
		return 1;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHECK_READING:
			Check[0] = 1 - Check[0];
			break;

		case IDC_CHECK_MUSIC:
			Check[1] = 1 - Check[1];
			break;

		case IDC_CHECK_INTERNET:
			Check[2] = 1 - Check[2];
			break;

		case IDC_RADIO_FEMALE:
			Radio = 0;
			break;
		case IDC_RADIO_MALE:
			Radio = 1;
			break;
		case ID_BUTTON_OUTPUT:
			_stprintf_s(output, _T("선택한 취미는 %s %s %s 입니다.\r\n") 
				_T("선택한 성별은 %s입니다."), 
				Check[0]?hobby[0]:_T(""), Check[1] ? hobby[1] : _T(""), 
				Check[2] ? hobby[2] : _T(""), sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case ID_BUTTON_CLOSE:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

//6-6 대화 상자 (콤보 박스)
BOOL CALLBACK Dlg6_6Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hCombo;
	static int selection;
	TCHAR name[20];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		hCombo = GetDlgItem(hDlg, IDC_COMBO_LIST);
		return 1;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name); //항목을 추가한다.
			return 0;

		case IDC_BUTTON_DELETE:
			SendMessage(hCombo, CB_DELETESTRING, selection, 0); //항목 하나를 제거한다.
			return 0;

		case IDC_COMBO_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0); //선택한 인덱스 번호를 얻는다.
			break;

		case IDCLOSE:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}
