#include <Windows.h>
#include <TCHAR.H>
#include  "resource.h"
#include <stdio.h>
#include <CommCtrl.h>

//�ݹ� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//��ȭ ����
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_6Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_7Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_8Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

//���� �κ� 
//hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID�� �޸𸮿����� ��ġ
//lpszCmdLine : ��� ���ο��� ���α׷� ������ ������ ���ڿ�
//nCmdShow : �����쿡 ����ϴ� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	HACCEL hAcc;

	hAcc = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //�������� ũ�⸦ �����ϸ� �ٽ� �׸��� ������ �����츦 ���Ѵ�.
	WndClass.lpfnWndProc = WndProc; //�޼��� ó���� ���� �Լ�
	WndClass.cbClsExtra = 0; //Ŭ������ ���� ������ �޸𸮸� ������� ����
	WndClass.cbWndExtra = 0; //�����츦 ���� ������ �޸𸮸� ������� ����
	WndClass.hInstance = hInstance; //WinMain  ù��° �Ű�����
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);  //�������� ����ǥ�� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM); //Ŀ���� ���̺�(�빮�� I)�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //�������� �⺻���� ����
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //�޴� ���
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass); //Ŀ�ο� ����Ѵ�.
	hwnd = CreateWindow(
		_T("Window Class Name"),  //������ Ŭ���� �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		_T("��ȭ����"), //������ Ÿ��Ʋ �̸�(���� �ڵ�� ��ȯ �ϱ� ���� _T ����)
		WS_OVERLAPPEDWINDOW, //������ ��Ÿ��(�ּ�, �ִ�ȭ, �ݱ� ��ư)
		600, //������ ��ġ x ��ǥ(�⺻), �⺻�� ������ CW_USEDEFAULT �� ����.
		200, //������ ��ġ y ��ǥ(�⺻)
		500, //������ ���� ũ��(�⺻)
		300, //������ ���� ũ��(�⺻)
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
	switch (iMsg)  //�޽��� ��ȣ, ó���� �޽����� case�� ����
	{
	case WM_CREATE: //������ â ���۽� ���
		break;

	case WM_COMMAND: //�޴� �׸� ���ý� ���
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
		case ID_6_7_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_7), hwnd, (DLGPROC)&Dlg6_7Proc);
			break;
		case ID_6_8_MENU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6_8), hwnd, (DLGPROC)&Dlg6_8Proc);
			break;
		}
		break;

	case WM_DESTROY: //������ â ����� ���
		PostQuitMessage(0);  //�ݺ� ���Ḧ ���� 0 ��ȯ
		break;
	}

	//�������� Ŀ���� ó���ϵ��� �޽��� ����
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

//6-3 ��ȭ ����(��ư)
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

//6-4 ��ȭ ����(����Ʈ)
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
			GetDlgItemText(hDlg, IDC_EDIT_SOURCE, word, 100); //���⼭ �޾Ƽ� get
			SetDlgItemText(hDlg, IDC_EDIT_COPY, word); //���⿡ �״�� ���� set
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

//6-5 ��ȭ ���� (üũ�ڽ�, ���� ��ư)
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int Check[3], Radio;
	TCHAR hobby[][30] = { _T("����"), _T("���ǰ���"), _T("���ͳ�") };
	TCHAR sex[][30] = { _T("����"), _T("����") };
	TCHAR output[200];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE); //�⺻���� ���ڷ� ����
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
			_stprintf_s(output, _T("������ ��̴� %s %s %s �Դϴ�.\r\n") 
				_T("������ ������ %s�Դϴ�."), 
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

//6-6 ��ȭ ���� (�޺� �ڽ�)
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
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name); //�׸��� �߰��Ѵ�.
			return 0;

		case IDC_BUTTON_DELETE:
			SendMessage(hCombo, CB_DELETESTRING, selection, 0); //�׸� �ϳ��� �����Ѵ�.
			return 0;

		case IDC_COMBO_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0); //������ �ε��� ��ȣ�� ��´�.
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

//6-7 ��ȭ ���� (����Ʈ �ڽ�)
BOOL CALLBACK Dlg6_7Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hList;
	static int selection;
	TCHAR name[20];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST_NAME);
		return 1;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name); //�׸��� �߰��Ѵ�.
			return 0;

		case IDC_BUTTON_DELETE:
			SendMessage(hList, LB_DELETESTRING, selection, 0); //�׸� �ϳ��� �����Ѵ�.
			return 0;

		case IDC_LIST_NAME:
			selection = (int)SendMessage(hList, LB_GETCURSEL, 0, 0); //������ �ε��� ��ȣ�� ��´�.
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

//6-8 ����Ʈ ��Ʈ�� �⺻ ����
void MakeColumn(HWND hDlg)
{
	LPCTSTR name[2] = { _T("�̸�"), _T("��ȭ��ȣ") };
	LVCOLUMN lvCol = { 0, };
	HWND hList;
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;

	for (size_t i = 0; i < 2; i++)
	{
		lvCol.cx = 90;
		lvCol.iSubItem = i;
		lvCol.pszText = (LPTSTR)name[i];
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
	}
}

//6-8 ����Ʈ ��Ʈ�� �Է� �Լ�
void InsertData(HWND hDlg)
{
	int count;
	LVITEM item;
	HWND hList;
	TCHAR name[20], phone[20];

	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));

	if (_tcscmp(name, _T("")) == 0) return;

	GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	count = ListView_GetItemCount(hList);
	item.mask = LVIF_TEXT;
	item.iItem = count;
	item.iSubItem = 0;
	item.pszText = name;
	ListView_InsertItem(hList, &item);
	ListView_SetItemText(hList, count, 1, phone);
}

//6-9 ����Ʈ ��Ʈ�� ���� �Լ�
int SelectItem(HWND hDlg, LPARAM lParam)
{
	LPNMLISTVIEW nlv;
	HWND hList;
	TCHAR name[20], phone[20];

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	nlv = (LPNMLISTVIEW)lParam;
	
	ListView_GetItemText(hList, nlv->iItem, 0, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, name);
	
	ListView_GetItemText(hList, nlv->iItem, 1, phone, 20);
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, phone);

	return(nlv->iItem);
}

//6-9 ����Ʈ ��Ʈ�� ���� �Լ�
void ModifyItem(HWND hDlg, int selection)
{
	static HWND hList;
	TCHAR name[20], phone[20];

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
	GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);
	
	if(_tcscmp(name, _T("")) == 0) return;

	ListView_SetItemText(hList, selection, 0, name);
	ListView_SetItemText(hList, selection, 1, phone);

	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));

	return;
}

//6-9 ����Ʈ ��Ʈ�� ���� �Լ�
void DeleteItem(HWND hDlg, int selection)
{
	static HWND hList;

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	ListView_DeleteItem(hList, selection);

	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));

	return;
}

#define UNSELECTED -1
//6-8 ��ȭ ���� (����Ʈ ��Ʈ��)
//vs 2022 ���� �������� ������ ���µ�
//�Ӽ� ->c/c++ -> ��� -> �ؼ���� -> �ƴϿ� �����ؾ� �Ѵ�.
BOOL CALLBACK Dlg6_8Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	HWND hList;
	static int selection;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		selection = UNSELECTED;
		MakeColumn(hDlg);
		return 1;

	case WM_NOTIFY:
		hdr = (LPNMHDR)lParam;
		hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
		if (hdr->hwndFrom == hList && hdr->code == LVN_ITEMCHANGING)
			selection = SelectItem(hDlg, lParam);
		return 1;
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_INSERT:
			InsertData(hDlg);
			return 0;

		case IDC_BUTTON_MODIFY:
			if (selection == UNSELECTED) break;
			ModifyItem(hDlg, selection);
			selection = UNSELECTED;
			return 0;

		case IDC_BUTTON_DELETE:
			if (selection == UNSELECTED) break;
			DeleteItem(hDlg, selection);
			selection = UNSELECTED;
			return 0;
		case IDCLOSE:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

