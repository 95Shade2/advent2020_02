#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Password {
    private:
        string password;    //holds the password
        int min_amount;     //holds the min amount of the letter assigned
        int max_amount;     //holds the max amount of the letter assigned
        char letter;        //the letter the password needs
        bool valid1;        //whether or not this password is valid
        bool valid2;        //whether or not this password is valid for part 2

    public:
        Password() {
            //set everything to invalid values
            Set_Password("");
            Set_Min(-1);
            Set_Max(-1);
            Set_Letter(' ');
            Set_Valid(false);
        }

        Password(string pass, int mi, int ma, char chr) {
            Set_Password(pass);
            Set_Min(mi);
            Set_Max(ma);
            Set_Letter(chr);
            Set_Valid(false);   //invalid until checked to be valid
            Set_Valid2(false);   //invalid until checked to be valid
        }

        void Set_Password(string new_password) {
            password = new_password;
        }

        void Set_Min(int min_value) {
            min_amount = min_value;
        }

        void Set_Max(int max_value) {
            max_amount = max_value;
        }

        void Set_Letter(char chr) {
            letter = chr;
        }

        void Set_Valid(bool is_valid) {
            valid1 = is_valid;
        }

        void Set_Valid2(bool is_valid) {
            valid2 = is_valid;
        }

        int Get_Max() {
            return max_amount;
        }

        int Get_Min() {
            return min_amount;
        }

        char Get_Letter() {
            return letter;
        }

        string Get_Password() {
            return password;
        }

        bool Get_Valid() {
            return valid1;
        }

        bool Get_Valid2() {
            return valid2;
        }
};

///converts a string of numbers into an int - assumes text is valid
int Int(string num) {
    int num_i = 0;

    while (num.size() > 0) {
        num_i *= 10;
        num_i += num[0] - '0';
        num = num.substr(1);
    }

    return num_i;
}

int Count(string text, char chr) {
    int num = 0;
    for (int c = 0; c < text.size(); c++) {
        if (text[c] == chr) {
            num++;
        }
    }
    return num;
}

int test = 0;

void Validate(Password &pass) {
    char letter = pass.Get_Letter();
    int min_amount = pass.Get_Min();
    int max_amount = pass.Get_Max();
    string password = pass.Get_Password();
    int number = Count(password, letter);

    //validate part 1
    if (number >= min_amount && number <= max_amount) {
        pass.Set_Valid(true);
    }

    //validate part 2 - the letters are not zero indexed
    if (password[min_amount-1] == letter ^ password[max_amount-1] == letter) {
        pass.Set_Valid2(true);
    }
}

///Gets a password and validates it
Password Get_Password(string line) {
    //assume password is in correct format
    int min_v, max_v;
    string pass;
    char chr;
    int index_dash = line.find('-');
    int index_space = line.find(' ');
    int index_colon = line.find(':');

    //get the data from the line
    min_v = Int(line.substr(0, index_dash));
    index_dash++;
    max_v = Int(line.substr(index_dash, index_space - index_dash));
    index_space++;
    chr = line.substr(index_space, index_colon - index_space)[0];
    index_colon += 2;
    pass = line.substr(index_colon);

    Password password(pass, min_v, max_v, chr);

    //set valid or invalid
    Validate(password);

    return password;
}

///Gets the number of valid passwords
int Num_Valids(vector<Password> passwords, int part = 1) {
    Password pass;
    int amount = 0;

    for (int p = 0; p < passwords.size(); p++) {
        pass = passwords[p];

        if (part == 1) {
            if (pass.Get_Valid()) {
                amount++;
            }
        }
        else {
            if (pass.Get_Valid2()) {
                amount++;
            }
        }
    }

    return amount;
}

///Gets the passwords
vector<Password> Get_Passwords() {
    ifstream file;
    string line;
    vector<Password> passwords;

    file.open("passwords.txt");

    getline(file, line);
    while (file) {
        passwords.push_back(Get_Password(line));
        getline(file, line);
    }

    file.close();

    return passwords;
}

int main()
{
    vector<Password> passwords;
    int valid_count;

    passwords = Get_Passwords();

    //get the valid password count for part 1
    valid_count = Num_Valids(passwords);
    cout << valid_count << endl;

    //get the valid password count for part 2
    valid_count = Num_Valids(passwords, 2);
    cout << valid_count << endl;

    return 0;
}
