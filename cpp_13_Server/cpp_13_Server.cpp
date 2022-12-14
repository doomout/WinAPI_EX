#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>

//프로젝트 -> 속성 -> 링커 -> 명령줄에 ws2_32.lib를 추가 해야 한다.
//소켓 프로그래밍은 WinMain 이 아닌 main으로 해야 에러가 나지 않는다.
int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	WSADATA wsadata;
	SOCKET s;
	TCHAR message[300];
	SOCKADDR_IN addr = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 2000;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	if (listen(s, 5) == -1)
		return 0;
	do
	{
		SOCKADDR_IN c_addr;
		char buffer[100];
#ifdef _UNICODE
		TCHAR wbuffer[100];
#endif
		int msgLen;
		int size = sizeof(c_addr);
		SOCKET cs = accept(s, (LPSOCKADDR)&c_addr, &size);
		msgLen = recv(cs, buffer, 100, 0);
		buffer[msgLen] = NULL;
#ifdef _UNICODE
		msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), wbuffer, msgLen);
		wbuffer[msgLen] = NULL;
		_stprintf_s(message, _T("클라이언트 메시지: %s, 서버를 종료하시겠습니까?"),
			wbuffer);
#else
		sprintf_s(message, _T("클라이언트 메시지: %s, 서버를 종료하시겠습니까?"),
			buffer);
#endif
	} while (MessageBox(NULL, message, _T("Server 메시지"), MB_YESNO) == IDNO);
	closesocket(s);
	WSACleanup();
	return 1;
}