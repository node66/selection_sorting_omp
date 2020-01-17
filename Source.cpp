#include <iostream>
#include <omp.h>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	setlocale(0, "");
	const unsigned n(100); // ������ �������
	int  temp[n];
	cout << "�� ��������������� ������: " << endl;
	for (unsigned i = 0; i < n; i++) {
		temp[i] = n - i;
		cout << temp[i] << " ";
	}
	cout << endl;
	
	int min_index_all(0);
	int min_value_all(INT_MAX);
	/*��������� ������������ ������ � ������ ����������� */
#pragma omp parallel shared(temp,min_index_all,min_value_all) 
	{
		/*��������� ���������� */
		int min_index, min_value;

		for (int i = 0; i < n - 1; i++) {
			min_index = i;
			min_value = temp[min_index];
			/*������������ ���� */
#pragma omp parallel for 
			for (int j = i + 1; j < n; j++)
				if (temp[j] < temp[min_index]) {
					min_index = j;
					min_value = temp[min_index];
				}
			/*���� ������ -> ���� ����� ����� ��������� ���� � ��� ���� �� ������� ��� */
#pragma omp critical
			{
				if (min_value < min_value_all) {
					min_index_all = min_index;
					min_value_all = min_value;
				}
			}
			/*���� ������� ���� �������*/
#pragma omp barrier
			/*���� ���� ����������� ������ ����� �������  */
#pragma omp single
			{
				//������ ��-�� �������
				swap(temp[i], temp[min_index]);                         
				min_index_all = i + 1;
				min_value_all = INT_MAX;
			}
		}
	}
	cout << "���������������: " << endl;
	for (const auto i : temp)
		cout << i << " ";
	cout << endl;
	//�������� �� �����������������
	cout << (is_sorted(begin(temp), end(temp)) ? "Yes" : "No") << endl;

	system("pause");
	return 0;
}
