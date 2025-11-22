.data 
array word 10,60,20,33,72,89,45,65,72,18
sample word 50
arraySize word LENGTHOF array
index word 0
sum word 0

.code
main PROC

While:
    mov ax , index
    cmp ax,arraySize
    jz endWhile
    jnc endWhile

    mov ax , [array + index*2]
    cmp ax,sample
    jnc else_case
    mov ax ,sum
    add ax , [array + index*2]
    mov sum , ax
    else_case:
    add index,1
    jmp While

endWhile:

exit
main ENDP
END main