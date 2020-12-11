def pushSort(arr, element):
	arr.append(element)
	# insertion sort part
	j = len(arr) - 2
	while j >= 0 and arr[j] < element:
		arr[j + 1] = arr[j]
		j -= 1
	arr[j + 1] = element


N = input("Введите число сигналов: ")
signal = None
signals = list(map(int, input('Массив сигналов: ').split(' ')))
visible = []

for signal in signals:
   pushSort(visible, signal)
   visibleLen = len(visible)
   print(*visible[-5:])