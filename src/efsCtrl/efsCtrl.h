#ifndef _EFS_CTRL_H_
#define _EFS_CTRL_H_

#define EFSCTRL_SUCCESS            0 
#define EFSCTRL_UNSUCCESSFUL       1
#define EFSCTRL_ALREADY_STARTED    2
#define EFSCTRL_NO_MEMORY          3
#define EFSCTRL_IO_ERROR           4
#define EFSCTRL_ERROR_ON_HOOK      5

DWORD efsCtrl_Start(  );

BOOL  SetEventReportValue(BOOL  bValue);
BOOL  GetEventReportValue(BOOL* bValue);

BOOL  SetPrivilegeControlValue(BOOL  bValue);
BOOL  GetPrivilegeControlValue(BOOL* bValue);

BOOL  SetFakedExeCheckValue(BOOL  bValue);
BOOL  GetFakedExeCheckValue(BOOL* bValue);

DWORD efsCtrl_Stop( );

#endif

