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
	cout << "������� ����� �������: ";
	int Task_num;
	cin >> Task_num;

	Task task = static_cast<Task>(Task_num);

	switch (task)
	{
	case Task::fermat_exponentiation:
		while (true) {
			try {
				string a_str, x_str, p_str;
				cout << "������� a, x, p (����� ������): ";
				cin >> a_str >> x_str >> p_str;

				mpz_class a(a_str), x(x_str), p(p_str);
				checkInput(a, x, p);

				cout << "��������� (�����): " << Fermat(x, a, p) << endl;
				cout << "��������� (�������� ����������): " << decomposition(to_2(x), a, p) << endl;
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

			cout << "������� ����� c: ";
			cin >> c_str;

			cout << "������� ������ m: ";
			cin >> m_str;

			mpz_class c(c_str), m(m_str);

			try {
				mpz_class d = find_d(c, m);
				cout << "����� d: " << d << endl;
				cout << "��������: (" << c << " * " << d << ") mod " << m << " = " << (c * d) % m << endl;
			}
			catch (const invalid_argument& e) {
				cerr << "������ �����: ������������ �����. " << e.what() << endl;
			}
			catch (const runtime_error& e) {
				cerr << "������: " << e.what() << endl;
			}
			catch (...) {
				cerr << "����������� ������." << endl;
			}
		}
		break;
	}
	case Task::modular_inverse:
	{
		while (true) {
			string c_str, m_str;

			cout << "������� ����� c: ";
			cin >> c_str;

			cout << "������� ������ m: ";
			cin >> m_str;

			mpz_class c(c_str), m(m_str);

			try {
				mpz_class inverse = mod_inverse(c, m);
				cout << "�������� ������� " << c << "^{-1} mod " << m << " = " << inverse << endl;
				cout << "��������: (" << c << " * " << inverse << ") mod " << m << " = " << (c * inverse) % m << endl;
			}
			catch (const invalid_argument& e) {
				cerr << "������ �����: ������������ �����. " << e.what() << endl;
			}
			catch (const runtime_error& e) {
				cerr << "������: " << e.what() << endl;
			}
			catch (...) {
				cerr << "����������� ������." << endl;
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

		cout << "������� ���� �� ����� ��� ������ ��������������� ������� ������(C:/Users/makst/source/repos/Praktika2/Praktika2/original_text.txt) : ";
		cin >> file_name;
		Read(file_name, letters);

		tie(encryp_letters, p, xgy) = encryption(letters);

		x = xgy[0];
		g = xgy[1];
		y = xgy[2];

		cout << "������������� ����� ��������� � �����: C:/Users/makst/source/repos/Praktika2/Praktika2/output.txt" << endl;
		Encryption_w("output.txt", encryp_letters);

		vector<char> decip_letters = decryption(encryp_letters, p, x);

		cout << "�������������� ����� ��������� � �����: C:/Users/makst/source/repos/Praktika2/Praktika2/res.txt" << endl;
		Decryption_w("res.txt", decip_letters);

		try {
			mpz_class x_attacked = elgamal_attack(encryp_letters, letters, p, g);
			cout << "��������� ��������� ���� x: " << x_attacked << "\n";
			cout << "�������� ��������� ���� x: " << x << "\n";

			if (x_attacked == x) {
				cout << "����� �������!\n";
			}
			else {
				cout << "����� �� �������.\n";
			}
		}
		catch (const exception& e) {
			cerr << "������ ��� ���������� �����: " << e.what() << "\n";
		}

		break;
	}
	case Task::equation_solver:
	{
		//1256a+847b=119
		int A = 1256, B = 847;
		int a, b;
		int gcd = extended_gcd(A, B, a, b);
		if (gcd != 1) cout << "������� ���" << endl;
		else cout << "������� ���������: " << A << "*" << a*119 << " + " << B << "*" << b*119 << " = " << gcd*119 << endl;
	}
	default:
		break;
	}

	return 0;
}