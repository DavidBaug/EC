.section .data
lista:    .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
          .int 0xF0000000,0xE0000000,0xE0000000,0xD0000000
longlista:  .int (.-lista)/4
resultado:  .quad -1

.section .text
_start: .global _start

  mov    $lista, %ebx
  mov longlista, %ecx
  call suma
  mov %eax, resultado
  mov %edx, resultado+4

  mov $1, %eax
  mov $0, %ebx
  int $0x80

suma:
  # Guardamos el registro del procesador
  push %esi

  # Declaramos y ponemos el índice del for a cero
  mov $0, %esi

  # Limpiamos el acumulador
  mov $0, %eax
  mov $0, %edx
  mov $0, %ebp
  mov $0, %edi
bucle:
  mov (%ebx,%esi,4), %eax

  # Extendemos (EDX:EAX)
  cdq

  # Sumar el elemento y su posible acarreo
  add %eax, %edi
  adc %edx, %ebp

  # Incrementamos el contador
  inc       %esi

  # Comparación del bucle
  cmp  %esi,%ecx
  jne bucle

  # Movemos el resultado a EDX:EAX
  mov %edi, %eax
  mov %ebp, %edx

  # Sacamos el registro guardados
  pop %esi

  # Retornamos
  ret
