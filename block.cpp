#include <stdio.h>
#include <Windows.h>

int countPrimes(int n)
{
    __asm
    {
        push 10001
        call DWORD PTR malloc
        //save nprime
        mov esi, eax

        push 40004
        call DWORD PTR malloc
        //save primes
        mov ebx, eax

        push 10000//S
        call DWORD PTR malloc
        //save bl
        mov edi, eax
        add esp, 12

//Memset nprime
        mov ecx, 10000
L1:
        mov [esi + ecx], 0
        loop L1
//Prepr
        mov edx, 2//i
        push 0//result
        push 0//cnt
LOOP1:
        mov eax, edx
        mov ecx, edx
        mul edx
        mov edx, ecx
        cmp eax, n
        jg LOOPEND
        mov ecx, eax//i*i
        cmp [esi + edx], 0
        jne CNTN
        pop eax
        mov [ebx + eax * 4], edx
        inc eax
        push eax
LOOP2:
        cmp ecx, 10000//maxsqrt
        jg CNTN
        push edx
        mov eax, ecx
        mov edx, ecx
        mul edx
        cmp eax, n
        pop edx
        jg CNTN
        mov [esi + ecx], 1
        add ecx, edx
        jmp LOOP2
CNTN:
        inc edx
        jmp LOOP1
LOOPEND:
//Free nprime
        push esi
        call DWORD PTR free
        add esp, 4
//Main part
        mov eax, n
        mov esi, 10000//S
        mov edx, 0
        div esi
        push eax//maxk
        mov esi, eax//maxk
        mov edx, 0//k
BLOOP1:
        cmp edx, esi
        jg BLOOPEND
//Memset bl
        mov ecx, 9999
L2:
        mov [edi + ecx], 0
        loop L2

        mov ecx, edx//save edx
        mov eax, edx//k
        mov edx, 10000//S
        mul edx//eax = start
        mov edx, ecx//edx = k
        mov esi, 0//i
        push edx//k
        push eax//start
BLOOP2:
        cmp esi, [esp + 12]//<cnt
        jge L3
        mov ecx, [esp]//start
        mov eax, [ebx + esi * 4]//primes[i]
        mov edx, eax//primes[i]
        add eax, ecx
        dec eax
        mov ecx, edx//primes[i]
        mov edx, 0
        div ecx//start_idx
        cmp eax, 2
        jge NMAX
        mov eax, 2
NMAX:
        mov ecx, [ebx + esi * 4]//primes[i]
        mul ecx
        sub eax, [esp]//eax = j
BLOOP3:
        cmp eax, 10000//S
        jge BCNTN2
        mov [edi + eax], 1
        add eax, ecx
        jmp BLOOP3
L3:
        mov esi, 0//i
        mov ecx, [esp + 16]//result
CLOOP2:
        cmp esi, 10000//S
        jge BCNTN
        mov eax, [esp]//start
        add eax, esi//start + i
        cmp eax, n
        jg BCNTN
        cmp [edi + esi], 0
        jne CCNTN2
        inc ecx
CCNTN2:
        inc esi
        jmp CLOOP2
BCNTN2:
        inc esi
        jmp BLOOP2
BCNTN:
        pop edx
        pop edx
        mov esi, [esp]
        inc edx
        mov [esp + 8], ecx
        jmp BLOOP1
BLOOPEND:
//Free all
        push ebx
        call DWORD PTR free
        push edi
        call DWORD PTR free
        add esp, 16
        pop eax
        dec eax
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int t = GetTickCount();
    printf("%d\n", countPrimes(n));
    printf("%d ms\n", GetTickCount() - t);
    return 0;
}
