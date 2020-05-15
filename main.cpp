#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
LPSTR cmdline;

void GainAdminPrivileges(UINT idd, BOOL bWait){

    //strCmd.Format (_T("/adminoption %d"), idd);
    char strCmd[MAX_PATH];
    char strApp[MAX_PATH*10];
    sprintf(strCmd, "/adminoption %d", idd);
    sprintf(strApp, cmdline, idd);

    SHELLEXECUTEINFO execinfo;
    memset(&execinfo, 0, sizeof(execinfo));
    execinfo.lpFile			= strApp;
    execinfo.cbSize			= sizeof(execinfo);
    execinfo.lpVerb			= TEXT("runas");
    execinfo.fMask			= SEE_MASK_NOCLOSEPROCESS;
    execinfo.nShow			= SW_SHOWDEFAULT;
    execinfo.lpParameters	= strCmd;

    ShellExecuteEx(&execinfo);

    if(bWait)
        WaitForSingleObject(execinfo.hProcess, INFINITE);
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    cmdline = lpCmdLine;
    LPSTR tmpstr;
    LPSTR currentpath;
    GetModuleFileName(NULL, currentpath, MAX_PATH*10);//GetCurrentDirectory(MAX_PATH*10, currentpath);
    LPSTR tmppath;
    sprintf(tmppath, "%s\\..\\settings.ini", currentpath);
    if (strcmp(lpCmdLine, "-i") == 0 || strcmp(lpCmdLine, "su") == 0) {
        strcpy(cmdline, (char*)"cmd.exe");
    }
    if (strcmp(lpCmdLine, "") == 0) {
        printf("usage: sudo -i | su | --help | --version\nusage: sudo [filename]\n");
        return 0;
    }
    if (strcmp(lpCmdLine, "--version") == 0) {
        GetPrivateProfileString(TEXT("VERSIONINFO"), TEXT("SUDOVER"), TEXT("Unknown"), tmpstr, 100, TEXT(tmppath));
        printf("WinSudo by EricNTH.\nView this project on Github: https://github.com/EricNTH080103/WinSudo/\nSudoVersion: %s.\n",tmpstr);
        return 0;
    }
    if (strcmp(lpCmdLine, "--wait false") == 0 || strcmp(lpCmdLine, "-w false") == 0) {
        WritePrivateProfileString("BASIC", "WAIT", "0", tmppath);
        return 0;
    }
    if (strcmp(lpCmdLine, "--wait true") == 0 || strcmp(lpCmdLine, "-w true") == 0) {
        WritePrivateProfileString("BASIC", "WAIT", "1", tmppath);
        return 0;
    }
    if (strcmp(lpCmdLine, "--wait") == 0 || strcmp(lpCmdLine, "-w") == 0) {
        WritePrivateProfileString("BASIC", "WAIT", "1", tmppath);
        return 0;
    }
    if (strcmp(lpCmdLine, "--help") == 0) {
        printf("usage: sudo -i | su: Execute command shell in administrator mode.\n\
sudo [filename]: Execute that file in administrator mode.\n\
sudo --version: Show version information.\n\
sudo -w | --wait [true | false]: Set wait. Default: true (If true/false not given). Last as long as you don't change this value.\n\
sudo --help: Show this help.\n");
        return 0;
    }
    GainAdminPrivileges(GetPrivateProfileInt(TEXT("BASIC"), TEXT("IDD"), 3, TEXT(tmppath)), GetPrivateProfileInt(TEXT("BASIC"), TEXT("WAIT"), 2, TEXT(tmppath)));
    return 0;
}