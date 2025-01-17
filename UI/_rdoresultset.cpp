// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "_rdoresultset.h"

// Dispatch interfaces referenced by this interface
#include "rdocolumns.h"
#include "_rdoconnection.h"
#include "rdopreparedstatement.h"


/////////////////////////////////////////////////////////////////////////////
// C_rdoResultset properties

/////////////////////////////////////////////////////////////////////////////
// C_rdoResultset operations

VARIANT C_rdoResultset::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CrdoColumns C_rdoResultset::GetRdoColumns()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CrdoColumns(pDispatch);
}

BOOL C_rdoResultset::GetBof()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL C_rdoResultset::GetBookmarkable()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL C_rdoResultset::GetEof()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL C_rdoResultset::GetLockEdits()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString C_rdoResultset::GetName()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL C_rdoResultset::GetTransactions()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetType()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetRowCount()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL C_rdoResultset::GetUpdatable()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL C_rdoResultset::GetRestartable()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetEditMode()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

float C_rdoResultset::GetPercentPosition()
{
	float result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetPercentPosition(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long C_rdoResultset::GetHStmt()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL C_rdoResultset::GetStillExecuting()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT C_rdoResultset::GetLastModified()
{
	VARIANT result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetBatchSize()
{
	long result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetBatchSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short C_rdoResultset::GetUpdateOperation()
{
	short result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetUpdateOperation(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short C_rdoResultset::GetUpdateCriteria()
{
	short result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetUpdateCriteria(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void C_rdoResultset::AddNew()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::Close()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::Delete()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::Edit()
{
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::MoveFirst()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::MoveLast(const VARIANT& Options)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Options);
}

void C_rdoResultset::MoveNext()
{
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::MovePrevious()
{
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::Update()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::Requery(const VARIANT& Options)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Options);
}

void C_rdoResultset::Move(long Rows, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Rows, &Start);
}

BOOL C_rdoResultset::MoreResults()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::Cancel()
{
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void C_rdoResultset::CancelUpdate()
{
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT C_rdoResultset::GetRows(const VARIANT& NumRows)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&NumRows);
	return result;
}

void C_rdoResultset::BatchUpdate(const VARIANT& SingleRow, const VARIANT& Force)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SingleRow, &Force);
}

void C_rdoResultset::CancelBatch(const VARIANT& SingleRow)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SingleRow);
}

C_rdoConnection C_rdoResultset::GetActiveConnection()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return C_rdoConnection(pDispatch);
}

void C_rdoResultset::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x24, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long C_rdoResultset::GetBatchCollisionCount()
{
	long result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT C_rdoResultset::GetBatchCollisionRows()
{
	VARIANT result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long C_rdoResultset::GetLockType()
{
	long result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long C_rdoResultset::GetStatus()
{
	long result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void C_rdoResultset::SetStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString C_rdoResultset::GetClipString(long NumRows, const VARIANT& ColumnDelimiter, const VARIANT& RowDelimiter, const VARIANT& NullExpr)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		NumRows, &ColumnDelimiter, &RowDelimiter, &NullExpr);
	return result;
}

void C_rdoResultset::Resync()
{
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
