#pragma once
#include <iostream>

#define ALPHABET_SIZE 20    

using namespace std;



struct Node
{
    struct Node *children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord = false;
    int freq = 0;
};


// возаращает новый узел с пустыми детьми
    Node *getNewNode(void)
    {
        // выделение памяти под новый узел
        struct Node *pNode = new Node;

        // устанавливаем флаг конца слова в false
        pNode->isEndOfWord = false;

        // инициализируем детей нулевым уазателем
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = nullptr;
        }
        return pNode;
    }
//вставка
void insert(Node* root, string key)
{
    Node* node = root;

    for(int i = 0;i<key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if(!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        node->children[index]->freq++;
        node = node->children[index];
    }
    // помечаем последний узлел как конец слова
    node->isEndOfWord = true;
}

// Возвращает true если ключ есть в дереве, иначе false
bool search(Node *root,string key)
{
    struct Node *node = root;

    for(int i = 0;i<key.length(); i++)
    {
        int index = key[i] - 'a';

        if(!node->children[index])
        {
            return false;
        }
        node = node->children[index];
    }
    return (node != nullptr && node->isEndOfWord);
}

// Возвращает true если root имеет лист, иначе false
bool isEmpty(Node* root)
{
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->children[i])
        {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция удаления ключа из дерева
Node* remove(Node* root,string key, int depth)
{
    //если дерево пустое
    if(!root)
    {
        return nullptr;
    }

    //если дошли до конца ключа
    if(depth = key.size())
    {
        //этот узел больше не конец слова
        if(root->isEndOfWord)
        {
            root->isEndOfWord = false;
        }

        // если ключ не является префиксом
        if(isEmpty(root))
        {
            delete root;
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth+1);


    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 

    if(isEmpty(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = nullptr;
    }

    return root;
}



// Рекурсивная функция для обхода поддерева и вывода всех слов
void displayWords(Node* node, string prefix)
{
    // Если узел пустой, возвращаемся
    if (!node)
        return;

    // Если текущий узел - конец слова, выводим его
    if (node->isEndOfWord)
        cout << prefix << endl;

    // Рекурсивно вызываем эту функцию для всех дочерних узлов
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            // Формируем префикс, добавляя текущий символ
            string newPrefix = prefix + char('a' + i);
            // Рекурсивно вызываем функцию для дочернего узла с новым префиксом
            displayWords(node->children[i], newPrefix);
        }
    }
}

// Функция для вывода всех слов с заданным префиксом
void displayPrefixWords(Node* root, string prefix)
{
    Node* node = root;

    // Поиск узла, соответствующего префиксу
    for (int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i] - 'a';
        if (!node->children[index])
        {
            // Если префикс не найден, просто завершаем функцию
            cout << "No words with prefix '" << prefix << "' found." << endl;
            return;
        }
        node = node->children[index];
    }

    // Вывод всех слов с заданным префиксом
    displayWords(node, prefix);
}
