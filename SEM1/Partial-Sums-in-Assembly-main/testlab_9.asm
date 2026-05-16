bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fscanf, fclose, fprintf,scanf
import scanf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    input db "input.txt",0
    format_w db "w",0
    format_r db "r",0
    desc_in dd 0
    output times 105 db 0
    format_output db "%s",0
    desc_ou dd 0
    a dd 0
    b dd 0
    numere times 105 dd 0
    format db "%d",0
    format_afis db "%d",13,10,0
    suma times 105 dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword format_r
        push dword input
        call [fopen]
        add esp,4*2
        mov [desc_in],eax
        cmp eax,0
        je end_cod
        ; exit(0)
        
        mov esi,numere
        citeste:
          push esi
          push dword format
          push dword [desc_in]
          call [fscanf]
          add esp,4*3
          cmp eax,1
          jne end_citeste
          mov eax,[esi]
          cmp eax,0
          je end_citeste
          add esi,4
          jmp citeste
      
        end_citeste:
            
            mov esi,numere
            mov edi,suma
            
            mov eax,[esi]
            mov [edi],eax
            cmp eax,0
            je pass_calc
            add esi,4
            add edi,4
        
        calc_suma:
            mov ebx,[esi]
            cmp ebx,0
            je pass_calc
            mov eax,[edi-4]
            add eax,ebx
            mov [edi],eax
            add esi,4
            add edi,4
            jmp calc_suma
        
        pass_calc:
            
             push dword output
             push dword format_output
             call [scanf]
             add esp,4*2
             
             push dword format_w
             push dword output
             call [fopen]
             add esp,4*2
             mov [desc_ou],eax
             cmp eax,0
             je end_cod
         
        calc_perechi:
               push dword a
               push dword format
               call [scanf]
               add esp,4*2
               
               push dword b
               push dword format
               call [scanf]
               add esp,4*2
               
        mov eax,dword[a]
        mov ebx,dword[b]
        cmp eax,-1
        jnle validare
        cmp ebx,-1
        je finish
        
        validare:
            mov ecx,0
            mov edi,numere
        contor_lung:
            mov edx,[edi]
            cmp edx,0
            je gata_contor
            add edi,4
            inc ecx
            jmp contor_lung
        
        gata_contor:
            cmp ebx,eax
            jl calc_perechi
            cmp ebx,ecx
            jge calc_perechi
            mov edx,suma
            cmp eax,0
            jne nu_prim
            mov eax,[edx+ebx*4]
            jmp afis
        
        nu_prim:
            mov esi,[edx+ebx*4]
            mov edi,[edx+(eax-1)*4]
            sub esi,edi
            mov eax,esi
        
        afis:
            push dword eax
            push dword format_afis
            push dword [desc_ou]
            call [fprintf]
            add esp,4*3
            jmp calc_perechi
        finish:
            push dword [desc_in]
            call [fclose]
            add esp,4
            
            push dword [desc_ou]
            call [fclose]
            add esp,4
        end_cod:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
