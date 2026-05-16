bits 32

global _verifica
global _neg,_poz,_n_neg,_n_poz

segment data use32 public data
    _neg times 100 dd 0
    _poz times 100 dd 0
    _n_neg dd 0
    _n_poz dd 0

segment code use32 public code
_verifica:
    push ebp
    mov ebp,esp
    
    mov eax,[ebp+8]
    cmp eax,0
    jl .negativ
    
    mov ecx,[_n_poz]
    mov [_poz+ecx*4],eax
    inc dword [_n_poz]
    jmp .final
 
.negativ:
    mov ecx,[_n_neg]
    mov [_neg+ecx*4],eax
    inc dword [_n_neg]
   
.final:
    mov esp,ebp
    pop ebp
    ret

