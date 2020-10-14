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
		cout << "1 - сжать\n2 - распаковать\n";
		n = _getche();
		cout << "\n";
	} while (n != '1' && n != '2');

	ifstream in;
	string name = "C:\\Users\\HomoHikka\\Desktop\\input1.txt";
	in.open(name, ios::binary);
	//do //вместо N че то другое подставить не забыть
	//{
	//	cout << "¬ведите им€ входного файла:\n";
	//	getline(cin, name);
	//	in.open(name);
	//	if (!in.is_open()) cout << "¬ходной файл не найден!\n";
	//} while (!in.is_open());

	stringstream ss;
	ss << in.rdbuf();
	string text = ss.str();
	in.close();

	ofstream out;
	//cout << "¬ведите им€ выходного файла:\n";
	//getline(cin, name);
	name = "C:\\Users\\HomoHikka\\Desktop\\output.txt";
	out.open(name, ios::binary);

	if (n == '1')
	{
		set<char> text_chars;
		map<string, int> dict;
		int k = 1;
		while (k < text.size())
		{
			dict[text[k - 1] + ""s + text[k]] += 1;
			text_chars.insert(text[k - 1]);
			k++;
		}

		vector<char> free_chars;
		for (unsigned char i = 0; i < 255; i++)
			if (!text_chars.count(i))
				free_chars.push_back(i);

		vector<pair<int, string>> sort_dict;
		for (auto i : dict)
			if (i.second > 3) sort_dict.push_back(make_pair(i.second, i.first));

		dict.clear();

		auto cmp = [](std::pair<int, string> const& a, std::pair<int, string> const& b)
		{
			return a.first > b.first;
		};

		sort(sort_dict.begin(), sort_dict.end(), cmp);

		//for (auto i : sort_dict)
		//	cout << i.first << " " << i.second << endl;

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
	out.close(); //1
}