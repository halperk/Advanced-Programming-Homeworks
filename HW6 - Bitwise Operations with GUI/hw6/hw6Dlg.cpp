/*******************************************

CS 204 (Fall 2021-2022)
Homework #6 - Bitwise operations with GUI
Huseyin Alper Karadeniz (28029)
Date: 12/26/2021

********************************************/

// hw6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "hw6.h"
#include "hw6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Chw6Dlg dialog


Chw6Dlg::Chw6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Chw6Dlg::IDD, pParent)
	, operandType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chw6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, operand1);
	DDX_Control(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_CHECK1, shiftCheck);
	DDX_Control(pDX, IDC_BUTTON1, computeButton);
	DDX_Control(pDX, IDC_COMBO1, shiftDirection);
	DDX_Control(pDX, IDC_LIST2, list);
	DDX_Control(pDX, IDC_EDIT4, shiftAmount);
	DDX_Radio(pDX, IDC_RADIO1, operandType);
}

BEGIN_MESSAGE_MAP(Chw6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST2, &Chw6Dlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON1, &Chw6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &Chw6Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Chw6Dlg message handlers

BOOL Chw6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	shiftDirection.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Chw6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Chw6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR Chw6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Chw6Dlg::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}

static int maxSize = 0; /* An integer to keep size of the string that have maximum length. */

void Chw6Dlg::OnBnClickedButton1()
{

	CDC *pDC = GetDC(); /* Gets a DC to get the length of the string. */
	CSize cz; /* Defines an object that keeps the length of the string. */

	CString op1, op2, sDirection, sAmount, result;

	operand1.GetWindowTextW(op1); /* Gets the value of the first operand. */
	operand2.GetWindowTextW(op2); /* Gets the value of the second operand. */

	if(op1 == "" || op2 == "") { /* Detects if two of the operands entered by the user. */
		list.AddString(_T("At least 1 operand was not entered"));
		return; /* Exits from the function if at least one of the operands is not entered. */
	}

	/* Converts CString operands to unsigned int to use them in further operations. */
	unsigned int operandValue1 = _tcstoul(op1,nullptr,10);
	unsigned int operandValue2 = _tcstoul(op2,nullptr,10);

	/* Initializes two operands which will be used at the end of the function. */
	unsigned int latestOperand1 = operandValue1, latestOperand2 = operandValue2;

	if(shiftCheck.GetCheck() == 1) { /* Detects if shifting box checked, or not. */
		int selectedIdx = shiftDirection.GetCurSel(); /* Gets the index of the list that was selected from the list. */
		shiftDirection.GetLBText(selectedIdx, sDirection); /* Gets the string at the given index and saves it. */
		shiftAmount.GetWindowTextW(sAmount); /* Gets the shift amount entered by the user. */

		if(sAmount == "") { /* Detects if any shift amount is entered by the user, or not. */
			list.AddString(_T("Specify by how many bits you want to shift"));
			return; /* Exits from the function if shift box is checked but no value was entered. */
		}

		unsigned int shiftingAmount = _tcstoul(sAmount,nullptr,10); /* Defines shift amount as an unsigned int. */

		/* Performs necessary bit operations with given operands and shifting amount. */
		if(sDirection == "Left") { /* Detects if shifting to left is selected. */
			latestOperand1 = operandValue1 << shiftingAmount;
			latestOperand2 = operandValue2 << shiftingAmount;
		} else if(sDirection == "Right") { /* Detects if shifting to right is selected. */
			latestOperand1 = operandValue1 >> shiftingAmount;
			latestOperand2 = operandValue2 >> shiftingAmount;
		}
	}

	UpdateData(TRUE); /* Updates the data to get the latest version of especially selected radio buttons. */
	
	/* Converts latest operands to the CString format to used them in the further operations. */
	CString latestOp1C, latestOp2C, resultCString;
	latestOp1C.Format(_T("%u"), latestOperand1);
	latestOp2C.Format(_T("%u"), latestOperand2);

	/* Creates a string with necessary operation, and adds it to the list to show the operation to the user. */
	unsigned int resultInt;
	if(operandType == 0) { /* Detects if the AND operator is selected from the radio buttons. */
		resultInt = latestOperand1 & latestOperand2; /* Makes the calculation with AND operator. */
		result.Format(_T("%u"), resultInt); /* Saves the result of the operation as a CString. */
		resultCString = latestOp1C + _T(" AND ") + latestOp2C + _T(" = ") + result;
		list.AddString(resultCString); /* Adds the string to the list. */
	}
	if(operandType == 1) { /* Detects if the OR operator is selected from the radio buttons. */
		resultInt = latestOperand1 | latestOperand2; /* Makes the calculation with OR operator. */
		result.Format(_T("%u"), resultInt); /* Saves the result of the operation as a CString. */
		resultCString = latestOp1C + _T(" OR ") + latestOp2C + _T(" = ") + result;
		list.AddString(resultCString); /* Adds the string to the list. */
	}
	if(operandType == 2) { /* Detects if the XOR operator is selected from the radio buttons. */
		resultInt = latestOperand1 ^ latestOperand2; /* Makes the calculation with XOR operator. */
		result.Format(_T("%u"), resultInt); /* Saves the result of the operation as a CString. */
		resultCString = latestOp1C + _T(" XOR ") + latestOp2C + _T(" = ") + result;
		list.AddString(resultCString); /* Adds the string to the list. */
	}	/* Updates the lenght of the horizontal scrollbar by some operations. */	cz = pDC->GetTextExtent(resultCString); /* Finds the size of the string and stores it inside cz. */
	if(cz.cx > maxSize) { /* Checks if the horizontal length of the string (cz.cx) is larger than the maximum. */
		maxSize = cz.cx; /* Updates maximum size with cz.cx since it is larger than the maximum value. */
	}
	list.SetHorizontalExtent(maxSize); /* Updates the horizontal scrollbar length of the list. */
}

void Chw6Dlg::OnBnClickedCheck1()
{
	/* Enables and disables the shift direction and amount sections accordingly. */
	if(shiftCheck.GetCheck()) { /* Enables them if shift checkbox is checked. */
		shiftDirection.EnableWindow(TRUE);
		shiftAmount.EnableWindow(TRUE);
	} else { /* Disables them if shift checkbox is not checked. */
		shiftDirection.EnableWindow(FALSE);
		shiftAmount.EnableWindow(FALSE);
	}
}
