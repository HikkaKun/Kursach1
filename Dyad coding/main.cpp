#include <iostream>
#include <conio.h>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
	setlocale(0, "");
	char n;
	do
	{
		cout << "1 - �����\n2 - �����������\n";
		n = _getche();
		cout << "\n";
	} while (n != '1' && n != '2');

	ifstream in;
	string name;
	do
	{
		cout << "������� ��� �������� �����:\n";
		getline(cin, name);
		in.open(name, ios::binary);
		if (!in.is_open()) cout << "������� ���� �� ������!\n";
	} while (!in.is_open());

	stringstream ss;
	ss << in.rdbuf();
	string text = ss.str();
	in.close();

	ofstream out;
	do
	{
		cout << "������� ��� ��������� �����:\n";
		getline(cin, name);
		out.open(name, ios::binary);
		if (!out.is_open()) cout << "�� ������� ������� �������� ����!\n";
	} while (!out.is_open());

	if (n == '1')
	{
		set<char> text_chars;
		map<string, int> dict;
		for (int k = 1; k < text.size(); k++)
		{
			dict[text[k - 1] + ""s + text[k]] += 1;
			text_chars.insert(text[k - 1]);
		}

		vector<char> free_chars;
		for (unsigned char i = 0; i < 255; i++)
			if (!text_chars.count(i))
				free_chars.push_back(i);

		vector<pair<int, string>> sort_dict;
		for (auto i : dict)
			if (i.second > 3) sort_dict.push_back(make_pair(i.second, i.first));

		dict.clear();

		sort(sort_dict.begin(), sort_dict.end(), [](auto& a, auto& b) { return a.first > b.first; });

		vector<pair<string, char>> d;

		for (int i = 0; i < min(free_chars.size(), sort_dict.size()); i++)
			d.push_back(make_pair(sort_dict[i].second, free_chars[i]));

		unsigned char size = d.size();

		out << size;

		string d_buf;

		for (auto i : d)
		{
			d_buf.append(i.first);
			d_buf.append(string(1, i.second));
			int sPos;
			while ((sPos = text.find(i.first, 0)) != string::npos)
				text.replace(sPos, 2, string(1, i.second));
		}

		out << d_buf << text;
	}
	else
	{
		int size = (unsigned char)text[0] * 3;
		map<char, string> d;
		for (int i = 1; i < size + 1; i+=3)
			d[text[i+2]] = text[i] + ""s + text[i + 1];
		text.erase(0, size + 1);
		int sPos;
		for (auto i : d)
		{
			while ((sPos = text.find(i.first, 0)) != string::npos)
				text.replace(sPos, 1, i.second);
		}
		out << text;
	}
	out.close();

	return 0;
}