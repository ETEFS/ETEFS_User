#ifndef _EFS_KERNEL_H_
#define _EFS_KERNEL_H_


#define EFSKRNL_SUCCESS            0 
#define EFSKRNL_UNSUCCESSFUL       1
#define EFSKRNL_ALREADY_STARTED    2
#define EFSKRNL_NO_MEMORY          3
#define EFSKRNL_IO_ERROR           4
#define EFSKRNL_ERROR_ON_HOOK      5


DWORD AddExtName(WCHAR*  pwszExt);
DWORD AddFile2Mfl(WCHAR*  wszFileName);
DWORD CheckMfl(WCHAR*  wszFileName);
VOID  SetWhiteState( BOOL  b);

#endif

