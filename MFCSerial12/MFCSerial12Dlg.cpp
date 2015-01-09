// MFCSerial12Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCSerial12.h"
#include "MFCSerial12Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSerial12Dlg ��ȭ ����




CMFCSerial12Dlg::CMFCSerial12Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCSerial12Dlg::IDD, pParent)
	, m_nPort(0)
	, m_nlstTxSelectedCol(0)
	, m_nlstTxSelectedRow(0)
	, m_sReadstack(_T(""))
	, m_btxtTxFocused(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerial12Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_lstRx, m_lstRx);
	DDX_Control(pDX, IDC_lstTx, m_lstTx);
	DDX_Control(pDX, IDC_cmbTx, m_cmbTx);
	DDX_Control(pDX, IDC_txtTx, m_txtTx);
}

BEGIN_MESSAGE_MAP(CMFCSerial12Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SERIAL(OnSerialMsg)
	ON_BN_CLICKED(IDC_btnPortOpen, &CMFCSerial12Dlg::OnBnClickedbtnportopen)
	ON_BN_CLICKED(IDC_btnPortClose, &CMFCSerial12Dlg::OnBnClickedbtnportclose)
	ON_NOTIFY(NM_CLICK, IDC_lstTx, &CMFCSerial12Dlg::OnNMClicklsttx)
	ON_BN_CLICKED(IDC_btnTxInput, &CMFCSerial12Dlg::OnBnClickedbtntxinput)
	ON_BN_CLICKED(IDC_btnTx, &CMFCSerial12Dlg::OnBnClickedbtntx)
	ON_EN_SETFOCUS(IDC_txtTx, &CMFCSerial12Dlg::OnEnSetfocustxttx)
	ON_EN_KILLFOCUS(IDC_txtTx, &CMFCSerial12Dlg::OnEnKillfocustxttx)
END_MESSAGE_MAP()


// CMFCSerial12Dlg �޽��� ó����

BOOL CMFCSerial12Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	if (CSerial::CheckPort(_T("COM1")) == CSerial::EPortAvailable)
		m_nPort = 1;
	else if (CSerial::CheckPort(_T("COM2")) == CSerial::EPortAvailable)
		m_nPort = 2;
	else if (CSerial::CheckPort(_T("COM3")) == CSerial::EPortAvailable)
		m_nPort = 3;
	else if (CSerial::CheckPort(_T("COM4")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else if (CSerial::CheckPort(_T("COM5")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else if (CSerial::CheckPort(_T("COM6")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else if (CSerial::CheckPort(_T("COM7")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else if (CSerial::CheckPort(_T("COM8")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else if (CSerial::CheckPort(_T("COM9")) == CSerial::EPortAvailable)
		m_nPort = 4;
	else
		m_nPort = 1;

	m_eBaudrate = CSerial::EBaud9600;	// 9600 bits/sec

	initial();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCSerial12Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCSerial12Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMFCSerial12Dlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
		{
			switch(pMsg->wParam)
			{
				case VK_ESCAPE:
				{
					::TranslateMessage(pMsg);
					::DispatchMessage(pMsg);
					
					return TRUE;
				} 
				case VK_RETURN:
				{
					::TranslateMessage(pMsg);
					::DispatchMessage(pMsg);

					if (m_btxtTxFocused)
						OnBnClickedbtntxinput();
					
					return TRUE;
				}     
			}
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

CString CMFCSerial12Dlg::hex(int i)
{
	CString out;
	out.Format(_T("%X"), i);
	return (out);
}

int CMFCSerial12Dlg::dex(CString hexStr)
{
	wchar_t *end = NULL;
	long value = wcstol (hexStr, &end, 16);
	return value;
}

void CMFCSerial12Dlg::initial(void)
{
	//initGrid(m_lstRx, 18, 5);
	//initGrid(m_lstTx, 18, 5);

	m_lstRx.DeleteAllItems();

	m_lstRx.SetExtendedStyle(LVS_EX_GRIDLINES);
	
	m_lstRx.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	for (int j = 0; j <= 4; j++)
	{
		m_lstRx.InsertItem(j, _T(""));
	}
	for (int i = 1; i <= 18; i++)
	{
		CString tmp;
		tmp.Format(_T("D%d"), i);
		m_lstRx.InsertColumn(i, tmp, LVCFMT_CENTER, 35, -1);

		for (int j = 0; j <= 4; j++)
		{
			m_lstRx.SetItem(j, i, LVIF_TEXT, _T("0"), 0, 0, 0, NULL);
		}
	}

	m_lstTx.DeleteAllItems();

	m_lstTx.SetExtendedStyle(m_lstTx.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_lstTx.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	for (int j = 0; j <= 4; j++)
	{
		m_lstTx.InsertItem(j, _T(""));
	}
	for (int i = 1; i <= 18; i++)
	{
		CString tmp;
		tmp.Format(_T("D%d"), i);
		m_lstTx.InsertColumn(i, tmp, LVCFMT_CENTER, 35, -1);

		for (int j = 0; j <= 4; j++)
		{
			m_lstTx.SetItem(j, i, LVIF_TEXT, _T("0"), 0, 0, 0, NULL);
		}
	}
	
	m_cmbTx.SendMessage(CB_SETCURSEL, 0, 0);
}

LRESULT CMFCSerial12Dlg::OnSerialMsg (WPARAM wParam, LPARAM /*lParam*/)
{
	CSerial::EEvent eEvent = CSerial::EEvent(LOWORD(wParam));
	CSerial::EError eError = CSerial::EError(HIWORD(wParam));
	
	if (eEvent & CSerial::EEventRecv)
	{
		DWORD dwRead;
		CString szString;
		char szData[101];
		const int nBuflen = sizeof(szData)-1;

		// Obtain the data from the serial port
		do
		{
			m_Serial.Read(szData,nBuflen,&dwRead);
			szData[dwRead] = '\0';

			for (DWORD dwChar=0; dwChar<dwRead; dwChar++)
			{
				szString += szData[dwChar];
				if(szData[dwChar] == '\r')
					szString += '\n';
			}

			process(szString);
		} while (dwRead == nBuflen);
	}
	return 0;
}

void CMFCSerial12Dlg::process(CString instr)
{
	m_sReadstack += instr;
	CString parser = _T("*;");
	
	if (m_sReadstack.Find(parser) != -1)
	{
		CString nowreading;
		CString afterreading;
		CString* hdata;
		nowreading = m_sReadstack.Left(m_sReadstack.Find(parser));
		m_sReadstack = m_sReadstack.Mid(m_sReadstack.Find(parser) + 2);
		hdata = new CString[nowreading.GetLength()];
		for (int i = 0; i < nowreading.GetLength(); i++)
		{
			hdata[i] = nowreading.Mid((i * 2), 2);
		}
		if (hdata[0] == _T("63"))
			done(hdata, nowreading.GetLength());
	}
}

void CMFCSerial12Dlg::done(CString* hdata, int length)
{
	int* idata = new int[length];

	for (int i = 0; i < length; i++)
	{
		idata[i] = dex(hdata[i]);
	}
	for (int i = 1; i < length; i++)
	{
		CString prnt;
		prnt.Format(_T("%d"), idata[i]);
		for (int j = 4; j >= 1; j--)
		{
			m_lstRx.SetItemText(j, i, m_lstRx.GetItemText(j - 1, i));
		}
		m_lstRx.SetItemText(0, i, prnt);
	}
}

CString CMFCSerial12Dlg::sendformat(int* idata)
{
	CString* hdata = new CString[20];
	for (int i = 0; i <= 18; i++)
	{
		hdata[i] = hex(idata[i]);
		hdata[i] = _T("00") + hdata[i];
		hdata[i] = hdata[i].Right(2);
	}
	hdata[19] = _T("*;");
	
	CString out = _T("");
	for (int i = 0; i <= 19; i++)
	{
		out += hdata[i];
	}

	return out;
}

int CMFCSerial12Dlg::getCS(int* idata)
{
	int sum = 0;
	for (int i = 0; i <= 17; i++)
	{
		sum += idata[i];
	}
	return sum;
}

void CMFCSerial12Dlg::send(CString str)
{
	char* ss = LPSTR(LPCTSTR(str));
	m_Serial.Write(ss, str.GetLength() * 2);
}

void CMFCSerial12Dlg::OnBnClickedbtnportopen()
{
	CString szPort;
	szPort.Format(_T("COM%d"), m_nPort);
	if (m_Serial.Open(szPort,this) != ERROR_SUCCESS)
	{
		szPort += _T(" ��Ʈ�� �� �� �����ϴ�.");
		AfxMessageBox((LPCTSTR)szPort,MB_ICONSTOP|MB_OK);
		return;
	}

	m_Serial.Setup(m_eBaudrate,
		CSerial::EData8,
		CSerial::EParNone,
		CSerial::EStop1);

	m_Serial.SetupHandshaking(CSerial::EHandshakeOff);

	GetDlgItem(IDC_btnPortOpen)->EnableWindow(false);
	GetDlgItem(IDC_btnPortClose)->EnableWindow(true);
}

void CMFCSerial12Dlg::OnBnClickedbtnportclose()
{
	m_Serial.Close();

	GetDlgItem(IDC_btnPortOpen)->EnableWindow(true);
	GetDlgItem(IDC_btnPortClose)->EnableWindow(false);
}

void CMFCSerial12Dlg::OnNMClicklsttx(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (pNMItemActivate->iItem == -1)
		return;
	
	m_nlstTxSelectedCol = pNMItemActivate->iSubItem;
	m_nlstTxSelectedRow = pNMItemActivate->iItem;

	CString str = m_lstTx.GetItemText(m_nlstTxSelectedRow, m_nlstTxSelectedCol);
	SetDlgItemText(IDC_txtTx, str);
	
	GetDlgItem(IDC_txtTx)->SetFocus();
	m_txtTx.SetSel(5, 0);
	
	*pResult = 0;
}

void CMFCSerial12Dlg::OnBnClickedbtntxinput()
{
	CString str = _T("");
	GetDlgItemText(IDC_txtTx, str);

	int num = _ttoi(str);

	if (num > 255)
		num = 255;
	else if (num < 0)
		num = 0;

	str.Format(_T("%d"), num);
	m_lstTx.SetItemText(m_nlstTxSelectedRow, m_nlstTxSelectedCol, str);

	if (m_nlstTxSelectedCol != 18)
	{
		int* idata = new int[18];
		idata[0] = 99;
		for (int i = 0; i <= 16; i++)
		{
			CString sitem = m_lstTx.GetItemText(m_nlstTxSelectedRow, i + 1);
			idata[i + 1] = _ttoi(sitem);
		}
		int cs = getCS(idata);
		
		str.Format(_T("%d"), cs);
		m_lstTx.SetItemText(m_nlstTxSelectedRow, 18, str);
	}
}

void CMFCSerial12Dlg::OnBnClickedbtntx()
{
	if (!m_Serial.IsOpen()) return;

	CString cmbstr;
	GetDlgItemText(IDC_cmbTx, cmbstr);
	int row = _ttoi(cmbstr);
	row--;

	int* idata = new int[18];
	idata[0] = 99;
	for (int i = 0; i <= 17; i++)
	{
		CString sitem = m_lstTx.GetItemText(row, i + 1);
		idata[i + 1] = _ttoi(sitem);
	}

	send(sendformat(idata));
}

void CMFCSerial12Dlg::OnEnSetfocustxttx()
{
	m_btxtTxFocused = true;
}

void CMFCSerial12Dlg::OnEnKillfocustxttx()
{
	m_btxtTxFocused = false;
}