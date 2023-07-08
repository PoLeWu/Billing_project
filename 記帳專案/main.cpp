#include<fstream>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;



int main()
{
    while(true)
    {
        cout << "歡迎使用記帳系統!" << endl;
        cout << "1.登入" << endl;
        cout << "2.註冊" << endl;

        cout << "請輸入指令: ";
        int option;
        cin >> option;

        if(option == 1)
        {
            cout << endl;
            cout << "登入頁面" << endl;
            cout<<"請輸入帳號:";

            string accountIn;
            cin>> accountIn;

            fstream inputFile;
            inputFile.open("account.txt", ios::in);
            bool accountSame = false;
            string s;

            while(inputFile >> s)
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
                    int failCount = 3;
                    while(true)
                    {

                        cout << endl <<"請輸入密碼(剩餘次數" << failCount << "次): ";
                        string password;
                        cin >> password;

                        if(password == readPassword)
                        {
                            cout << "登入完成" << endl;
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
                cout<<"查無此帳號!"<<endl << endl;
            }
        }
        else if(option == 2)
        {
            while(true)
            {
                cout << endl;
                cout << "請輸入註冊的帳號(包含英文字母大小寫,數字,長度8~16): ";

                string account;
                cin >> account;

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
                            cout << endl <<"請輸入註冊的密碼(包含英文字母大小寫,數字,長度8~16): ";
                            string password;
                            cin >> password;
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
                                    cout << endl << "註冊完成" << endl << endl;

                                    //把帳號密碼寫入檔案
                                    fstream file;
                                    file.open("account.txt", ios::app);
                                    string encodeString = account + ":" + password + "\n" ;
                                    file << encodeString;
                                    file.close();

                                    break;
                                }
                                else
                                {
                                    cout << endl << "密碼包含不合法字元" << endl;
                                }
                            }
                            else
                            {
                                if(password_len < 8)
                                {
                                    cout << endl << "密碼長度過短!" << endl;
                                }
                                else
                                {
                                    cout << endl << "密碼長度過長!" << endl;
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << endl << "帳號包含不合法字元" << endl;
                    }

                }
                else
                {
                    if(len < 8)
                    {
                        cout << endl << "帳號長度過短!" << endl;
                    }
                    else
                    {
                        cout << endl << "帳號長度過長!" << endl;
                    }
                }

            }
        }
    }
}

