.section .data
lista:    .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
          .int 0x00000001, 0x00000001, 0x00000001, 0x00000001
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
bucle:
  # Sumar el elemento y su posible acarreo (más cero).
  add (%ebx,%esi,4), %eax
  adc $0,%edx

  # Incrementamos el contador
  inc       %esi

  # Comparación del bucle
  cmp  %esi,%ecx
  jne bucle

  # Sacamos el registro guardados
  pop %esi

  # Retornamos
  ret
