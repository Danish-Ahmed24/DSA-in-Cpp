TITLE Fibonacci Series (Recursive)

INCLUDE Irvine32.inc

; --- Constants ---
MAX_TERMS = 20

.data
    
.code
; -----------------------------------------------------------------
; Main procedure: Drives the series generation
; -----------------------------------------------------------------
main PROC
    
    mov ecx, 1          ; Loop counter 'Index', starting at F(1)
    mov ebx, MAX_TERMS  ; Loop limit (20)

MainLoop:
    ; 1. Call Fibonacci(Index)
    push ecx            ; Push 'Index' (N) as the parameter
    call Fibonacci      
    
    ; 2. Display the result (EAX)
    call WriteDec       ; Display EAX (F(N))
    call WriteString    ; Display a space for separation
    
    ; 3. Increment Index and loop
    inc ecx             ; Index = Index + 1
    cmp ecx, ebx        ; Check if Index > MAX_TERMS
    jle MainLoop        ; Loop while Index <= MAX_TERMS

    call Crlf           ; Newline at the end
    exit
main ENDP

; -----------------------------------------------------------------
; Fibonacci PROC: Calculates the N-th Fibonacci number recursively.
; Receives: [ebp+8] = N
; Returns: EAX = F(N)
; -----------------------------------------------------------------
Fibonacci PROC
    push ebp            ; Start Prologue
    mov ebp, esp        ; Establish frame pointer
    
    mov eax, [ebp+8]    ; Get N into EAX

    ; --- Base Case 1 & 2: If N <= 2, return 1 ---
    cmp eax, 2          
    jle BaseCase        ; If N is 1 or 2, jump to base case
    
    ; --- Recursive Step: F(N) = F(N-1) + F(N-2) ---
    
    ; 1. Calculate F(N-1):
    dec eax             ; EAX = N - 1
    push eax            ; Push N-1 as parameter
    call Fibonacci      ; Recurse
    mov ebx, eax        ; Save F(N-1) result (EAX) in EBX
    
    ; 2. Calculate F(N-2):
    mov eax, [ebp+8]    ; Get original N back into EAX
    sub eax, 2          ; EAX = N - 2
    push eax            ; Push N-2 as parameter
    call Fibonacci      ; Recurse. F(N-2) is now in EAX
    
    ; 3. Sum the results:
    add eax, ebx        ; EAX = F(N-2) + F(N-1) (Final result F(N))
    jmp Finish          ; Skip base case return
    
BaseCase:
    mov eax, 1          ; Set EAX = 1 (F(1) = 1, F(2) = 1)

Finish:
    pop ebp             ; End Epilogue (Restores caller's EBP)
    ret 4               ; Return and clean up the 4-byte parameter (N)
Fibonacci ENDP
END main