bits 32

global _modul
extern _permutari

segment data use32 public data
    format db "%s", 10, 0  
    hex db "0123456789ABCDEF"
    buffer resb 9       
    length resb 1        


segment code use32 public code
_modul:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    mov ecx, 0
    
    mov edi, buffer
    add edi, 8
    mov byte [edi], 0       
    dec edi

    cmp eax, 0
    jne .convert
    
    mov byte [edi],'0'
    mov byte [length], 1
    dec edi             
                            
    jmp .setup_copy

.convert:
    mov edx, eax
    and edx, 0Fh          
    mov dl, [hex + edx]    
    mov [edi], dl          
    shr eax, 4             
    dec edi                
    inc ecx                 
    cmp eax, 0
    jne .convert

    mov [length], cl

.setup_copy:
    inc edi             
    mov esi, buffer        
    
    cmp edi, esi
    je .pass
    
    movzx edx, byte [length]

.copy:
    mov al, [edi]         
    mov [esi], al          
    inc edi
    inc esi
    dec edx
    jnz .copy
    mov byte [esi], 0      

    ;permutari(buffer,length);
    .pass:
    movzx eax,byte [length]
    push eax
    push buffer
    call _permutari
    add esp,8
    
.final:

    mov esp, ebp
    pop ebp
    ret