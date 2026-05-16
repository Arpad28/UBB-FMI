bits 32

global _compara

segment code use32 public code

_lungime:
    push esi
    xor eax, eax
scan_len:
    cmp byte [esi], 0
    je done_len
    inc eax
    inc esi
    jmp scan_len
done_len:
    pop esi
    ret

_compara:
    push ebp
    mov ebp, esp
    ; [ebp+8]  = adresa current
    ; [ebp+12] = valoare cur_voc
    ; [ebp+16] = adresa best
    ; [ebp+20] = valoare best_voc

    mov eax, [ebp+12]  
    cmp eax, [ebp+20] 
    ja ret_cur      
    jb ret_best  
    
    mov esi, [ebp+8]  
    call _lungime
    mov ecx, eax 

    mov esi, [ebp+16]
    call _lungime
    
    cmp ecx, eax
    ja ret_cur  
    jb ret_best
  
    mov esi, [ebp+8]   
    mov edi, [ebp+16]

lex_loop:;bana<cana
    mov al, [esi]  
    mov bl, [edi]  
    cmp al, bl
    jb ret_cur
    ja ret_best
    cmp al, 0    
    je ret_best   
    inc esi
    inc edi
    jmp lex_loop

ret_cur:
    mov eax, [ebp+8]
    jmp done

ret_best:
    mov eax, [ebp+16]

done:
    mov esp, ebp
    pop ebp
    ret