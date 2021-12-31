#include "Utilities.h"

void clearScreen()
{
    system("cls");
    _flushall();
}

void gotoxy(short row, short col)
{
    static HANDLE hConsoleOutput = NULL;
    if (NULL == hConsoleOutput)
    {
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD dwCursorPosition = { row, col };
    cout.flush();
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

bool is_key_in_fileName(const string& fileName, const string& key)
{
    int size = key.size();
    int key_index = 0;

    for (int i = 0; i < fileName.size() && key_index != size; i++)
    {
        if (isupper(key[key_index]))
        {
            if (fileName[i] == tolower(key[key_index]) || fileName[i] == key[key_index])
            {
                key_index++;
            }
            else
            {
                key_index = 0;
            }
        }
        else
        {
            if (fileName[i] == toupper(key[key_index]) || fileName[i] == key[key_index])
            {
                key_index++;
            }
            else
            {
                key_index = 0;
            }
        }
    }
    if (key_index == size)
    {
        return true;
    }     
    else
    {
        return false;
    }
}


// ofir update exe3
int get_Game_Mode(char** args, int size)
{
    bool silent = false;
    
    if (size == 1)
        return NORMAL_MODE;

    try
    {
        for (int i = 1; i < size; i++)
        {
            if (is_equal_string("silent", args[i]))
                silent = true;
        }
        for (int i = 1; i < size; i++)
        {
            if (is_equal_string("load", args[i]))
            {
                if (silent)
                    return SILENT_LOAD_MODE;
                else
                    return LOAD_MODE;
            }
            else if (is_equal_string("save", args[i]))
                return SAVE_MODE;
        }
        throw "Wrong keys, please try again with one of the folowing: SAVE , LOAD , SILENT \n";       

    }
    catch (const char* error)
    {
        throw "Error reading arguments, please press any key to EXIT and try again \n";
    }
    return NORMAL_MODE;
}
bool is_equal_string(const string& base, const string& toCheck)
{
    if (base.size() == 0 || toCheck.size() == 0)
        throw "Error reading String!";

    if (base.size() != toCheck.size())
        return false;

    for (int i = 0; i < base.size(); i++)
    {
        if (isupper(base[i]))
        {
            if (toCheck[i] != tolower(base[i]) && toCheck[i] != base[i])
                return false;
        }
        else
        {
            if (toCheck[i] != toupper(base[i]) && toCheck[i] != base[i])
                return false;
        }
    }

    return true;
}
int get_string_size(const char* string)
{
    if (string == nullptr)
        return 0;

    char c = string[0];
    int count = 0;
    while (c != '\0')
    {
        count++;
        c = string[count];        
    }

    return count;
}
string delete_screen_from_fileName(const string& fileName)
{
    if (fileName.size() == 0)
        throw "Error reading File Name";

    string res = fileName;
    int size = res.size();

    if (!is_key_in_fileName(fileName, "screen"))
        return res;

    res.resize(size - 7);
    return res;
}
string convert_char_to_string(char* str)
{
    if (str == nullptr)
        throw "Error reading string";

    string res;
    int size = get_string_size(str);

    for (int i = 0; i < size; i++)
        res += str[i];
    return res;
}
string convert_int_to_string(int num)
{
    string res;

    if (num >= 100)
    {
        res += ('0' + num/100);
        num = num % 100;
        res += ('0' + num/10);
        num = num % 10;
        res += ('0' + num);
    }
    else if (num >= 10)
    {
        res += ('0' + num / 10);
        num = num % 10;
        res += ('0' + num);
    }
    else
    {
        res += ('0' + num);
    }
    
    return res;
}
int getDigitsOfNum(int num)
{
    int res = 1;
    while (num > 9)
    {
        num = num / 10;
        res++;
    }

    return res;
}

