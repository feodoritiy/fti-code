README_BASE = """## Программирование

Автор: Никонов Фёдор

Группа: ПИ-б-о-201(2)

### Первый семестр

| Практические | Лабораторные |
|--------------|--------------|
"""

import os
table = []

projects = list(filter(lambda el: el.is_dir(), os.scandir('Practice')))
labs = list(filter(lambda el: el.is_dir(), os.scandir('Labs')))
for folder in projects:
   if not folder.is_dir(): continue
   folder = folder.name
   table += [f'| Практическая {folder} - [[С++]](./Practice/{folder}/C++/{folder}.cpp) [[Python]](./Practice/{folder}/Python/{folder}.py) | ']
   
for i in range(len(projects)):
   if (i < len(labs)):
      folder = labs[i].name
      table[i] += f' [Лабораторная {folder}](./Labs/{folder}/README.md) |\n'
   else:
      table[i] += '|\n'

readme = open('README.md', 'w')
readme.write(README_BASE + ''.join(table))
readme.close()
