#include <windows.h>
#include <TCHAR.H>

//������Ʈ -> �Ӽ� -> ��Ŀ -> ����ٿ� ws2_32.lib�� �߰� �ؾ� �Ѵ�.
//���� ���α׷����� WinMain �� �ƴ� main���� �ؾ� ������ ���� �ʴ´�.
int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WSADATA wsadata;
	SOCKET s;
	SOCKADDR_IN addr = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 2000; //���� ��Ʈ ��ȣ
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(s, (LPSOCKADDR)&addr, sizeof(addr));
	closesocket(s);
	WSACleanup();
	return 0;
}