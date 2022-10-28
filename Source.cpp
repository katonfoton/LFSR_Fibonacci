#include <iostream>
#include <string>
using namespace std;

int LFSR_Fibonacci_cipher(int binary [], int a) {
	register int size = a;
	register int seed = 0b1000110101101000;
	//x^16 + x^15 + x^13 + x^4
	register int key_size = size / 16;
	register int dop_key_size = size % 16;
	if (dop_key_size != 0)
		key_size++;
	register int* key = new int[size];
	for (int i = 0; i < key_size; i++) {
		register int newBit = ((seed >> 15) & 1) ^ ((seed >> 14) & 1) ^ ((seed >> 12) & 1) ^ ((seed >> 3) & 1);
		seed = (seed >> 1) | (newBit << 15);
		if (dop_key_size == 0) {
			for (int k = i * 16, j = 15; (k <= i * 16 + 15) && (j >= 0); k++, j--)
				key[k] = (seed >> j) & 1;
		}
		else {
			if (i != key_size - 1) {
				for (int k = i * 16, j = 15; (k <= i * 16 + 15) && (j >= 0); k++, j--)
					key[k] = (seed >> j) & 1;
			}
			else {
				for (int k = i * 16, j = 15; (k <= i * 16 + dop_key_size - 1) && (j >= 0); k++, j--)
					key[k] = (seed >> j) & 1;
			}

		}
	}
	for (int i = 0; i < size; i++) 
		binary[i] ^= key[i];
	delete[] key;
	return *binary;
}

int LFSR_Fibonacci_decipher(int binary[], int a) {
	register int size = a;
	register int seed = 0b1000110101101000;
	// x^16 + x^15 + x^13 + x^4
	register int key_size = size / 16;
	register int dop_key_size = size % 16; 
	if (dop_key_size != 0)
		key_size++;
	register int* key = new int[size];
	for (int i = 0; i < key_size; i++) {
		register int newBit = ((seed >> 15) & 1) ^ ((seed >> 14) & 1) ^ ((seed >> 12) & 1) ^ ((seed >> 3) & 1);
		seed = (seed >> 1) | (newBit << 15);
		if (dop_key_size == 0) {
			for (int k = i * 16, j = 15; (k <= i * 16 + 15) && (j >= 0); k++, j--)
				key[k] = (seed >> j) & 1;
		}
		else {
			if (i != key_size - 1) {
				for (int k = i * 16, j = 15; (k <= i * 16 + 15) && (j >= 0); k++, j--)
					key[k] = (seed >> j) & 1;
			}
			else {
				for (int k = i * 16, j = 15; (k <= i * 16 + dop_key_size - 1) && (j >= 0); k++, j--)
					key[k] = (seed >> j) & 1;
			}
		}
	}
	for (int i = 0; i < size; i++)
		binary[i] ^= key[i];
	delete[] key;
	return *binary;
}

void main() {
	setlocale(LC_ALL, "Rus");
	register string str;
	cout << "Ââåäèòå áèíàðíîå ÷èñëî" << endl;
label:
	getline(cin, str);
	register int size = str.length();
	register int* binary = new int[size];
	if ((size == 0)) {
		cout << "Îøèáêà ââîäà ÷èñëà, ïîïðîáóéòå åùå ðàç:" << endl;
		goto label;
	}
	for (int j = 0; j < size; j++) {
		if ((str[j] != '0') && (str[j] != '1') && (str[j] != '\0')){
			cout << "Îøèáêà ââîäà ÷èñëà, ïîïðîáóéòå åùå ðàç:" << endl;
			goto label;
		}
		if (str[j] == '1')
			binary[j] = 1;
		else 
			binary[j] = 0;
	}
	LFSR_Fibonacci_cipher(binary, size);
	for (int i = 0; i < size; i++) 
		cout << binary[i];
	cout << " - øèôðîâêà";
	cout << endl;

	LFSR_Fibonacci_decipher(binary, size);
	for (int i = 0; i < size; i++) 
		cout << binary[i];
	cout << " - ðàñøèôðîâêà";
	cout << endl;

	delete[] binary;
	system("pause");
}
