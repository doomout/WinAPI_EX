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

//콜백 함수 선언
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//비트맵
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

	hInst = hInstance;
	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR5_1));
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
		if (!TranslateAccelerator(hwnd, hAcc, &msg)) //단축키 검사
		{
			TranslateMessage(&msg); //두 메시지를 하나로 변형할 때 사용
			DispatchMessage(&msg); //메시지 처리하는 함수에 메시지 보냄
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

//메세지 처리 부분, 콜백 함수 명시
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
	TCHAR word[] = _T("장원영~~ >.<");

	TCHAR str[100], lpstrFile[100] = _T(""); //파일 경로 저장을 위한 배열
	TCHAR filter[] = _T("전체 파일(*.*) \0*.*\0Text File\0*.txt; *.doc\0");

	//폰트 관련 변수
	CHOOSEFONT FONT;
	static COLORREF  fColor;
	HFONT hFont, OldFont;
	static LOGFONT LogFont;

	//컬러 변경 관련 변수
	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	int i;

	//원 선택 관련 변수
	static HMENU hMenu, hSubMenu;
	int mx, my;
	static BOOL Select; //원 클릭 했을 때 원의 선택 여부
	static BOOL Copy;
	static int x, y;

	switch (iMsg)  //메시지 번호, 처리할 메시지만 case에 나열
	{
	case WM_CREATE: //윈도우 창 시작시 사용
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

		// 버퍼(hBit1)가 다 비워지면 hdc와 호환 되도록 만든다.
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


	case WM_COMMAND: //메뉴 항목 선택시 사용
		if (LOWORD(wParam) == ID_EDITCOPY)
		{
			Copy = TRUE;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;

		switch (LOWORD(wParam)) //어떤 메뉴 항목이 선택 되었는지 판단.
		{
		case ID_FILENEW: //새 파일
			MessageBox(hwnd, _T("새 파일을 열겠습니까?"), _T("새 파일 선택"), MB_OKCANCEL);
			break;

		case ID_FILEOPEN: //파일 열기
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
				_stprintf_s(str, _T("%s 파일로 저장하겠습니까?"), SFN.lpstrFile);
				MessageBox(hwnd, str, _T("저장하기 선택"), MB_OK);
			}
			break;

		case ID_EXIT:
			answer = MessageBox(hwnd, _T("파일을 저장하고 끝내겠습니까?"), _T("끝내기 선택"), MB_YESNOCANCEL);
			if (answer == IDYES || answer == IDNO)
			{
				PostQuitMessage(0);
			}
			break;
		}
		break;

	case WM_DESTROY: //윈도우 창 종료시 사용
		if (hBit1) DeleteObject(hBit1);
		DeleteObject(hBit2);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);  //반복 종료를 위해 0 반환
		break;
	}

	//나머지는 커널이 처리하도록 메시지 전달
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}