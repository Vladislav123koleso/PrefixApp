#include "cpp/tree.cpp"


int main()
{
    // Создаем корень дерева
    Node* root = getNewNode();

    // Вставляем некоторые слова для примера
    insert(root, "apple");
    insert(root, "app");
    insert(root, "application");
    insert(root, "banana");
    insert(root, "bat");

    string prefix;

    while(prefix != "exit" || "Exit")
    {
        // Запрашиваем префикс у пользователя и выводим слова с этим префиксом
        cout << "Enter prefix: ";
        cin >> prefix;
        displayPrefixWords(root, prefix);
    }
    


    return 0;
}