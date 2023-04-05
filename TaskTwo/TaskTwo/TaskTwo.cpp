// TaskTwo.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct point {
    double x;
    double y;
    double z;
};

double getLength(const point* p1, const point* p2) {
    __asm {
        finit
        mov ecx, p1
        mov ebx, p2
        fld qword ptr[ecx]
        fld qword ptr[ebx]
        fsubp st(1), st(0)
        fmul st(0), st(0)
        fld qword ptr[ecx][8]
        fld qword ptr[ebx][8]
        fsubp st(1), st(0)
        fmul st(0), st(0)
        faddp st(1), st(0)
        fld qword ptr[ecx][16]
        fld qword ptr[ebx][16]
        fsubp st(1), st(0)
        fmul st(0), st(0)
        faddp st(1), st(0)
        fsqrt
    }
}

double maxLength(point points[], int size_) {
    __asm {
        finit
        fldz
        xor esi, esi
        xor edi, edi
        add edi, 24
        mov edx, points
        FORI :
        sub esp, 8
            fst qword ptr[esp]
            push esi
            push edi
            push edx
            lea ecx, [edx][edi]
            push ecx
            lea ecx, [edx][esi]
            push ecx
            call getLength
            add esp, 8
            pop edx
            pop edi
            pop esi
            fld qword ptr[esp]
            add esp, 8
            fxch st(1)
            fcom st(1)
            fstsw ax
            sahf
            jbe OLDMAX
            fxch st(1)
            OLDMAX:
        fstp st(0)
            mov ecx, size_
            mov eax, 24
            mul ecx
            mov ecx, eax
            mov edx, points
            add edi, 24
            cmp edi, ecx
            jb FORI

            add esi, 24
            mov edi, esi
            add edi, 24
            cmp edi, ecx
            jb FORI
            END :
    }
}

int main()
{
    point p1;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    point p2;
    p2.x = 3;
    p2.y = 4;
    p2.z = 8;
    point p3;
    p3.x = 2;
    p3.y = 7;
    p3.z = 0;
    point ps[3];
    ps[0] = p2;
    ps[1] = p1;
    ps[2] = p3;
    std::cout << maxLength(ps, 3);
}