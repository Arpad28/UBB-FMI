bits 32

global _proceseaza
extern _compara

segment data use32 public data
    vocale  db "aeiouAEIOU",0
    current times 256 db 0 
    best    times 256 db 0    

segment code use32 public code
_proceseaza:
    push ebp
    mov ebp, esp

    mov esi, [ebp+8]    
    mov edi, current 
    xor ecx, ecx
    xor eax, eax;nr cur voc
    xor ebx, ebx ;nr max voc
    mov byte [best], 0
next_char:
    mov dl, [esi]     
    cmp dl, 0          
    je end_line
    cmp dl, ' '       
    je separator
    mov [edi+ecx], dl
    inc ecx
    push eax;pentru a verifica vocala
    mov eax, 0        
    push esi   
    mov esi, vocale
    
check_v_loop:
    mov dh, [esi]     
    cmp dh, 0
    je not_v_found
    cmp dh, dl   
    je is_v_found
    inc esi
    jmp check_v_loop

is_v_found:
    pop esi    
    pop eax  
    inc eax      
    jmp char_processed

not_v_found:
    pop esi        
    pop eax         

char_processed:
    inc esi          
    jmp next_char
separator:
    cmp ecx, 0
    je skip_space
    mov byte [edi+ecx], 0 
    push ebx              ; [ebp+20] best_voc
    push best             ; [ebp+16] best
    push eax              ; [ebp+12] cur_voc
    push current          ; [ebp+8]  current
    call _compara
    mov edx, [esp+4];return de pe stiva
    add esp, 16    
    cmp eax, current     
    jne reset_current
    mov ebx, edx     
    push esi        
    push edi
    mov esi, current
    mov edi, best
copy_best_loop:
    mov dl, [esi]
    mov [edi], dl
    inc esi
    inc edi
    cmp dl, 0
    jne copy_best_loop
    pop edi
    pop esi
reset_current:
    xor ecx, ecx     
    xor eax, eax    
    mov edi, current   
skip_space:
    inc esi
    jmp next_char
end_line:
    cmp ecx, 0
    je prepare_output
    mov byte [edi+ecx], 0 ;caz de e vocala
    push ebx
    push best
    push eax
    push current
    call _compara
    mov edx, [esp+4]     
    add esp, 16
    cmp eax, current
    jne prepare_output
    push esi
    push edi
    mov esi, current
    mov edi, best
copy_last_loop:
    mov dl, [esi]
    mov [edi], dl
    inc esi
    inc edi
    cmp dl, 0
    jne copy_last_loop
    pop edi
    pop esi
prepare_output:
    mov esi, best
    mov edi, [ebp+12]   
copy_out_loop:
    mov dl, [esi]
    mov [edi], dl
    inc esi
    inc edi            
    cmp dl, 0
    jne copy_out_loop
    mov esp, ebp
    pop ebp
    ret