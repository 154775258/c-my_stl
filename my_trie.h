#pragma once
#include<cstring>
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

class my_trie
{
public:
	my_trie() {
		m_data = new Info();
	}

	~my_trie() {
		delete m_data;
	}

	void insert(string word) {
		Info* t = m_data;
		for (int i = 0; i < word.size(); i++) {
			if (t->children[word[i]] == nullptr) {
				t -> children[word[i]]  = new Info();
			}
			t = t->children[word[i]];
		}
		if (!t->end) {
			words.push_back(word);
			wordIndex[word] = words.size() - 1;
		}
		t -> end++;
	}

	void moveWord(string word) {
		Info* t = m_data;
		for (int i = 0; i < word.size(); i++) {
			if (t->children[word[i]] == nullptr) {
				t->children[word[i]] = new Info();
			}
			t = t->children[word[i]];
		}
		if(t -> end)
		t->end--;
		if(t->end == 0){
			int q = wordIndex[word];
			string tmp = words.back();
			swap(words[wordIndex[word]], words.back());
			words.pop_back();
			wordIndex[tmp] = q;
			wordIndex.erase(word);
		}
	}

	int wordFrequency(string word) {
		Info* t = m_data;
		for (int i = 0; i < word.size(); i++) {
			if (t->children[word[i]] == nullptr) {
				return 0;
			}
			t = t->children[word[i]];
		}
		return t->end;
	}

	bool search(string word) {
		Info* t = m_data;
		for (int i = 0; i < word.size(); i++) {
			if (t->children[word[i]] == nullptr) {
				return 0;
			}
			t = t->children[word[i]];
		}
		return t->end;
	}

	bool startsWith(string word) {
		Info* t= m_data;
		for (int i = 0; i < word.size(); i++) {
			if (t->children[word[i]] == NULL) {
				return 0;
			}
			t = t->children[word[i]];
		}
		return 1;
	}

	my_trie& operator = (my_trie& val) {
		delete m_data;
		m_data = val.m_data;
		return*this;
	}

	vector<string> allWords() {
		return words;
	}

private:
	struct Info {
		int end;
		Info* children[128];
		Info() {
			end = 0;
			memset(children, 0, sizeof(children));
		}

		~Info() {
			end = 0;
			memset(children, 0, sizeof(children));
		}
	};
	Info* m_data;
	vector<string> words;
	unordered_map<string, int> wordIndex;
};

