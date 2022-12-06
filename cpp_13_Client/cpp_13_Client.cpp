#include <windows.h>
#include <TCHAR.H>

//프로젝트 -> 속성 -> 링커 -> 명령줄에 ws2_32.lib를 추가 해야 한다.
//소켓 프로그래밍은 WinMain 이 아닌 main으로 해야 에러가 나지 않는다.
int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WSADATA wsadata;
	SOCKET s;
	SOCKADDR_IN addr = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 2000; //임의 포트 번호
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(s, (LPSOCKADDR)&addr, sizeof(addr));
	closesocket(s);
	WSACleanup();
	return 0;
}