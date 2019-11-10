import sys

class BFInterpreter:
  def run(self, s, inp=None):
    l = len(s)
    if inp:
      inp = [*map(ord, inp)]
    stack = []
    brackets = {}
    for i, c in enumerate(s):
      if c == '[':
        stack.append(i)
      elif c == ']':
        if not stack:
          raise ValueError("Bracket mismatch")
        opening = stack.pop()
        brackets[opening] = i
        brackets[i] = opening
    if stack:
      raise ValueError("Bracket mismatch")

    m = [0]*1000
    p = 0
    pc = 0
    while True:
      c = s[pc]
      if c == '>':
        p += 1
      elif c == '<':
        p -= 1
      elif c == '+':
        m[p] += 1
      elif c == '-':
        m[p] -= 1
      elif c == '.':
        print(chr(m[p]),end='')
      elif c == ',':
        if inp == None:
          m[p] = ord(input()[0])
        else:
          if not inp:
            break
          m[p] = inp.pop(0)
      elif c == '[' and m[p] == 0:
        pc = brackets[pc] + 1
        continue
      elif c == ']' and m[p] != 0:
        pc = brackets[pc] + 1
        continue
      pc += 1
      if pc >= l:
        break
  
if __name__ == "__main__":
  bfi = BFInterpreter()
  with open(sys.argv[1], "r") as f:
    bfi.run(f.read())