#include "Header.h"

enum class Task {
	fermat_exponentiation = 1,
	extended_euclidean = 2,
	modular_inverse = 3,
	enc_ElGamal = 4,
	equation_solver = 5
};

int main() {
	setlocale(LC_ALL, "rus");
	cout << "Введите номер задания: ";
	int Task_num;
	cin >> Task_num;

	Task task = static_cast<Task>(Task_num);

	switch (task)
	{
	case Task::fermat_exponentiation:
		while (true) {
			try {
				string a_str, x_str, p_str;
				cout << "Введите параметры a, x, p (через пробел): ";
				cin >> a_str >> x_str >> p_str;

				mpz_class a(a_str), x(x_str), p(p_str);
				checkInput(a, x, p);

				cout << "Результат используя теарему ферма: " << Fermat(x, a, p) << endl;
				cout << "Результат используя бинарное разложение: " << decomposition(to_2(x), a, p) << endl;
			}
			catch (const exception& e) {
				cerr << e.what() << endl;
			}
		}
		break;
	case Task::extended_euclidean:
	{
		while (true) {
			string c_str, m_str;

			cout << "Введите число c, m (через пробел): ";
			cin >> c_str >> m_str;;

			mpz_class c(c_str), m(m_str);

			try {
				mpz_class d = find_d(c, m);
				cout << "Число d: " << d << endl;
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка ввода: недопустимое число. " << e.what() << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			catch (...) {
				cerr << "Неизвестная ошибка." << endl;
			}
		}
		break;
	}
	case Task::modular_inverse:
	{
		while (true) {
			string c_str, m_str;

			cout << "Введите число c, m (через пробел): ";
			cin >> c_str >> m_str;

			mpz_class c(c_str), m(m_str);

			try {
				mpz_class inverse = mod_inverse(c, m);
				cout << "Обратный элемент " << c << "^{-1} mod " << m << " = " << inverse << endl;
				cout << "Ïðîâåðêà: (" << c << " * " << inverse << ") mod " << m << " = " << (c * inverse) % m << endl;
			}
			catch (const invalid_argument& e) {
				cerr << "Ошибка ввода: недопустимое число. " << e.what() << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			catch (...) {
				cerr << "Неизвестная ошибка." << endl;
			}
		}
		break;
	}
	case Task::enc_ElGamal:
	{
		vector<int> letters;
		vector<pair<mpz_class, mpz_class>> encryp_letters;
		mpz_class p, x, g, y;
		vector<mpz_class> xgy;
		string file_name;

		cout << "Введите путь до файла или можете воспользоваться готовым файлом(C:/Users/makst/source/repos/Praktika2/Praktika2/original_text.txt) : ";
		cin >> file_name;
		Read(file_name, letters);

		tie(encryp_letters, p, xgy) = encryption(letters);

		x = xgy[0];
		g = xgy[1];
		y = xgy[2];

		cout << "Зашифрованный текст храниться в файле: C:/Users/makst/source/repos/Praktika2/Praktika2/output.txt" << endl;
		Encryption_w("output.txt", encryp_letters);

		vector<char> decip_letters = decryption(encryp_letters, p, x);

		cout << "Расшифрованный текст храниться в файле: C:/Users/makst/source/repos/Praktika2/Praktika2/res.txt" << endl;
		Decryption_w("res.txt", decip_letters);

		try {
			mpz_class x_attacked = elgamal_attack(encryp_letters, letters, p, g);
			cout << "Найденный секретный ключ x: " << x_attacked << "\n";
			cout << "Истинный секретный ключ x: " << x << "\n";

			if (x_attacked == x) {
				cout << "Атака удалась\n";
			}
			else {
				cout << Атака не удалась\n";
			}
		}
		catch (const exception& e) {
			cerr << e.what() << "\n";
		}

		break;
	}
	case Task::equation_solver:
	{
		//1256a+847b=119
		int A = 1256, B = 847;
		int a, b;
		int gcd = extended_gcd(A, B, a, b);
		if (gcd != 1) cout << "Решения нет" << endl;
		else cout << "Решение уравнения: " << A << "*" << a*119 << " + " << B << "*" << b*119 << " = " << gcd*119 << endl;
	}
	default:
		break;
	}

	return 0;
}
