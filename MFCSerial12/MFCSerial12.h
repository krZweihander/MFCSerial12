// MFCSerial12.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCSerial12App:
// �� Ŭ������ ������ ���ؼ��� MFCSerial12.cpp�� �����Ͻʽÿ�.
//

class CMFCSerial12App : public CWinApp
{
public:
	CMFCSerial12App();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCSerial12App theApp;