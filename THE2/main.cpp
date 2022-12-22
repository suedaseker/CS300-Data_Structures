#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Tree.h"
#include "strutils.h"
using namespace std;

struct DocumentItem
{
    string documentName;
    int count;
    DocumentItem(string s = "", int c = 1) : documentName(s), count(c) {};
};

struct WordItem
{
    string word;
    vector<DocumentItem*> documentArray;
    WordItem(string s) : word(s) {};
    // List of DocumentItem’s. In order to keep the documents
};

struct WordCount
{
    string word;
    int count;
    WordCount(string s = "", int c = 0) : word(s), count(c) {};
};
struct OutputItem
{
    string filename;
    vector<WordCount*> wordList;
    OutputItem(string f = "") : filename(f) {};
};

DocumentItem* inArray(const string& filename, const vector<DocumentItem*> documentArray)
{
    if (documentArray.size() != 0)
    {
        for (int i = 0; i < documentArray.size(); i++)
        {
            if (documentArray[i]->documentName == filename)
            {
                return documentArray[i];
            }
        }
    }
    return NULL;
}


int inOutput(const string filename, const vector<OutputItem>& out)
{
    for (int i = 0; i < out.size(); i++)
    {
        if (out[i].filename == filename)
        {
            return i;
        }
    }
    return -1;
}

void PrintOut(vector<OutputItem>& out)
{
    for (int i = 0; i < out.size(); i++)
    {
        cout << "in Document " << out[i].filename << ", ";
        for (int j = 0; j < out[i].wordList.size(); j++)
        {
            cout << out[i].wordList[j]->word << " found " << out[i].wordList[j]->count;
            if (j != (out[i].wordList.size() - 1))
                cout << " times, ";
            else
                cout << " times." << endl;
        }
    }
}

bool isAlpha(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if ('a' > s[i] || s[i] > 'z')
            return false;
    }
    return true;
}

void readFile(string& filename, AvlTree<string, WordItem*>& wordTree)
{
    ifstream input;
    input.open(filename.c_str());

    string s;
    while (input >> s)
    {
        ToLower(s);
        if (isAlpha(s))
        {
            WordItem* w = wordTree.find(s);
            if (w == NULL) //if the word is not in the wordTree
            {
                WordItem* word = new WordItem(s);
                DocumentItem* doc = new DocumentItem(filename);
                word->documentArray.push_back(doc);
                wordTree.insert(s, word);
            }
            else
            {
                DocumentItem* d = inArray(filename, w->documentArray);
                if (d == NULL) //if the document name is not in the array
                {
                    DocumentItem* doc = new DocumentItem(filename);
                    w->documentArray.push_back(doc);
                }
                else
                    d->count += 1;
            }
        }
    }
    input.close();
}

int main()
{
    int n;
    cout << "Enter number of input files: ";
    cin >> n;
    vector<string> files;
    for (int i = 0; i < n; i++)
    {
        static int c = 1;
        string filename;
        cout << "Enter " << c << ". file name: ";
        cin >> filename;
        files.push_back(filename);
        cin.clear();
        c++;
    }

    vector<string> queries;
    cout << "Enter queried words in one line: ";
    cin.ignore();
    string t;
    getline(cin, t);
    istringstream iss(t);
    string word;
    while (iss >> word)
    {
        ToLower(word);
        queries.push_back(word);
    }

    //form the tree while reading all files
    AvlTree<string, WordItem*> wordTree;
    for (int i = 0; i < files.size(); i++)
    {
        string filename = files[i];
        readFile(filename, wordTree);
    }

    vector<OutputItem> out;
    for (int i = 0; i < queries.size(); i++)
    {
        string query = queries[i];
        //find if every query is in the tree and cout the results
        WordItem* w = wordTree.find(query);
        if (w != NULL) //found
        {
            for (int i = 0; i < files.size(); i++)
            {
                for (int j = 0; j < w->documentArray.size(); j++)
                {
                    if (files[i] == w->documentArray[j]->documentName)
                    {
                        int index = inOutput(files[i], out);
                        if (index != -1)
                        {
                            WordCount* wc = new WordCount(query, w->documentArray[j]->count);
                            out[index].wordList.push_back(wc);
                        }
                        else {
                            WordCount* wc = new WordCount(query, w->documentArray[j]->count);
                            OutputItem* o = new OutputItem(files[i]);
                            o->wordList.push_back(wc);
                            out.push_back(*o);
                        }
                    }
                }
            }
        }
    }

    if (out.size() == 0)
    {
        cout << "No document contains the given query" << endl;
    }
    else
    {
        PrintOut(out);
    }

    wordTree.makeEmpty();

    return 0;
}
