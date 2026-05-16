bits 32 

global _concatenare

segment data use32 public data
    ; ...

; our code starts here
segment code use32 public code
       ;concatenare(a,b,sir1,sir2);
    _concatenare:
        push ebp
        mov ebp,esp
        
        cld
        mov esi,[ebp+8]
        mov edi,[ebp+16]
        .copy:
            lodsb
            cmp al,0
            je .cifre1
            stosb
        jmp .copy
        .cifre1:
        mov esi,[ebp+12]
        .cifre:
            lodsb
            cmp al,0
            je .gata1
            cmp al,'0'
            jl .cifre
            cmp al,'9'
            jg .cifre
            stosb
        jmp .cifre
        .gata1:
            mov al,0
            stosb
         
        mov esi,[ebp+8]
        mov edi,[ebp+20]
         .copy1:
            lodsb
            cmp al,0
            je .copy2.1
            stosb
        jmp .copy1
        .copy2.1:
        mov esi,[ebp+12]
         .copy2:
            lodsb
            cmp al,0
            je .final
            stosb
        jmp .copy2
        .final:
        mov al,0
        stosb
        mov esp,ebp
        pop ebp
        ret
