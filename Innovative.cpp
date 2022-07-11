//20BCE318 innovative assignment
//Hospital Management System

#include<bits/stdc++.h>
using namespace std;
static int cap[5]={0,0,0,0,0};      //cap[] is the number of patients in the queue of a doctor
static char doc_name[][50]={"Krunal Sharma","Ashok Shah","Sandhya Desai","Jayesh Shah","Gauri Mehta"};
static char pass[][50]={"Cardiologist","Neurologist","Physiotherapist","Skin Care","MBBS"};
static char pass_recep[]="abcd";       //password of receptionist
struct hospital
{
    int id;
    char patient[50],dname[50];
    int dno;                    //stores number of doctor for cancellation of appointment
    char gender;
    int age;
    char bg[5];
    long charge;
    hospital *next;
}*doc[4],*curr[4];
//doc[] is the pointer to first patient of a doctor
//curr[] is the pointer till where doctor has consulted

//function creates a node with the following details
hospital *create(char patient[],char g,int a,char bg[],int choice)
{
    hospital *np=new hospital();
    strcpy(np->patient,patient);
    np->gender=g;
    np->age=a;
    strcpy(np->bg,bg);
    np->charge=0;
    strcpy(np->dname,doc_name[choice-1]);
    np->dno=choice-1;
    np->next=NULL;
    return np;
}

//gives an appointment if available
void appointment(char patient[],char g,int a,char bg[],int choice)
{
        hospital *temp=doc[choice-1];
        while(temp!=NULL)
        {
            if(strcmp(temp->patient,patient)==0)
            {
                system("cls");
                cout<<"Patient already has an appointment\n";
                cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
                return;
            }
        }
        hospital *np=create(patient,g,a,bg,choice);
        if(doc[choice-1]==NULL)
        {
            ++cap[choice-1];
            doc[choice-1]=np;
            doc[choice-1]->id=cap[choice-1];
            cout<<"Appointment confirmed\n";
            cout<<"Your appointment number is "<<cap[choice-1]<<endl;
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
            curr[choice-1]=doc[choice-1];
            return;
        }
        temp=doc[choice-1];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        cap[choice-1]++;
        np->id=cap[choice-1];
        temp->next=np;
        curr[choice-1]=doc[choice-1];
        cout<<"Appointment confirmed\n";
        cout<<"Your appointment number is "<<cap[choice-1]<<endl;
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
}

void checkup(int choice)
{
    if(curr[choice]==NULL)
    {
        cout<<"You have no appointments left today\n";
        return;
    }
    cout<<"Patient Id:"<<curr[choice]->id<<endl;
    cout<<"Patient Name:"<<curr[choice]->patient<<endl;
    cout<<"Doctor Name:"<<curr[choice]->dname<<endl;
    cout<<"Age:"<<curr[choice]->age<<endl;
    cout<<"Gender:"<<curr[choice]->gender<<endl;
    cout<<"Blood Group:"<<curr[choice]->bg<<endl;
    cout<<"Enter charges of the patient:";
    cin>>curr[choice]->charge;
    curr[choice]=curr[choice]->next;
}

void display(int i)         //displays all the appointments of the day
{
    if(cap[i]==0)
        return;
    cout<<"|Id\t||\tPatient Name\t|\n";
    hospital *temp=doc[i];
    while(temp!=NULL)
    {
        cout<<temp->id<<"\t||\t"<<temp->patient<<endl;
        temp=temp->next;
    }
}

char bill(char name[])      //function to view and pay the bill of a patient
{
    system("cls");
    int found=0;
    int i;
    hospital *temp;
    for(i=0;i<5;++i)        //searches the patient in all the linked lists
    {
        temp=doc[i];
        while(temp!=NULL)
        {
            if(strcmp(name,temp->patient)==0)
            {
                found=1;
                break;
            }
            temp=temp->next;
        }
        if(found==1)
            break;
    }
   if(found==1 && temp->charge==0)  //if patient has not been consulted
    {
        cout<<"Check-up not done yet, please wait\n";
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
        return NULL;
    }

    else if(found==0)           //if patient not found
    {
        char ch;
        cout<<"Patient not confirmed an appointment\n";
        cout<<"Do you want to get an appointment(y/n):";    //asks if the patient wants to get an appointment
        cin>>ch;
        return ch;
    }

    cout<<"Id:"<<temp->id<<endl;
    cout<<"Name:"<<temp->patient<<endl;
    cout<<"Age:"<<temp->age<<endl;
    cout<<"Gender:"<<temp->gender<<endl;
    cout<<"Blood Group:"<<temp->bg<<endl;
    cout<<"Charges:"<<temp->charge<<endl;
    cout<<"Pay bill?(y/n):";
    char ch;
    cin>>ch;
    if(ch!='y')
    {
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
        return NULL;
    }
    long long card_num;
    char n[20];
    int cvv;
    char otp[5];

    //gets the following details for payment
    cout<<"Enter Card Number:";
    cin>>card_num;
    cout<<"Enter Card Holder's Name:";
    cin.ignore();
    cin.getline(n,20);
    cout<<"Enter CVV code:";
    cin>>cvv;
    cout<<"Enter OTP generated:";
    cin>>otp;
    cout<<"Payment succesfull\n\tStay Safe\t Stay Healthy\n";
    cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
    return NULL;
}

//function to cancel an appointment
char remove(char name[])
{
    system("cls");
    int found=0;
    int i;
    hospital *temp,*pred;
    for(i=0;i<5;++i)
    {
        temp=pred=doc[i];
        while(temp!=NULL)
        {
            if(strcmp(name,temp->patient)==0)
            {
                found=1;
                cap[i]--;
                cout<<"Patient's appointment has been cancelled\n";
                if(temp->id==1)
                {
                    doc[i]=temp->next;
                    delete temp;
                    if(doc[i]==NULL)
                    {
                        return NULL;
                    }
                    pred=doc[i];
                    temp=pred->next;
                    continue;
                }
                else
                {
                    pred->next=temp->next;
                    delete temp;
                    temp=pred->next;
                    continue;
                }
            }
            if(found==1)
            {
                temp->id--;
            }
            pred=temp;
            temp=temp->next;
        }
        if(found==1)
            break;
    }

    if(found==0)
    {
        char ch;
        cout<<"Patient has no confirmed appointment\n";
        cout<<"Do you want to get an appointment(y/n):";
        cin>>ch;
        return ch;
    }
    return NULL;
}

int main()
{
    int logch,ch;
    char name[50],p[50],bg[5];
    char gen;
    int age;

    label:          //asks user how he wants to login
    cout<<"1.Doctor\n";
    cout<<"2.Patient\n";
    cout<<"3.Receptionist\n";
    cout<<"4.exit\n";
    cout<<"\tLog in as:";
    cin>>logch;

    if(logch==1)        //for doctor
    {
        system("cls");
        cout<<"To log-in\n";
        cout<<"\tEnter Name:";
        cin.ignore();
        cin.getline(name,49);
        cout<<"\tEnter Password:";
        cin.getline(p,49);
        int i;
        for(i=0;i<5;++i)
        {
            //checks name and password of the doctors to login
            if(!strcmp(doc_name[i],name) && !strcmp(pass[i],p))
            {
                system("cls");
                cout<<"You are logged in Dr."<<name<<"\n";
                cout<<cap[i]<<" patients have their appointments today\n";
                display(i);
                break;
            }
        }
        if(i==5)
        {
            cout<<"Sorry either your name or your password is wrong\n";
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
            goto label;
        }
        else if(cap[i]==0)      //if no appointments
        {
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
            goto label;
        }

        char check='y';
        while(check=='y'||check=='Y')
        {
            checkup(i);
            cout<<"Do you want to continue checking(y,n):";
            cin>>check;
            system("cls");
        }
        cout<<"Logged-out\n";
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
        goto label;
    }

    else if(logch==2)       //for patient
    {
        system("cls");
        label2:
        cout<<"1.Cardiologist - Dr.Krunal Sharma\n";
        cout<<"2.Neurologist - Dr.Ashok Shah\n";
        cout<<"3.Physiologist - Dr.Sandhya Desai\n";
        cout<<"4.Skin Care Specialist - Dr.Jayesh Shah\n";
        cout<<"5.MBBS - Dr.Gauri Mehta\n";
        cout<<"6.Back:\n";
        cout<<"\tWhich doctor do you want to consult:";
        cin>>ch;
        if(ch==6)
        {
            cout<<endl;
            goto label;
        }
        else if(ch<=0 && ch>5)
        {
            system("cls");
            cout<<"You entered a wrong number\n";
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
            goto label2;
        }
        if(cap[ch-1]>20)
        {
            system("cls");
            cout<<"Sorry no more appointments available for the day \n\tHave a Good Day\n";
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
            goto label2;
        }
        cout<<"Enter the details for Registration:\n";
        cout<<"\tEnter your name:";
        cin.ignore();
        cin.getline(name,20);
        cout<<"\tEnter your gender(m/f):";
        cin>>gen;
        cout<<"\tEnter your age:";
        cin>>age;
        cout<<"\tEnter your Blood group:";
        cin>>bg;
        appointment(name,gen,age,bg,ch);
        goto label;
    }

    else if(logch==3)       //for receptionist
    {
        cout<<"To log-in as receptionist\n\tEnter password:";
        cin.ignore();
        cin>>p;
        if(strcmp(p,pass_recep)!=0)
        {
            cout<<"You entered wrong password\n";
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
            goto label;
        }
        system("cls");
        label3:
        cout<<"Menu:\n";
            cout<<"\t1. Today's appointments\n";
            cout<<"\t2. Bill Payment\n";
            cout<<"\t3. Cancel an appointment\n";
            cout<<"\t4. log-out\n";
            cout<<"Enter your choice:";
            cin>>ch;
            if(ch==1)
            {
                cout<<"\n1.Cardiologist - Dr.Krunal Sharma\n";
                cout<<"2.Neurologist - Dr.Ashok Shah\n";
                cout<<"3.Physiologist - Dr.Sandhya Desai\n";
                cout<<"4.Skin Care Specialist - Dr.Jayesh Shah\n";
                cout<<"5.MBBS - Dr.Gauri Mehta\n";
                cout<<"\tWhich doctors appointments?\n\t->";
                int choice;
                cin>>choice;
                if(cap[choice-1]==0)
                {
                    system("cls");
                    cout<<"\tNo appointments\n\n";
                    goto label3;
                }
                display(choice-1);
                goto label3;
            }

            else if(ch==2)
            {
                cout<<"Enter your name:";
                cin.ignore();
                cin.getline(name,20);
                char c=bill(name);
                if(c=='y' || c=='Y')
                {
                    cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
                    goto label2;
                }
                goto label3;
            }

            else if(ch==3)
            {
                cout<<"Enter name of the patient:";
                cin.ignore();
                char n[20];
                cin.getline(n,20);
                char c=remove(n);
                if(c=='y' || c=='Y')
                {
                    cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
                    goto label2;
                }
                else
                {
                    cout<<endl;
                    goto label3;
                }
            }
            else if(ch==4)
            {
                system("cls");
                goto label;
            }
            else
            {
                system("cls");
                 cout<<"Wrong choice\n";
                 goto label3;
            }

    }
    else if(logch==4)
        exit(0);
    else
    {
        system("cls");
        cout<<"Wrong choice\n";
        goto label;
    }
    return 0;
}






