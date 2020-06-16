#ifndef _EFS_API_H_
#define _EFS_API_H_

#define  EFSAPI_SUCCESS                0
#define  EFSAPI_OPEN_SRC_FILE          1
#define  EFSAPI_OPEN_DEST_FILE         2
#define  EFSAPI_NO_MEMORY              3
#define  EFSAPI_NOT_IMPLEMENTED        4
#define  EFSAPI_NOT_ENCRYPTED          5
#define  EFSAPI_KEY_MISMATCH           6
#define  EFSAPI_INVALID_PARAMETER      7
#define  EFSAPI_CONNECT_PORT_FAILED    8
#define  EFSAPI_UNSUCCESSFUL           9
#define  EFSAPI_NO_SUCH_ITEM          10
#define  EFSAPI_ITEM_EXITS            11
#define  EFSAPI_NOT_START_FILTER      12
#define  EFSAPI_CIPHER_MISMATCH       13
#define  EFSAPI_OKPF_MISMATCH         14
#define  EFSAPI_MOD_CTRL_MISS         15
#define  EFSAPI_MOD_KRNL_MISS         16

#define  HEADER_BUFFER_SIZE   2048
#define  CUSTOM_DATA_SIZE     1024

DWORD    efsApi_SetStartFiltering(BOOL  bStart);
DWORD    efsApi_GetStartFiltering(BOOL*  bStart);

#define  CIPHER_ID_XTEA    0
#define  CIPHER_ID_AES     1

DWORD    efsApi_SetCryptConfig(DWORD   CihperID,int bUseRandomKey, char* szKeyBuffer, int nKeyLength);
DWORD    efsApi_GetCryptConfig(DWORD*  CihperID,int* bUseRandomKey);

#define  PROC_FLAG_ENCRYPT_ON_OPEN  0x00000002

DWORD    efsApi_AddPolicy(WCHAR* wszExeName, WCHAR* wszExtNameList, ULONG nFlags );
DWORD    efsApi_DeletePolicy(WCHAR* wszExeName);
DWORD    efsApi_DeleteAllPolicy( );

typedef struct _FILE_CRYPT_CONFIG
{
	ULONG   dwCipherID;
	ULONG   nUseRandomKey;
	CHAR    szFileKey[128];
}FILE_CRYPT_CONFIG,*PFILE_CRYPT_CONFIG;

DWORD    efsApi_GetFileCryptConfig(WCHAR* wszFileName, PFILE_CRYPT_CONFIG cryptConfig);
DWORD    efsApi_IsEncryptedFile(WCHAR* wszFileName);

DWORD    efsApi_EncryptFile(WCHAR* wszFileName);
DWORD    efsApi_EncryptFileAlone( WCHAR* wszFileName, int CipherID, int bUseRandomKey, char* FileKey);

DWORD    efsApi_DecryptFile(WCHAR* wszFileName);
DWORD    efsApi_DecryptFileAlone( WCHAR* wszFileName, int CipherID, char* FileKey);


DWORD    efsApi_SetCustomData(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize );
DWORD    efsApi_SetCustomDataAlone(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize, 
								int CipherID,  char* FileKey, int KeyLength
								);

DWORD    efsApi_GetCustomData(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize );
DWORD    efsApi_GetCustomDataAlone(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize, 
						   int CipherID,  char* FileKey, int KeyLength
						   );

DWORD    efsApi_SetCustomDataResident(DWORD dwValue );
DWORD    efsApi_GetCustomDataResident(DWORD* dwValue );
DWORD    efsApi_SetManualEncryptFile(DWORD dwValue );
DWORD    efsApi_GetManualEncryptFile( DWORD* dwValue );

DWORD    efsApi_AddWhiteDir(WCHAR*  wszDir);
DWORD    efsApi_RemoveWhiteDir(WCHAR* wszDir);

DWORD  LoadNotepadPolicy( );
DWORD  UnloadNotepadPolicy( );

DWORD  LoadWordpadPolicy( );
DWORD  UnloadWordpadPolicy( );

DWORD  LoadWordPolicy( );
DWORD  UnloadWordPolicy( );

DWORD  LoadExcelPolicy( );
DWORD  UnloadExcelPolicy( );

DWORD  LoadPPTPolicy( );
DWORD  UnloadPPTPolicy( );

DWORD  LoadWPSWordPolicy( );
DWORD  UnloadWPSWordPolicy( );

DWORD  LoadWPSExcelPolicy( );
DWORD  UnloadWPSExcelPolicy( );

DWORD  LoadWPSPPTPolicy( );
DWORD  UnloadWPSPPTPolicy( );

DWORD  LoadAutoCADPolicy( );
DWORD  UnloadAutoCADPolicy( );

DWORD  LoadFoxitPDFPolicy( );
DWORD  UnloadFoxitPDFPolicy( );

DWORD  LoadAdobePDFPolicy( );
DWORD  UnloadAdobePDFPolicy( );

DWORD  LoadMspaintPolicy( );
DWORD  UnloadMspaintPolicy( );

DWORD  LoadImgViewerPolicy( );
DWORD  UnloadImgViewerPolicy( );


#endif

