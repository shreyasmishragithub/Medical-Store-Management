#include<iostream>
#include<string.h>
#include<vector>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include<windows.h>

using namespace std;

int i,n;

ifstream fin1,fin2;
ofstream fout1,fout2;
fstream fio;

class utility
{
public:
    void addnew();
    void disp();
    void refill();
    friend void remove();
    void withdraw();
};



class medicine:public utility
{
    char name[20],pass[10];
    float pr;
    int quant;

public:
    void get();
    void get2();
    void show();
    int stchk(char nm[30]);
    void withd(int qty);
    void refil(int qty);
} st;


void medicine::withd(int qty)
{
    if(quant>=qty)
    {
        quant-=qty;
        cout<<"\n\nStock updated.\n";
        cout<<"\n\nTotal price to be paid :  "<<pr<<"*"<<qty<<" = "<<pr*qty;
    }
    else{
        cout<<"\n\nInsufficient stock";
    }
    getch();
}


void medicine::refil(int qty)
{

    quant+=qty;
    cout<<"\n\nStock updated.";
    getch();
}


int medicine::stchk(char nm[30])
{
    if(strcmp(nm,name)==0)
        return 0;
    else
        return 1;

}


void medicine::get()
{
    cout<<"Enter the Name of the Medicine --->\t\t"<<setw(10);
    cin>>name;
    cout<<"Enter the Price of the Medicine --->\t\t"<<setw(10);
    cin>>pr;
    cout<<"Enter the quantity of the Medicine --->\t\t"<<setw(10);
    cin>>quant;
    vector<int>v;
    int w=0;
    for(int i=0;i<quant;i++){
        v.push_back(pr);
        w=w+v[i];
    }
    cout<<endl<<"Your total Medical Bill Is :"<<endl<<w<<"Rs";
}


void medicine::get2()
{
    cin>>name>>quant;
}


void medicine::show()
{
    cout.setf(ios::left,ios::adjustfield);
    cout.setf(ios::fixed,ios::floatfield);
    cout<<"\n\t*  "<<setw(15)<<name<<"\t\t      "<<setw(15)<<quant<<setprecision(2)<<"\t"<<"Rs. "<<pr<<"/-\n";
}


void utility::addnew()
{
    system("cls");
    disp();
    getch();
    system("cls");
    cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;
    if (n!=0)
    {
        int j,l,sum=0;
        fout1.open("shop.dat",ios::binary|ios::app);
        for(i=0; i<n; i++)
        {
            cout<<"\n\nEnter the details of item no. "<<i+1<<"\n\n";
            st.get();
            fout1.write((char*)&st,sizeof(st));
            cout<<"\n\nItem Updated!";
            cin.get();
        }
        cout<<"\n\nStock Updated!!";
        fout1.close();
        cin.get();
        system("cls");
        st.disp();
    }
    else
    {

        fout1.close();
        cin.get();
        system("cls");
        cout<<"\n\nNo items to be added";
    }
}


void utility::withdraw()
{
    system("cls");
    char temp[100];
    int qty;
    int count=0;
    long pos=0;
    st.disp();
    cout<<"\n\nEnter the product's name to be purchased : \n"<<endl;
    cin>>temp;
    cout<<"\n\nHow much quantity you want to buy :  \n"<<endl;
    cin>>qty;
    fio.open("shop.dat",ios::binary|ios::out|ios::in);
    while(fio)
    {
        pos=fio.tellp();
        fio.read((char*)&st,sizeof(st));
        if(st.stchk(temp)==0)
        {
            st.withd(qty);
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            count=1;
            break;
        }
    }
    if(count!=1)
    {
        cout<<"\n\n!!Record not found!!";
        getch();
    }
    fio.close();
    cin.get();
    system("cls");
    st.disp();
}


void utility::disp()
{
    int i=1;
    cout<<"\n================================================================================";
    cout<<"\n\n\t================\tTHE STOCK ITEMS ARE\t==============";
    cout<<"\n\n\t==============================================================\n";
    cout<<"\n\n       MEDICINE NAME\t\t      STOCK AVAILABLE\t      PRICE(per piece)";
    cout<<"\n\n     ======================================================================\n";
    fin1.open("shop.dat",ios::binary);
    while(!fin1.eof())
    {
        fin1.read((char*)&st,sizeof st);
        if(!fin1.eof())
        {
            if(fin1.tellg()<0)
            {
                i=0;
                break;
            }
            st.show();
        }
    }
    cout<<"\n\n     ======================================================================\n\n\n";
    if(i==0)
    {
        cout<<"\n\n\t\t\t!!Empty record room!!";
        getch();
    }
    fin1.close();
}


void utility::refill()
{
    system("cls");
    char temp[100];
    int qty;
    int i=0;
    long pos=0;
    st.disp();
    cout<<"\n\nEnter the products name \n"<<endl;
    cin>>temp;
    cout<<"\n\nEnter quantity: \n"<<endl;
    cin>>qty;
    fio.open("shop.dat",ios::binary|ios::out|ios::in);
    while(fio)
    {
        pos=fio.tellp();
        fio.read((char*)&st,sizeof st);
        if(st.stchk(temp)==0)
        {
            st.refil(qty);
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            i++;
            break;
        }
    }
    if(i!=1)
    {
        cout<<"\n\n!!Record not found!!";
        getch();
    }
    fio.close();
    system("cls");
    cin.get();
    st.disp();
    cin.get();
}


void remove()
{
    system("cls");
    int i=0;
    char temp[30];
    cout<<"\n\n\n\t\t\t\tDELETE RECORD";
    cout<<"\n\n================================================================================\n";
    cout<<"================================================================================\n\n";
    st.disp();
    cout<<"\n\nEnter the name of the product to be deleted :    ";
    cin>>temp;
    fout2.open("tmp.dat",ios::binary|ios::out);
    fin1.open("shop.dat",ios::binary|ios::in);
    while(!fin1.eof())
    {
        fin1.read((char*)&st,sizeof(st));
        if(!fin1.eof())
            if(st.stchk(temp)==0)
            {
                st.show();
                cout<<"\n\n\t\tRecord deleted";
                i++;
            }
            else
                fout2.write((char*)&st,sizeof(st));
    }
    if(i==0)
        cout<<"\n\n!!Record not found!!";
    fin1.close();
    fout2.close();
    remove("shop.dat");
    int res=rename("tmp.dat","shop.dat");
    if ( res == 0 )

        puts ( "File successfully renamed" );
    else
        perror( "Error renaming file" );
    getch();
}


int main()
{

    vector<int>v;
    int k=12;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    char pass[10],pass2[10];
    int i,j;
    cout<<"\n\n\n\n\n\t\t\t    |====================== WELCOME ======================|";
    cout<<"\n\n\n\n\n\t\t\t!==================== JANTA MEDICAL STORE ====================!";
    getch();
mainmenu:
    system("cls");
    k=10;
    SetConsoleTextAttribute(hConsole, k);
    cout<<"\n\n\n\n \t\t\t|============";
    _sleep(400);
    cout<<"  WELCOME ";
    _sleep(400);
    cout<<" TO ";
    _sleep(400);
    cout<<"MEDICAL";
    _sleep(400);
    cout<<"  STOREMANAGEMENT";
    _sleep(400);
    cout<<"============|"<<"\n";
    _sleep(400);
    getch();
    system("cls");
    for (int j = 0; j < 1; j++)
    {
        cout<<setw(18)<<"\r\t\t\t\t\t\tLoading";
        for (int i = 0; i <7; i++)
        {
            cout << ".";
            _sleep(100);


        }
    }
    //cout<<"\t===========================================";
    cout<<"\n\n\t\t\t   1. Dealer Menu\n\n\t\t\t   2. Customer Menu\n\n\t\t\t   3. Employee Menu\n\n\t\t\t   4. Exit";
    cout<<"\n\n\t=============================================================\n";
    cout<<"\n\nEnter Your Choice:";
    cin>>j;
    if(j==1)
    {
        int k=11;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
        system("cls");
        cout<<"\n\n\n\n\nEnter the password letter by letter: ";
        for(int z=0; z<6; z++)
        {
            pass[z]=getch();
            system("cls");
            cout<<"\n\n\n\n\n\n\nEnter the password letter by letter: ";
            for(i=1; i<=(z+1); i++)
            {
                cout<<"*";
            }
        }
        getch();
        if(strncmp(pass,"dealer",6)== 0)
        {
            cout<<"\n\n\n\n\n\n\t\t    Congrats!!  Access Granted!!\n\n";
            getch();
            system("cls");
dealermenu:
            system("cls");
            cout<<"================================================================================";
            cout<<"\n\n\t\t\t\t    DEALER MENU\n\n    1. Add new product\n    2. Display stock\n    3. Refill Stock\n    4. Remove an item\n    5. Home\n    6. Exit";
            cout<<"\n\n\n=================================END OF MENU====================================";
            cout<<"\n\n Enter your Choice :\t";
            cin>>i;
            if(i==1)
            {
                st.addnew();
                getch();
                goto dealermenu;
            }
            else if(i==2)
            {
                system("cls");
                st.disp();
                getch();
                goto dealermenu;
            }
            else if(i==3)
            {
                st.refill();
                goto dealermenu;
            }
            else if(i==4)
            {
                remove();
                getch();
                goto dealermenu;
            }
            else if(i=5)
            {
                goto mainmenu;
            }
            else
            {
                cout<<"\n\n\t\t\tThank You!";
                getch();
                exit(0);
            }
        }
        else
        {
            cout<<"\n\n\n\n\n\t\t\t\t WRONG PASSWORD!\n\n\t\t\t Only Authorized Personnel Allowed!\n\n";
            getch();
            exit(0);
        }
    }
    else if(j==2)
    {
        int k=13;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
custmenu:
        system("cls");
        cout<<"================================================================================";
        cout<<"\n\n\t\t\t\t    CUSTOMER MENU\n\n    1. Purchasing\n    2. Display stock\n    3. Home Screen\n    4. Exit";
        cout<<"\n\n\n=================================END OF MENU====================================";
        cout<<"\n\n Enter your Choice :\t";
        cin>>i;
        if (i==1)
        {
            st.withdraw();
            getch();
            goto custmenu;
        }
        else if(i==2)
        {
            system("cls");
            st.disp();
            getch();
            goto custmenu;
        }
        else if(i==3)
        {
            goto mainmenu;
        }
        else
        {
            cout<<"\n\n\t\t\tThank You!";
            getch();
            exit(0);
        }
    }
    else if(j==3)
    {
        int k=14;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
        system("cls");
        cout<<"\n\n\n\n\nEnter the password letter by letter: ";
        for(int z=0; z<3; z++)
        {
            pass[z]=getch();
            system("cls");
            cout<<"\n\n\n\n\n\n\nEnter the password letter by letter: ";
            for(i=1; i<=(z+1); i++)
            {
                cout<<"*";
            }
        }
        getch();
        if(strncmp(pass,"emp",3)== 0)
        {
            cout<<"\n\n\n\n\n\n\t\t    Congrats!!  Access Granted!!\n\n";
            getch();
            system("cls");
empmenu:
            system("cls");
            cout<<"================================================================================";
            cout<<"\n\n\t\t\t\t    EMPLOYEE MENU\n\n    1. Refill stock\n    2. Display Stock\n    3. Home Screen\n    4. Exit";
            cout<<"\n\n\n=================================END OF MENU====================================";
            cout<<"\n\n Enter your Choice :\t";
            cin>>i;
            if(i==1)
            {
                st.refill();
                goto empmenu;
            }
            if(i==2)
            {
                system("cls");
                st.disp();
                getch();
                goto empmenu;
            }
            else if(i==3)
            {
                goto mainmenu;
            }
            else
            {
                system("cls");
                cout<<"\n\n\n\t\t\tThank You!!";
                getch();
                exit(0);
            }
        }
        else
        {
            cout<<"\n\n\n\n\n\t\t\t\t WRONG PASSWORD!\n\n\t\t\t Only Authorized Personnel Allowed!\n\n";
            getch();
            exit(0);
        }
    }
    else if(j==4)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\t\t\t\tThank You!!";
        getch();
        exit(0);
    }
    else
    {
        /*cout<<"\n\nSorry!! Access Denied..\n\n";
        getch();*/
        goto mainmenu;
    }
    getch();
    }
