
// hw6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Chw6Dlg dialog
class Chw6Dlg : public CDialogEx
{
// Construction
public:
	Chw6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HW6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList2();
	CEdit operand1;
	CEdit operand2;
	CButton shiftCheck;
	CButton computeButton;
	CComboBox shiftDirection;
	CListBox list;
	CEdit shiftAmount;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	int operandType;
};
