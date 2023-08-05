//#pragma once
//
//#include <Windows.h>
//#include <string>
//#include <array>
//#include <cstdarg>
//#include "xorstr.h"
//
//
//
//void* m_Ntdll = GetProcAddress(GetModuleHandleA(xorstr("ntdll.dll")), xorstr("RtlInterlockedCompareExchange64"));
//void* m_CreateRemoteThreadEx = GetProcAddress(GetModuleHandleA(xorstr("KERNELBASE.dll")), xorstr("CreateRemoteThreadEx"));
//
//const uint64_t ntdll170 = (uint64_t)m_Ntdll + 0x170;
//const uint64_t CreateRemoteThreadKernel = (uint64_t)m_CreateRemoteThreadEx;
//
//void __declspec(naked) CopyZwCreateThread()
//{
//    __asm
//    {
//        mov rax, 0x4E
//        mov rdx, ntdll170
//        call rdx
//        ret 0x20
//    }
//}
//
//HANDLE __declspec(naked) __stdcall CopyCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
//    SIZE_T dwStackSize,
//    LPTHREAD_START_ROUTINE lpStartAddress,
//    LPVOID lpParameter,
//    uint64_t dwCreationFlags,
//    LPuint64_t lpThreadId)
//{
//    __asm
//    {
//        mov rdi, rdi
//        push rbp
//        mov rbp, rsp
//        push[ebp + 0x1C]
//        mov rax, [rbp + 0x18]
//        push 0
//        and rax, 0x10004
//        push rax
//        push[rbp + 0x14]
//        push[rbp + 0x10]
//        push[rbp + 0xC]
//        push[rbp + 8]
//        push - 1
//        call CreateRemoteThreadKernel
//        pop rbp
//        ret 0x18
//    }
//}