bits 32

global _permutari
extern _printf

segment data use32 public data
    format db "%s",13,10,0

; our code starts here
segment code use32 public code
    _permutari:
        ;permutari(buffer,length);
        push ebp
        mov ebp,esp
        
        push dword [ebp+8]
        push format
        call _printf
        add esp,8
        mov ecx,[ebp+12]
        dec ecx
        jz .final
        .repeta:
        push ecx
        mov esi,[ebp+8];buffer[0]
        mov al,[esi]
        mov edi,[ebp+8]
        inc edi ;buffer[1]
        mov ebx,[ebp+12]
        dec ebx
        .permutare:
            mov dl,[edi]
            mov [esi],dl
            inc esi
            inc edi
            dec ebx
            jnz .permutare
        
        mov [esi],al
        push dword[ebp+8]
        push format
        call _printf
        add esp,8
        pop ecx
        loop .repeta
        
        
     .final:   
        mov esp,ebp
        pop ebp
        ret
        
