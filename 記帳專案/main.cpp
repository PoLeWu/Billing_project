#include<fstream>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;



int main()
{
    while(true)
    {
        cout << "�w��ϥΰO�b�t��!" << endl;
        cout << "1.�n�J" << endl;
        cout << "2.���U" << endl;

        cout << "�п�J���O: ";
        int option;
        cin >> option;

        if(option == 1)
        {
            cout << endl;
            cout << "�n�J����" << endl;
            cout<<"�п�J�b��:";

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

                        cout << endl <<"�п�J�K�X(�Ѿl����" << failCount << "��): ";
                        string password;
                        cin >> password;

                        if(password == readPassword)
                        {
                            cout << "�n�J����" << endl;
                            break;
                        }
                        else
                        {

                             failCount--;
                             if(failCount == 0)
                             {
                                 cout << "��J���ƥΧ��A�N�ɦV����" << endl << endl;
                                 break;
                             }
                             else
                             {
                                 cout << "�K�X���~�A�Цb��J�@��!" << endl;
                             }
                        }
                    }

                    break;
                }
            }
            inputFile.close();

            if(accountSame==false)
            {
                cout<<"�d�L���b��!"<<endl << endl;
            }
        }
        else if(option == 2)
        {
            while(true)
            {
                cout << endl;
                cout << "�п�J���U���b��(�]�t�^��r���j�p�g,�Ʀr,����8~16): ";

                string account;
                cin >> account;

                int len = strlen(account.c_str());
                if(len >= 8 && len <= 16)//�b���ŦX����
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
                            cout << endl << "�b���w�Q�H�ϥ�!" << endl;
                            continue;
                        }


                        while(true)
                        {
                            cout << endl <<"�п�J���U���K�X(�]�t�^��r���j�p�g,�Ʀr,����8~16): ";
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
                                    cout << endl << "���U����" << endl << endl;

                                    //��b���K�X�g�J�ɮ�
                                    fstream file;
                                    file.open("account.txt", ios::app);
                                    string encodeString = account + ":" + password + "\n" ;
                                    file << encodeString;
                                    file.close();

                                    break;
                                }
                                else
                                {
                                    cout << endl << "�K�X�]�t���X�k�r��" << endl;
                                }
                            }
                            else
                            {
                                if(password_len < 8)
                                {
                                    cout << endl << "�K�X���׹L�u!" << endl;
                                }
                                else
                                {
                                    cout << endl << "�K�X���׹L��!" << endl;
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << endl << "�b���]�t���X�k�r��" << endl;
                    }

                }
                else
                {
                    if(len < 8)
                    {
                        cout << endl << "�b�����׹L�u!" << endl;
                    }
                    else
                    {
                        cout << endl << "�b�����׹L��!" << endl;
                    }
                }

            }
        }
    }
}

