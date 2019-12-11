#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
	int num;
	vector<string> words;
	Solution(vector<string> ss) : words(ss){};
	~Solution(){};
	void uniqueMorseRepresentations()
	{
		vector<string> morses;
		for (auto word : words)
		{
			string morse = "";
			for (auto letter : word)
			{
				morse.append(table[letter - 'a']);
			}
			morses.push_back(morse);
		}
		num = get_unique_number(morses);
	}

	int get_unique_number(vector<string> morses)
	{
		vector<string> hash;
		for (auto s : morses) {
			int flag = 0;
			for (auto it : hash)
			{
				if (it == s)
				{
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				hash.push_back(s);
			}
		}
		return hash.size();
	}


private:
	string table[26] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..",\
			"--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

};

int main() 
{
	Solution x({"gin", "zen", "gig", "msg","a","a"});
	x.uniqueMorseRepresentations();
	printf("%d\n", x.num);
	system("pause");
}