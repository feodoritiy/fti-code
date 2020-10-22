README_BASE = """## Программирование

Автор: Никонов Фёдор

Группа: ПИ-б-о-201(2)

### Первый семестр

| Практические | Лабораторные |
|--------------|--------------|"""

import os
table = ''

projects = os.scandir('Practice')
for folder in projects:
   if not folder.is_dir(): continue
   folder = folder.name
   table += f'| Практическая {folder} - [[С++]](./Practice/{folder}/C++/) [[Python]](./Practice/{folder}/Python) |  |\n'

readme = open('README.md', 'w')
readme.write(README_BASE + table)
