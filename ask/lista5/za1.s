.global adduSkok
.global adduBezSkok


# x %rdi
# y %rsi
# wynik w %rax
adduSkok:
  addq  %rdi, %rsi
  jo dajMax # jeśli dostaniemy OF to zwaracamy INTmax

  # nie dostaliśmy OF można zwrócić x + y w rax
  movq %rsi, %rax
  return

dajMax:
  movq $0xffffffffffffffff, %rax
  ret

adduBezSkok:
  addq %rsi, %rdi # dodaje rsi do rdi
  sbb  %rax, %rax # jeśli OF to -1, jeślie nie OF to 0
  orq  %rdi, %rax 
  ret
  
