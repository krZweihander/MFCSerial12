// MFCSerial12Dlg.h : ��� ����
//

#pragma once

#include "..\Serial\SerialMFC.h"
#include "afxwin.h"
#include "afxcmn.h"

// CMFCSerial12Dlg ��ȭ ����
class CMFCSerial12Dlg : public CDialog
{
// �����Դϴ�.
public:
	CMFCSerial12Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCSERIAL12_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnBnClickedbtnportopen();
	afx_msg void OnBnClickedbtnportclose();
	afx_msg void OnNMClicklsttx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedbtntxinput();
	afx_msg void OnBnClickedbtntx();
	afx_msg void OnEnKillfocustxttx();
	afx_msg void OnEnSetfocustxttx();
	afx_msg LRESULT OnSerialMsg (WPARAM wParam, LPARAM /*lParam*/);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	void initial(void);
	void process(CString instr);
	void done(CString* hdata, int length);
	void send(CString str);
	CString sendformat(int* idata);
	int getCS(int* idata);
	CString hex(int i);
	int dex(CString hexStr);

	int m_nPort;
	CSerial::EBaudrate m_eBaudrate;
	CSerialMFC m_Serial;
	CListCtrl m_lstRx;
	CListCtrl m_lstTx;
	CEdit m_txtTx;
	int m_nlstTxSelectedCol;
	int m_nlstTxSelectedRow;
	CString m_sReadstack;
	bool m_btxtTxFocused;
	void autoPortOpen(void);
};
