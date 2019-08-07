#include "SymbolTable.h"
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <list>
using namespace std;


struct hashNode
{
	stack<int> lines;
	string s;
	hashNode* next = NULL;
};

class SymbolTableImpl
{
public:
	SymbolTableImpl()
	{
		for (int i = 0; i < 20000; i++)
			table[i] = NULL;
	};
	~SymbolTableImpl()
	{
		while (!todelete.empty()) {
			delete todelete.top();
			todelete.pop();
		}
	};
	void enterScope();
	bool exitScope();
	bool declare(const string& id, int lineNum);
	int find(const string& id) const;
	void popLine(const string& id) {
		//cout << "popping " << id << "." << endl;
		int x = hashfunc(id);
		hashNode* ptr = table[x];
		while (ptr != NULL) {
			if (ptr->s == id && !ptr->lines.empty()) {
				ptr->lines.pop();
				return;
			}
			ptr = ptr->next;
		}
		return;
	};

	int hashfunc(const string& id) const {
		int hashnumber = 0;
		for (int i = 0; i < id.size(); i++) {
			hashnumber += (int)id[i] * (2 ^ (92 * i) + 1);
		}
		return (hashnumber % 20000);
	};

private:
	vector<string> m_ids;
	hashNode* table[20000];
	stack<hashNode*> todelete;
};

void SymbolTableImpl::enterScope()
{
	m_ids.push_back("");
}

bool SymbolTableImpl::exitScope()
{
	while (!m_ids.empty() && m_ids.back() != "")
	{
		popLine(m_ids.back());
		m_ids.pop_back();
	}
	if (m_ids.empty())
		return false;
	m_ids.pop_back();;
	return true;
}

bool SymbolTableImpl::declare(const string& id, int lineNum)
{
	if (id.empty())
		return false;
	size_t k = m_ids.size();
	while (k > 0)
	{
		k--;
		if (m_ids[k].empty())
			break;
		if (m_ids[k] == id)
			return false;
	}
	m_ids.push_back(id);
	int x = hashfunc(id);
	if (table[x] == NULL) {
		table[x] = new hashNode;
		todelete.push(table[x]);
		table[x]->s = id;
		table[x]->lines.push(lineNum);
		return true;
	}
	hashNode* ptr = table[x];
	hashNode*lagger;
	while (ptr != NULL) {
		if (ptr->s == id) {
			ptr->lines.push(lineNum);
			return true;
		}
		lagger = ptr;
		ptr = ptr->next;
	}
	lagger->next = new hashNode;
	todelete.push(lagger->next);
	lagger->next->lines.push(lineNum);
	lagger->next->s = id;
	return true;
}

int SymbolTableImpl::find(const string& id) const
{
	int x = hashfunc(id);
	hashNode* ptr = table[x];
	while (ptr != NULL) {
		if (ptr->s == id && !ptr->lines.empty()) {
			return ptr->lines.top();
		}
		ptr = ptr->next;
	}
	return -1;
}

//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
	m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
	delete m_impl;
}

void SymbolTable::enterScope()
{
	m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
	return m_impl->exitScope();
}

bool SymbolTable::declare(const string& id, int lineNum)
{
	return m_impl->declare(id, lineNum);
}

int SymbolTable::find(const string& id) const
{
	return m_impl->find(id);
}

