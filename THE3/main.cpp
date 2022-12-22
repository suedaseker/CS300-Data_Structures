#include<iostream>
#include<string>
#include<chrono>
#include<vector>
#include<fstream>
#include<sstream>

#include"HashTable.h"
#include "BinarySearchTree.h"

using namespace std;

class DocumentItem{
public:
    string documentName;
    int count;

    DocumentItem(string name)
            :documentName(name),count(1)
    {}

    bool operator == (const DocumentItem & rhs)
    {
        if(this->documentName == rhs.documentName)
            return true;
        else
            return false;
    }
};

class WordItem{
public:
    string word;
    vector<DocumentItem> documentList;

    WordItem(string input = "")
            :word(input)
    {}

    bool operator < (const WordItem & rhs) const
    {
        if(this->word < rhs.word)
            return true;
        else
            return false;
    }
    bool operator > (const WordItem & rhs) const
    {
        if(this->word > rhs.word)
            return true;
        else
            return false;
    }
    bool operator == (const WordItem & rhs) const
    {
        if(this->word == rhs.word)
            return true;
        else
            return false;
    }
    bool operator != (const WordItem & rhs) const
    {
        if(this->word == rhs.word)
            return false;
        else
            return true;
    }
    //Hash Function for wordItem
    int hash(int hashTableCapacity) const
    {
        unsigned long c,i,h;

        for(i=h=0;word[i];i++)
        {
            c = toupper(word[i]);
            h = ((h << 5) + h) ^ c;
        }
        return (h%hashTableCapacity);
    }

    bool empty() const{
        if(word == ""){
            return true;
        }
        else{
            return false;
        }
    }
};

void editTextFunc(string & text)
{
    for(unsigned int k=0; k<text.length(); k++)
    {
        if(text[k] < 'a' || text[k] > 'z')
        {
            if(text[k] >= 'A' && text[k] <= 'Z')
            {
                text[k] = text[k] + 32;
            }
            else
            {
                text[k] = ' ';
            }
        }

    }
}

int searchDocumentVector(const vector<DocumentItem> & vec, const DocumentItem doc)
{
    for(unsigned int i =0; i<vec.size(); i++)
    {
        if(vec[i].documentName == doc.documentName)
            return i;
    }
    return -1;
};


int main() {
    //PROGRAM START

    int fileCount;
    cout << "Enter number of input files: ";
    cin >> fileCount;
    vector<string> files;

    for (int i = 0; i < fileCount; i++)
    {
        static int c = 1;
        string filename;
        cout << "Enter " << c << ". file name: ";
        cin >> filename;
        files.push_back(filename);
        cin.clear();
        c++;
    }

    //PREPROCESS FILES
    HashTable<WordItem> hashTable(11);
    BinarySearchTree<WordItem> binarySearchTree(WordItem(""));

    for(int i=0; i<fileCount; i++) {
        string fileName = files[i];
        DocumentItem document(fileName);
        ifstream inputStream;
        inputStream.open(fileName.c_str());
        string text, word;
        while (inputStream >> word)
            text = text + " " + word;
        editTextFunc(text);
        istringstream wordStream(text);
        while (wordStream >> word) {
            WordItem newWord(word);

            //PREPROCESS HASHTABLE
            WordItem & item = hashTable.find(newWord);
            if (item.empty()) {
                newWord.documentList.push_back(document);
                hashTable.insert(newWord);
            } else {
                int result = searchDocumentVector(item.documentList, document);
                if (result == -1) {
                    item.documentList.push_back(document);
                } else {
                    item.documentList[result].count += 1;
                }
            }

            //PREPROCESS BINARY SEARCH TREE
            WordItem & treeItem = binarySearchTree.find(newWord);
            if(treeItem != binarySearchTree.ITEM_NOT_FOUND)
            {
                bool foundDoc = false;
                int index = searchDocumentVector(treeItem.documentList, document);
                if (index != -1) {
                    treeItem.documentList[index].count++;
                }
                else {
                    treeItem.documentList.push_back(document);
                }
            }
            else
            {
                binarySearchTree.insert(newWord);
                binarySearchTree.find(newWord).documentList.push_back(document);
            }

        }
        wordStream.clear();
        inputStream.close();
    }

    cout<<endl;
    cout<<"After preprocessing, the unique word count is "<<hashTable.getHashTableSize()<<". Current load ratio is "<<hashTable.getCurrentLoadFactor()<<endl;
    cout<<endl;

    string query;
    cout<<"Enter queried words in one line: ";
    cin.ignore();
    getline(cin, query);
    editTextFunc(query);
    string queryWord;
    vector<WordItem> queryWordVector;
    istringstream queryStream(query);
    while(queryStream>>queryWord)
    {
        queryWordVector.push_back(WordItem(queryWord));
    }

    int k = 100;
    auto start = std::chrono::high_resolution_clock::now();
    // QueryDocuments(with BST);
    vector<WordItem> binarySearchTreeResultVector;
    for (int i = 0; i < k; i++)
    {
        for(int c=0; c< queryWordVector.size(); c++){
            WordItem & result = binarySearchTree.find(queryWordVector[c]);
        }
    }
    for(int c=0; c< queryWordVector.size(); c++){
        WordItem & result = hashTable.find(queryWordVector[c]);
        if(! result.empty()) {
            binarySearchTreeResultVector.push_back(result);
        }
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
    // cout << "\nTime: " << BSTTime.count() / k << "\n";
    vector<WordItem> hashTableResultVector;
    start = std::chrono::high_resolution_clock::now();
    // QueryDocuments (with hashtable);
    for (int i = 0; i < k; i++)
    {
        for(int c=0; c< queryWordVector.size(); c++){
            WordItem & result = hashTable.find(queryWordVector[c]);
        }
    }
    for(int c=0; c< queryWordVector.size(); c++){
        WordItem & result = hashTable.find(queryWordVector[c]);
        if(! result.empty()) {
            hashTableResultVector.push_back(result);
        }
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
    bool check = true;
    if(hashTableResultVector.size() == 0){
        check = false;
        cout<<"No document contains the given query"<<endl;
    }
    if(binarySearchTreeResultVector.size() == 0){
        check = false;
        cout<<"No document contains the given query"<<endl;
    }
    if (check){
        for(int d=0; d<files.size(); d++){
            DocumentItem document(files[d]);
            cout<<"in Document "<<files[d]<<", ";
            for(int m = 0; m<hashTableResultVector.size(); m++){
                WordItem wordItem = hashTableResultVector[m];
                string word = wordItem.word;
                int documentIndex = searchDocumentVector(wordItem.documentList, document);
                cout<<wordItem.word<<" found "<<wordItem.documentList[documentIndex].count<<" times, ";
            }
            cout<<endl;

            cout<<"in Document "<<files[d]<<", ";
            for(int m = 0; m<binarySearchTreeResultVector.size(); m++){
                WordItem wordItem = binarySearchTreeResultVector[m];
                string word = wordItem.word;
                int documentIndex = searchDocumentVector(wordItem.documentList, document);
                cout<<wordItem.word<<" found "<<wordItem.documentList[documentIndex].count<<" times, ";
            }
            cout<<endl;
        }
    }
    cout << "\nTime: " << BSTTime.count() / k << "\n";
    cout << "\nTime: " << HTTime.count() / k << "\n";
    
    double speedUp = double(BSTTime.count())/HTTime.count();
    cout<<"Speed Up: "<<speedUp<<endl;

    hashTable.makeEmpty();

    return 0;
}
