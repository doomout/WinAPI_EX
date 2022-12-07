#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>

//������Ʈ -> �Ӽ� -> ��Ŀ -> ����ٿ� ws2_32.lib�� �߰� �ؾ� �Ѵ�.
//���� ���α׷����� WinMain �� �ƴ� main���� �ؾ� ������ ���� �ʴ´�.
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
		_stprintf_s(message, _T("Ŭ���̾�Ʈ �޽���: %s, ������ �����Ͻðڽ��ϱ�?"),
			wbuffer);
#else
		sprintf_s(message, _T("Ŭ���̾�Ʈ �޽���: %s, ������ �����Ͻðڽ��ϱ�?"),
			buffer);
#endif
	} while (MessageBox(NULL, message, _T("Server �޽���"), MB_YESNO) == IDNO);
	closesocket(s);
	WSACleanup();
	return 1;
}