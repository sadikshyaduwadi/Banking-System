#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
using namespace std;
class Bank
{
    protected:
    int acc_no;
    char name[70];
    char type;
    double balance;
    double number_of_deposits;
    double number_of_withdrawls;
    double interest_rate;
    double monthly_service_charges;
    double annual_interest_rate;
    double service_charges;

    public:
    double monthly_interest_rate,monthly_interest,deposit,withdrawl;
    void create_account();
    void read_account();
    void update_account();
    void delete_account();
    void deposit_money();
    void withdraw_money();
    Bank (double b,double a)
    {
      balance = b;
      annual_interest_rate = a;
    }
    virtual void make_deposit(double d)
    {
      number_of_deposits = d;
      balance = balance + d;

    }
    virtual void makewithdrawal(double wd)
    {
      number_of_withdrawls = wd;
      balance = balance - wd;

    }
    virtual void calcInt()
    {
      monthly_interest_rate = (annual_interest_rate / 12);
      monthly_interest = balance * monthly_interest_rate;
      balance = balance + monthly_interest ;
    }
    virtual void monthlyProc()
    {
        
      balance = balance - monthly_service_charges;
      calcInt();
      number_of_withdrawls = 0;
      number_of_deposits = 0;
      monthly_service_charges = 0;
    
    }
    void display()
    {
      cout<<acc_no<<"\t"<<name<<"\t"<<endl;
    }

};
void Bank::create_account()
{
  ofstream fout;
  Bank b;
  cout<<"INSERT RECORD\n";
  fout.open("Accounts.dat",ios::app|ios::binary);
  cout<<"Enter the account no: ";
  cin>>b.acc_no;
  cout<<"Enter account holder's name: ";
  cin.ignore(); //used to clear buffer occupied by the previous variables.
  cin.getline(b.name,70);
  cout<<"\nEnter the type of account you want to create (C/S) : ";
  cin>>type;
  type=toupper(type);
  cout<<"\nEnter The Initial amount(>=100 for Saving and >=500 for current ) : ";
  cin>>deposit;
  fout.write((char*)&b,sizeof(b));
  fout.close();
  cout<<"\n\n\tYour account has been created successfully..";
  
  
}
void Bank::read_account()
{
  Bank b;
  file.open("Accounts.dat",ios::in);
  if(!file)
  {
   cout<<"ERROR IN OPENING FILE \n";
  }
  else
  {
    while(file.read((char*)&b,sizeof(b)))
    {
      b.display();
    }
  }
  file.close();
}
void searchForRecord()
{
  Bank b; 
  int isFound=0;
 
  cout<<"Enter the account no.: ";
  cin>>b.acc_no;


  file.open("Accounts.DAT",ios::in|ios::binary);
  if(!file)
  {
    cout<<"ERROR IN OPENING FILE \n";
  }
  while(file)
  {
    if(file.read((char*)&b,sizeof(b)))
    {
      if(acc_no == b.acc_no)
      {
        cout<<"RECORD FOUND\n";
        b.display();
        isFound=1;
        break;
      }
    }
  }
  if(isFound==0)
  {
    cout<<"Record not found!!!\n";
  }
  file.close();
}
void Bank::update_account()
{
  Bank b;
  int isFound=0;

  cout<<"Enter the account you want to udpate: ";
  cin>>b.acc_no;
  file.open("Accounts.dat", ios::out | ios::binary)
  if(!file)
  {
   cout<<"ERROR IN OPENING FILE \n";
  }
  else
  {
    while(file)
    {
      if(file.read(char*)&b,sizeof(b))
      {
        if(acc_no == b.acc_no)
        {
          cout<<"Enter the new account no: ";
          cin>>b.acc_no;
          cout<<"Enter account holder's new name: ";
          cin.ignore(); 
          cin.getline(b.name,70);
          cout<<"\nModify Type of Account : ";
	        cin>>type;
          type=toupper(type);
	        cout<<"\nModify Balance amount : ";
	        cin>>deposit;
          b.update();
          isFound=1;
          break;
        }
        
      }
    }
    if(isFound==0)
    {
      cout<<"Record not found!!\n";
    }
    file.close();
    cout<<"Your account has been updated successfully..";
  }
}
void Bank::delete_accounts()
{
  int acc_no;
  Bank b;
  ofstream fout("temp.dat",ios::binary);
  ifstream fin ("Accounts.dat",ios::binary);
  cout<<"\n Enter account number you want to delete :";
  cin>>acc_no;
  while(fin.read((char*)&b,sizeof(Bank)))
  {

    if(acc_no!=b.acc_no)
    {
      fout.write((char*)&b,sizeof(Bank));
    }
    fin.close();
    fout.close();
    remove("Accounts.dat");
    rename("temp.dat","Accounts.dat");
  }
  void Bank::deposit_money()
  {
    int d;
    cout<<"\nEnter amount you want to deposit:"<<endl;
    cin>>d;
    balance = balance + d;
    cout<<"\nYour total balance is: "<<balance<<endl;
  }
  void Bank::withdraw_money()
  {
    int w;
    cout<<"\nEnter amount you want to withdraw:"<<endl;
    cin>>withdraw;
    balance = balance - w;
    cout<<"\nYour total balance is: "<<balance<<endl;
  }
  void Bank::display_account()
  {
    
  }
};
class Saving_account()
{
  class Saving_acc : public Bank
  {
    private:
    bool status;
    bool ACTIVE;
    bool INACTIVE;
    public:
    Saving_acc(double b, double air) :Bank(b, air)

    {
        ACTIVE = true;
        INACTIVE = false;

        if(balance >= 25)
        {
            status = ACTIVE;
        }

        else
        {
            status = INACTIVE;
        }
    }
  }bool getStatus() { return status; }
  virtual void makeWithdrawal(double wd)
  {
    //check if status is active
    if(status == ACTIVE){
    Bank::makeWithdrawal(wd);
    if(balance < 25)
    status = INACTIVE;
  }
  else
  {
    //otherwise, print error message then return
    cout << fixed << setprecision(2);
    cout << "Withdrawal failed! "<<endl;
    cout << "Your Savings Account is inactive :\nBalance: $";
    cout << balance << endl;
  }
  virtual void makeDeposit(double d)
  {
    if(status == INACTIVE)
    {
      if(d + balance > 25)
      {
        Saving_acc::makeDeposit(d); 
      }
      else
      {
        cout<<"your bank account is still inactive."; //NAMILNA NI SAKXA
      }

    }
  }
  virtual void monthlyProc()
  {
    if(number_of_withdrawls > 4)
    {
     service_charges = service_charges + 1 *(number_of_withdrawls - 4);
     monthly_service_charges = monthly_service_charges + service_charges;
    } //baki xa
    Bank::monthlyProc();
    if(balance < 25)
    {
      status = INACTIVE;
    }
    return temp;
  }
};
class Checking_account()  
{
  class Checking_acc : public Bank
  {
    virtual void makeWithdrawal(double wd)
    {
      if(withdrawal > balance)
      {
        cout << "Withdrawal failed! \n";
        cout << "Your Checking Account is :\nBalance: $";
        cout << balance << endl;
        balance = balance - 15;
      }
      else
      {
        Bank::makeWithdrawal(wd);
      }
      
    }
    virtual void monthlyProc()
    {
      service_charges = serviceCharges + 5 + 0.1 * number_of_withdrawls;
      Bank::monthlyProc();
    }
  }
};
int main()
{
	Bank obj;
  int ch;
  char option;
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n1.) CREATE ACCOUNT";
		cout<<"\n2.) DEPOSIT AMOUNT";
		cout<<"\n3.) WITHDRAW AMOUNT";
    cout<<"\n4.) DISPLAY AMOUNT";
		cout<<"\n5.) UPDATE AN ACCOUNT";
    cout<<"\n6.) DELETE AN ACCOUNT";
		cout<<"\n7.) EXIT";
		cout<<"\n\n\tSelect Your Option (1-7) ";
		cin>>ch;
  do
	{
		system("cls");
		switch(ch)
		{
		case '1':
			cout<<"\n1.) Create Account:"<<endl;
      obj.create_account();
			break;
		case '2':
      cout<<"\n2.) Deposit Money:"<<endl;
			obj.deposit_money()
			break;
		case '3':
			cout<<"\n3.) Withdraw Money:"<<endl;
			obj.withdraw_money();
			break;
		case '4': 
			cout<<"\n4.) Display Account:"<<endl;
			obj.display_sp(num);
			break;
      case '5':
			cout<<"\n5.) Update AN ACCOUNT:"<<endl;
      obj.update_account();
			break;
      case '6':
			cout<<"\n6.) Delete AN ACCOUNT:"<<endl;
      obj.delete_account();
			break;
		 case '7':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\nPlease try again and choose correct option!"<<endl;
     break;
		}

    char option;
    cout<<"\nDou you want to continue? Press(Y/N) : "<<endl;
    option = getch();
     
     if((option == 'N')||(option == 'n'))
     {
       exit(0);
     }
     while((option == 'Y')||(option == 'y'))
     {
       return 0;
     }
  }
		
}



    
