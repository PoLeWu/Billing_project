#include<fstream>
#include<iostream>
#include<string>
#include<string.h>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;



int dateCompare(string a, string b) // , -1 : a < b , 0: a = b , 1: a > b
{
    int aYear,aMonth,aDay;
    int bYear,bMonth,bDay;


    int lenA = a.length();
    int lenB = b.length();


    int index;
    string buffer = "";


    for(int i = 0; i < lenA; i++)
    {
        if(a[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += a[i];
        }
    }
    aYear = stoi(buffer);
    buffer = "";


    //===============================


    for(int i = index; i < lenA; i++)
    {
        if(a[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += a[i];
        }
    }
    aMonth = stoi(buffer);
    buffer = "";


    //===============================


    for(int i = index; i < lenA; i++)
    {
        buffer += a[i];
    }
    aDay = stoi(buffer);
    buffer = "";


    //===========================================================================================


    for(int i = 0; i < lenB; i++)
    {
        if(b[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += b[i];
        }
    }
    bYear = stoi(buffer);
    buffer = "";


    //===============================


    for(int i = index; i < lenB; i++)
    {
        if(b[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += b[i];
        }
    }
    bMonth = stoi(buffer);
    buffer = "";


    //===============================


    for(int i = index; i < lenB; i++)
    {
        buffer += b[i];
    }
    bDay = stoi(buffer);
    buffer = "";


    //===============================


    if(aYear > bYear)
    {
        return 1;
    }
    else if(aYear < bYear)
    {
        return -1;
    }
    else if(aYear == bYear)
    {
        if(aMonth > bMonth)
        {
            return 1;
        }
        else if(aMonth < bMonth)
        {
            return -1;
        }
        else if(aMonth == bMonth)
        {
            if(aDay > bDay)
            {
                return 1;
            }
            else if(aDay < bDay)
            {
                return -1;
            }
            else if(aDay == bDay)
            {
                return 0;
            }
        }
    }

    //unreachable
    return 0;
}



class Log
{
private:
    string timeStamp;
    int value;
    string description;
public:
    Log(string time, int v, string des)
    {
        timeStamp = time;
        value = v;
        description = des;
    }
    int getValue()
    {
        return value;
    }
    string getTimeStamp()
    {
        return timeStamp;
    }
    void printInfo()
    {
        cout << timeStamp << "," << value << "," << description << endl;
    }
    void writeInfo(fstream &database)
    {
        database << timeStamp << "," << value << "," << description << endl;
    }
};

bool logCompare(Log a, Log b) // > return true， <= return false
{
    int compareResult = dateCompare(a.getTimeStamp(), b.getTimeStamp());
    if(compareResult == -1)
    {
        return false;
    }
    else if(compareResult == 1)
    {
        return true;
    }
    else if(compareResult == 0)
    {
        return a.getValue() > b.getValue();
    }

    //unreachable
    return false;
}


bool logCompare2(Log a, Log b)  // >= return true， < return false
{
    int compareResult = dateCompare(a.getTimeStamp(), b.getTimeStamp());
    if(compareResult == -1)
    {
        return false;
    }
    else if(compareResult == 1)
    {
        return true;
    }
    else if(compareResult == 0)
    {
        return a.getValue() >= b.getValue();
    }

    //unreachable
    return false;
}


class Account
{
private:
    string account;
    vector<Log> accountLog;
    int balance;
public:
    Account(string accountName, int b)
    {
        account = accountName;
        balance = b;
        accountLog.clear();
    }
    Account()
    {

    }
    void addLog(string time, int val, string des)
    {
        accountLog.push_back(Log(time,val,des));
    }
    void insertNewLog(Log newLog)
    {
        balance += newLog.getValue();
        accountLog.push_back(newLog); //讓他有位置

        int j = accountLog.size()-2;   //現在看到第幾個
        while (j >= 0 && logCompare(accountLog[j], newLog)) //如果前面的比較大，而且有數字


        {
            accountLog[j+1] = accountLog[j];
            j--;
        }
        accountLog[j+1] = newLog; //現在這個並沒有比較大，因此填入到上一個的位置


    }
    string getName()
    {
        return account;
    }
    void print()
    {
        cout << account << " : " << balance << endl << endl;
        for(int i = 0; i < accountLog.size(); i++)
        {
            accountLog[i].printInfo();
        }
    }
    void writeFile(fstream &database)
    {
        database << account << ":" << balance << endl;
        for(int i = 0; i < accountLog.size(); i++)
        {
            accountLog[i].writeInfo(database);
        }
        database << "=====" << endl;
    }

    int myLowerBound(Log myLog)
    {
        int l = 0;
        int r = accountLog.size()-1;

        while(l < r)
        {
            int mid = (l+r) / 2;

            if(logCompare2(accountLog[mid],myLog) == true) //  mid >= myLog
            {
                r = mid;
            }
            else // mid < myLog
            {
                l = mid+1;
            }
        }

        if(l == accountLog.size()-1)
        {
            if(logCompare(myLog,accountLog[accountLog.size()-1]))
            {
                l++;
            }
        }

        return l ;
    }

    int myUpperBound(Log myLog)
    {
        int l = 0;
        int r = accountLog.size()-1;

        while(l < r)
        {
            int mid = (l+r) / 2;

            if(logCompare(accountLog[mid],myLog) == true) //  mid > myLog
            {
                r = mid;
            }
            else // mid <= myLog
            {
                l = mid+1;
            }
        }

        if(l == accountLog.size()-1)
        {
            if(logCompare(myLog,accountLog[accountLog.size()-1]))
            {
                l++;
            }
        }

        return l ;
    }

    void searchLog(string startDate, string endDate, int startVal, int endVal)
    {
        Log startLog(startDate,startVal,"");
        Log endLog(endDate,endVal,"");

        int startIndex = myLowerBound(startLog);

        int endIndex = myUpperBound(endLog);

        cout << "查詢日期於 " << startDate << " ~ " << endDate << " ，金額於 " << startVal << " ~ " << endVal << " 的帳目：" << endl << endl;

        for(int i = startIndex; i < endIndex; i++)
        {
            accountLog[i].printInfo();
        }

        cout << endl << "請按任意鍵繼續......";
        char input = _getch();

        system("cls");

    }


};





bool isLeap(int year)
{
    if(year % 4 != 0)
    {
        return false;
    }
    if(year % 4 == 0 && year % 100 != 0)
    {
        return true;
    }
    if(year % 100 == 0 && year % 400 != 0)
    {
        return false;
    }
    if(year % 400 == 0)
    {
        return true;
    }


    //unreachable
    return true;
}


bool checkDate(string date)
{
    int len = date.length();
    int slashCount = 0;
    for(int i = 0; i < len; i++)
    {
        if(date[i] >= '0' && date[i] <= '9')
        {


        }
        else if(date[i] == '/')
        {
            slashCount++;
        }
        else
        {
            return false;
        }
    }


    if(slashCount != 2)
    {
        return false;
    }


    string buffer = "";


    int year,month,day;
    int index = 0;


    for(int i = 0; i < len; i++)
    {
        if(date[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += date[i];
        }
    }


    try
    {
        year = stoi(buffer);
    }
    catch (exception &e)
    {
        return false;
    }


    if(!(year > 0))
    {
        return false;
    }


    buffer = "";


    for(int i = index; i < len; i++)
    {
        if(date[i] == '/')
        {
            index = i+1;
            break;
        }
        else
        {
            buffer += date[i];
        }
    }


    try
    {
        month = stoi(buffer);
    }
    catch (exception &e)
    {
        return false;
    }




    if(!(month >= 1 && month <= 12))
    {
        return false;
    }




    buffer = "";


    for(int i = index; i < len; i++)
    {
        buffer += date[i];
    }


    try
    {
        day = stoi(buffer);
    }
    catch (exception &e)
    {
        return false;
    }


    int correctDay[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};


    if(isLeap(year) == true)
    {
        correctDay[2] = 29;
    }


    if(!(day <= correctDay[month]))
    {
        return false;
    }


    return true;


}




int main()
{

    string loginAccount = "";//登入帳號

    while(true)
    {
        cout << "歡迎使用記帳系統!" << endl;
        cout << "1.登入" << endl;
        cout << "2.註冊" << endl;
        cout << "3.離開" << endl;


        cout << "請輸入指令: ";
        int option;
        cin >> option;


        system("cls");


        if(option == 1)
        {
            cout << "登入頁面" << endl;
            cout<<"請輸入帳號:";


            string accountIn;
            cin>> accountIn;


            fstream inputFile;
            inputFile.open("account.txt", ios::in);
            bool accountSame = false;
            string s;


            while(inputFile >> s) //一行一行讀取account.txt並檢查是否有對應的帳號
            {
                string readAccount="";
                string readPassword="";
                bool seeAccount = false;
                int len=strlen(s.c_str());
                for(int i=0; i<len; i++)//split the account
                {
                    if(seeAccount == false)
                    {
                        if(s[i] == ':')
                        {
                            seeAccount = true;
                            continue;
                        }
                        readAccount += s[i];
                    }
                    else
                    {
                        readPassword += s[i];
                    }
                }




                if(readAccount==accountIn)
                {
                    accountSame=true;
                }




                if(accountSame==true)
                {
                    system("cls");
                    int failCount = 3;
                    while(true)
                    {


                        cout << "請輸入密碼(剩餘次數" << failCount << "次): ";
                        string password;
                        cin >> password;


                        system("cls");


                        if(password == readPassword)
                        {
                            cout << "登入完成" << endl << endl;
                            loginAccount = accountIn;
                            break;
                        }
                        else
                        {


                            failCount--;
                            if(failCount == 0)
                            {
                                cout << "輸入次數用完，將導向首頁" << endl << endl;
                                break;
                            }
                            else
                            {
                                cout << "密碼錯誤，請在輸入一次!" << endl;
                            }
                        }
                    }


                    break;
                }
            }
            inputFile.close();


            if(accountSame==false)
            {
                system("cls");
                cout<<"查無此帳號!"<<endl << endl;
            }
        }
        else if(option == 2)
        {
            while(true)
            {
                cout << "請輸入註冊的帳號(包含英文字母大小寫,數字,長度8~16): ";


                string account;
                cin >> account;


                system("cls");


                int len = strlen(account.c_str());
                if(len >= 8 && len <= 16)//帳號符合長度
                {
                    bool allRight = true;
                    for(int i = 0; i < len; i++)
                    {
                        if((account[i] >= 'a' && account[i] <= 'z') || (account[i] >= 'A' && account[i] <= 'Z') || (account[i] >= '0' && account[i] <= '9'))
                        {


                        }
                        else
                        {
                            allRight = false;
                            break;
                        }
                    }




                    if(allRight == true)
                    {
                        fstream inputFile;
                        inputFile.open("account.txt", ios::in);
                        bool nothingSame = true;
                        string s;


                        while(inputFile >> s)
                        {
                            int tempLen = strlen(s.c_str());
                            string readAccount = "";
                            for(int i = 0; i < tempLen; i++)
                            {
                                if(s[i] == ':')
                                {
                                    for(int j = 0; j < i; j++)
                                    {
                                        readAccount += s[j];
                                    }
                                    break;
                                }
                            }
                            if(readAccount == account)
                            {
                                nothingSame = false;
                                break;
                            }
                        }
                        inputFile.close();


                        if(nothingSame == false)
                        {
                            cout << endl << "帳號已被人使用!" << endl;
                            continue;
                        }




                        while(true)
                        {
                            cout <<"請輸入註冊的密碼(包含英文字母大小寫,數字,長度8~16): ";
                            string password;
                            cin >> password;
                            system("cls");
                            int password_len = strlen(password.c_str());
                            if(password_len >= 8 && password_len <= 16)
                            {
                                bool password_allRight = true;
                                for(int i = 0; i < password_len; i++)
                                {
                                    if((password[i] >= 'a' && password[i] <= 'z') || (password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= '0' && password[i] <= '9'))
                                    {


                                    }
                                    else
                                    {
                                        password_allRight = false;
                                        break;
                                    }
                                }


                                if(password_allRight == true)
                                {
                                    cout << "註冊完成" << endl << endl;


                                    //把帳號密碼寫入檔案
                                    fstream file;
                                    file.open("account.txt", ios::app);
                                    string encodeString = account + ":" + password + "\n" ;
                                    file << encodeString;
                                    file.close();


                                    //database.txt
                                    //新增一個人的資料進到database.txt中
                                    fstream databaseFile;
                                    databaseFile.open("database.txt", ios::app);
                                    databaseFile << account << ":" << 0 << endl;
                                    databaseFile << "=====" << endl;
                                    databaseFile.close();


                                    break;
                                }
                                else
                                {
                                    cout  << "密碼包含不合法字元" << endl <<endl;
                                }
                            }
                            else
                            {
                                if(password_len < 8)
                                {
                                    cout << "密碼長度過短!" << endl << endl;
                                }
                                else
                                {
                                    cout << "密碼長度過長!" << endl << endl;
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << "帳號包含不合法字元" << endl << endl;
                    }


                }
                else
                {
                    if(len < 8)
                    {
                        cout << "帳號長度過短!" << endl << endl;
                    }
                    else
                    {
                        cout << "帳號長度過長!" << endl << endl;
                    }
                }


            }
        }
        else if(option == 3)
        {
            cout << "謝謝使用" << endl;
            break;
        }


        if(loginAccount != "") //用loginAccount是否 = 空字串來判斷有沒有登入
        {
            unordered_map<string, Account> db;


            //讀取database，全部都要讀下來
            fstream database;
            database.open("database.txt", ios::in);


            string s;
            bool firstLine = true;
            Account user;


            while(getline(database,s))
            {
                if(s == "=====") //一個人的資料結束
                {
                    db[user.getName()] = user;
                    firstLine = true;
                }
                else
                {
                    if(firstLine == true)
                    {
                        string accountNameBuffer = "";
                        string balanceBuffer = "";
                        int splitPoint;
                        for(int i = 0; i < s.length(); i++)
                        {
                            if(s[i] == ':')
                            {
                                splitPoint = i;
                                break;
                            }
                            else
                            {
                                accountNameBuffer += s[i];
                            }
                        }
                        for(int i = splitPoint+1; i < s.length(); i++)
                        {
                            balanceBuffer += s[i];
                        }
                        int balanceValue = stoi(balanceBuffer);


                        user = Account(accountNameBuffer,balanceValue); //建立一個Acoount的物件，把accountNameBuffer與balanceValue傳進去


                        firstLine = false;
                    }
                    else //讀紀錄
                    {
                        int splitPoint_1;
                        int splitPoint_2;
                        string timeBuffer = "";
                        string valueBuffer = "";
                        string desBuffer = "";
                        int valueINT;
                        for(int i = 0; i < s.length(); i++)
                        {
                            if(s[i] == ',')
                            {
                                splitPoint_1 = i;
                                break;
                            }
                            else
                            {
                                timeBuffer += s[i];
                            }
                        }
                        for(int i = splitPoint_1+1; i < s.length(); i++)
                        {
                            if(s[i] == ',')
                            {
                                splitPoint_2 = i;
                                break;
                            }
                            else
                            {
                                valueBuffer += s[i];
                            }
                        }
                        for(int i = splitPoint_2+1; i < s.length(); i++)
                        {
                            desBuffer += s[i];
                        }


                        valueINT = stoi(valueBuffer);


                        user.addLog(timeBuffer,valueINT,desBuffer);


                    }
                }
            }


            database.close();




            /*
            unordered_map<string,Account>::iterator iter;
            for(iter = db.begin(); iter != db.end(); iter++)
            {
                (iter->second).print();
            }
            */



            while(true) //登入後的動作
            {
                cout << "使用者 ： " << loginAccount << endl;
                cout << "1. 查帳" << endl;
                cout << "2. 新增帳目" << endl;
                cout << "3. 登出" << endl;


                int action;
                cin >> action;


                system("cls");


                if(action == 1)
                {
                    cout << "1. 查詢所有帳目" << endl;
                    cout << "2. 依照日期及金額查詢" << endl;


                    int checkMode;
                    cin >> checkMode;


                    system("cls");


                    if(checkMode == 1)
                    {
                        db[loginAccount].print();
                        cout << endl << "請按任意鍵繼續......";
                        char input = _getch();
                        system("cls");
                    }
                    else
                    {
                        string startDate, endDate;
                        int startValue, endValue;


                        while(true)
                        {
                            cout << "請輸入查詢起始日期(yyyy/mm/dd)：";
                            cin >> startDate;
                            system("cls");
                            if(checkDate(startDate) == true)
                            {
                                break;
                            }
                            else
                            {
                                cout << "輸入日期錯誤，請再試一次！(yyyy/mm/dd)" << endl << endl;
                            }
                        }


                        while(true)
                        {
                            cout << "請輸入查詢結束日期：(yyyy/mm/dd)";
                            cin >> endDate;
                            system("cls");
                            if(checkDate(endDate) ==  false)
                            {
                                cout << "輸入日期錯誤，請再試一次！(yyyy/mm/dd)" << endl << endl;
                                continue;
                            }
                            if(dateCompare(endDate,startDate) == -1)


                            {
                                cout << "結束日期必須在起始日期之後，請再試一次！(yyyy/mm/dd)" << endl << endl;
                                continue;
                            }
                            break;


                        }


                        cout << "請輸入查詢最低金額：";
                        cin >> startValue;
                        system("cls");


                        while(true)
                        {
                            cout << "請輸入查詢最高金額：";
                            cin >> endValue;
                            system("cls");


                            if(endValue >= startValue)
                            {
                                break;
                            }
                            else
                            {
                                cout << "最高金額必須 >= 最低金額！" << endl << endl;
                            }
                        }

                        db[loginAccount].searchLog(startDate,endDate,startValue,endValue);


                    }


                }
                else if(action == 2)
                {
                    string date;
                    int newValue;
                    string newDescription;


                    //輸入日期
                    while(true)
                    {
                        cout << "請輸入日期：(yyyy/mm/dd)" << endl;
                        cin >> date;


                        system("cls");


                        if(checkDate(date) == true)
                        {
                            break;
                        }
                        else
                        {
                            cout << "輸入錯誤，請再輸入一次(yyyy/mm/dd)" << endl;
                        }
                    }
                    //輸入金額
                    cout << "請輸入金額：" << endl;
                    cin >> newValue;
                    system("cls");


                    //輸入說明
                    cout << "請輸入帳目說明(英文)：" << endl;
                    getline(cin,newDescription);
                    getline(cin,newDescription);
                    system("cls");


                    Log newLog(date,newValue,newDescription);


                    db[loginAccount].insertNewLog(newLog);


                    /*
                    unordered_map<string,Account>::iterator iter;
                    for(iter = db.begin(); iter != db.end(); iter++)
                    {
                        (iter->second).print();
                    }
                    */




                    cout << "新增帳目完成！" << endl << endl;




                }
                else if(action == 3) //登出的時候，會重新把資料寫到database.txt
                {
                    fstream database;
                    database.open("database.txt", ios::out);
                    unordered_map<string,Account>::iterator iter;
                    for(iter = db.begin(); iter != db.end(); iter++)
                    {
                        (iter->second).writeFile(database);
                    }
                    loginAccount = "";
                    break;
                }


            }
        }
    }




}
