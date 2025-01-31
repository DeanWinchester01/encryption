#include <iostream>
#include <map>
#include <string>

using namespace std;

map<char, char> key;
map<char, char> secondKey = {
    {'a', 'c'},
    {'b', 'k'},
    {'c', 'm'},
    {'d', 'e'},
    {'e', 'x'},
    {'f', 'b'},
    {'g', 't'},
    {'h', 'r'},
    {'i', 'n'},
    {'j', 'p'},
    {'k', 'o'},
    {'l', 'u'},
    {'m', 'a'},
    {'n', 'w'},
    {'o', 'v'},
    {'p', 'z'},
    {'q', 's'},
    {'r', 'y'},
    {'s', 'g'},
    {'t', 'd'},
    {'u', 'l'},
    {'v', 'i'},
    {'w', 'h'},
    {'x', 'q'},
    {'y', 'j'},
    {'z', 'f'},
    {'1', 'C'},
    {'2', 'J'},
    {'3', 'G'},
    {'4', 'T'},
    {'5', 'Q'},
    {'6', 'B'},
    {'7', 'R'},
    {'8', 'M'},
    {'9', 'X'},
    {'0', 'O'},
};
string firstKey = "RSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789áéíóúüñß";
string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char GetCorrectLetter(char letter, map<char, char> key) {
    char defaultChar = '_';
    for (auto entry : key) {
        if (entry.second == letter)
            return entry.first;
    }
    return defaultChar;
}

string Decrypt(string message, map<char, char> key) {
    string decrypted = "";
    for (char letter : message) {
        char correctLetter = GetCorrectLetter(letter, key);
        if (correctLetter == '_')
            decrypted += letter;
        else
            decrypted += GetCorrectLetter(letter, key);
    }
    return decrypted;
}

string reverse(string word) {
    string newWord = "";
    string even = "";
    string uneven = "";

    for (int i = 0; i < word.length(); i++) {
        if (i % 2 == 0) {
            even += word[i];
        }
        else {
            uneven += word[i];
        }
    }
    cout << even << uneven << endl;
    newWord = even + uneven;

    return newWord;
}

string unmix(string word) {
    string newWord = "";
    string uneven = "";
    string even = "";

    for (int i = 0; i < word.length(); i++) {
        {
            if (word.length() % 2 == 0) {
                if (i < word.length() / 2)
                    even += word[i];
                else
                    uneven += word[i];
            }
            else {
                if (i <= word.length() / 2)
                    even += word[i];
                else
                    uneven += word[i];
            }
        }
    }

    int i = 0;
    bool evenTurn = true;
    while (newWord.length() < word.length()) {
        if (evenTurn) {
            newWord += even[i];
            evenTurn = false;
        }
        else {
            newWord += uneven[i];
            evenTurn = true;
            i++;
        }
    }

    return newWord;
}

string Translate(string pass, map<char, char> key) {
    string newPass = "";

    for (char letter : pass) {
        cout << newPass << endl;
        if (key.find(letter) == key.end())
            newPass += letter;
        else
            newPass += key[letter];
    }

    return newPass;
}

int GetRandomNum(int lower, int upper) {
    int number = lower + rand() % (upper - lower);
    return number;
}

string RemoveGarbage(string message) {
    int messageFound = sqrt(message.length());
    /*int a = 1;
    int b = 1;
    int length = message.length() * -1;
    int discriminant = b * b - 4 * a * length;
    int x1 = (-b + sqrt(discriminant)) / (2 * a);
    string actualMessage = message.substr(x1, x1);
    */
    string actualMessage = message.substr(messageFound, messageFound);

    return actualMessage;
}

string AddGarbage(string message) {
    string newMessage = "";
    int amountOfGarbage = pow(message.length(), 2);

    for (int i = 0; i < amountOfGarbage; i++) {
        if (i == message.length()) {
            newMessage += message;
            char chosenChar = firstKey[GetRandomNum(0, firstKey.length())];
            newMessage += chosenChar;
        }
        else {
            char chosenChar = firstKey[GetRandomNum(0, firstKey.length())];
            newMessage += chosenChar;
        }
    }

    return newMessage;
}

string EncryptMessage() {
    cout << "Input message to encrypt" << endl;
    string pass;
    getline(cin, pass);
    system("cls");
    if (pass.length() < 2) {
        pass = "Message too short to decrypt";
    }
    else {
        for (int i = 0; i < 3; i++) {
            pass = reverse(pass);
            pass = Translate(pass, secondKey);
        }

        pass = Translate(pass, secondKey);
        pass = reverse(pass);
        pass = Translate(pass, key);
        pass = AddGarbage(pass);

    }
    return pass;
}

string DecryptMessage() {
    cout << "Input message to decrypt" << endl;
    string pass;
    getline(cin, pass);
    system("cls");
    string decrypted = "";
    if (pass.length() < 2) {
        decrypted = "Message too short to decrypt";
    }
    else {
        decrypted = RemoveGarbage(pass);
        cout << decrypted << endl;
        decrypted = Decrypt(decrypted, key);
        cout << decrypted << endl;
        decrypted = unmix(decrypted);
        cout << decrypted << endl;
        decrypted = Decrypt(decrypted, secondKey);
        cout << decrypted << endl;

        for (int i = 0; i < 3; i++) {
            decrypted = unmix(decrypted);
            cout << decrypted << endl;
            decrypted = Decrypt(decrypted, secondKey);
            cout << decrypted << endl;
        }

    }

    return decrypted;
}

int main() {
    for (int i = 0; i < alphabet.length(); i++) {
        key.insert({ alphabet[i], firstKey[i] });
    }

    while (true) {
        system("cls");
        cout << "1. Encrypt message" << endl;
        cout << "2. Decrypt message" << endl;
        cout << "3. Exit" << endl;

        string result;
        getline(cin, result);
        system("cls");

        if (result == "1") {
            string pass = EncryptMessage();
            cout << "Encrypted message: " << pass << endl;
        }

        if (result == "2") {
            string pass = DecryptMessage();
            cout << "Message: " << pass << endl;
        }

        if (result == "3")
            exit(0);

        cout << "Hit enter to continue" << endl;
        getline(cin, result);
            
    }

    return 0;
}