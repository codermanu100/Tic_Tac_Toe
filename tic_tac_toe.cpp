// Program is for playing Tic Tac Toe game
#include<iostream>
#include<cstdlib>
#include <windows.h>
#include<bits/stdc++.h>

using namespace std;

static int num_print=0;  // for printing the positional tic tac toe
static int com_win=0;  // for counting the winning of the computer

// function for clearing the terminal screen
void clear()
{
    system("cls");
} // end of clear function

// function for showing that game is loading
void loading_the_game()
{
    cout<<"\t\t\t\t\t Loading\n";
    cout<<"\t\t\t\t\t";
    for(int i=0;i<9;i++)
    {
        cout<<(char)254;
        Sleep(200);
    }
    clear();
}  // end of function loading_the_game

// function for inputing enter to continue the program
void Continue()
{
    string s;
    cout<<"Press Enter to continue\n";
    fflush(stdin);
    getline(cin,s);
    clear();
} // end of continue function

// program to print the match
void print_match(char *m)
{
    int i,j,k=1;char t;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            t=*(m+i*3+j);
            if(num_print==0)
            cout<<" "<<k++<<" ";
            else if(t=='X'||t=='O')
            cout<<" "<<t<<" ";
            else
            cout<<"   ";
            if(j<=1)
            cout<<"|";
        }
        if(i<=1)
        cout<<endl<<"-----------"<<endl;
        else
        cout<<endl;
    }
    cout<<endl;
    num_print++;
} // end of print_match function

// function to calculate the result
int result(char *m)
{
    int i,j,c,d,e,f;
    if((*(m)=='X'&&*(m+4)=='X'&&*(m+8)=='X')||(*(m+2)=='X'&&*(m+4)=='X'&&*(m+6)=='X'))
    return 1;
    else if((*(m)=='O'&&*(m+4)=='O'&&*(m+8)=='O')||(*(m+2)=='O'&&*(m+4)=='O'&&*(m+6)=='O'))
    return 0;
    else
    {
        for(i=0;i<3;i++)
        {
            c=0;d=0;e=0;f=0;
            for(j=0;j<3;j++)
            {
                if(*(m+i*3+j)=='X')
                {
                    c++;
                    if (c==3)
                    return 1;                
                }
                if(*(m+j*3+i)=='X')
                {
                    d++;
                    if (d==3)
                    return 1;                
                }
                if(*(m+i*3+j)=='O')
                {
                    e++;
                    if (e==3)
                    return 0;                
                }
                if(*(m+j*3+i)=='O')
                {
                    f++;
                    if (f==3)
                    return 0;                
                }
            }
        }
    }
    return -1;
} // end of result function

// class for player
class player
{
    public:
    string name;
    int win;
    player()
    {
        name="";
    }
    player(string n)
    {
        name=n;
        win=0;
    }
}; // end of class player

// function for checking whether the position is entererd or not
int check_position(int position,int *pos,int c)
{
    int i;
    for(i=0;i<=c;i++)
    {
        if(*(pos+i)==position)
        return 1;
    }
    return 0;
} // end of check_position function

// play is the function for playing with computer
void play(player *p)
{
    srand((unsigned) time(NULL));
    num_print=0;
    char ch1,ch2;
    char *ch=new char[1];
    int random;
    cout<<p->name<<", Enter your choice O or X: ";
    a:
    cin>>ch;
    try
    {
        if((ch[0]=='X'||ch[0]=='O'||ch[0]=='x'||ch[0]=='o') && ch[1]=='\0')
        {
            ch1=ch[0];
            if(ch1=='x'||ch1=='o')
            ch1=(int)ch1-32;
            if(ch1=='X')
            {
                cout<<"Computer choice is O"<<endl;
                ch2='O';
            }
            else
            {
                cout<<"Computer choice is X"<<endl;
                ch2='X';
            }
        }
        else
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid choice"<<endl;
        Continue();
        cout<<p->name<<", Enter your choice O or X: ";
        goto a;
    }

    Continue();
    char *arr=new char[3*3];
    int *pos=new int[9];
    int position,c=0,k,check;
    loading_the_game();
    cout<<"Enter position according to this \n";
    print_match(arr);
    Continue();
    cout<<"Now, Let's start the Game \n";
    print_match(arr);

    while(c<9)
    {
        if(c%2==0)
        {
            cout<<p->name<<", Enter position: \n";
            co:
            cin>>ch;
            try
            {
                if(ch[0]>48 && ch[0]<=57 && ch[1]=='\0')
                {
                    position=((int)ch[0]-48);
                    cout<<endl;
                    position--;
                    if(c!=0)
                    check=check_position(position,pos,c);
                    if(check==1)
                    {
                        cout<<"Value is present at the entered position.\n";
                        Continue();
                        print_match(arr);
                        cout<<p->name<<", Enter another position: \n";
                        goto co;
                    }
                    *(arr+position)=ch1;
                    *(pos+c)=position;
                }      
                else
                throw ch; 
            }
            catch(char *d)
            {
                cout<<d<<" is not a valid position\n";
                Continue();
                print_match(arr);
                cout<<p->name<<", Enter valid position: \n";
                goto co;
            }
        }
        else
        {
            b:
            position=(0+(rand()%8));
            check=check_position(position,pos,c);
            if(check==1)
            goto b;
            else
            {
                cout<<"Computer has chose their turn\n";
                *(pos+c)=position;
                *(arr+position)=ch2;
                print_match(arr);
                Continue();
            }
        }

        if(c>=4)
        {
            k=result(arr);
            if(k==1)
            {
                clear();
                print_match(arr);
                if(ch1=='X')
                {
                    cout<<p->name<<" is the winner\n\n";
                    (p->win)++;
                    Continue();
                    return;
                }
                else if(ch2=='X')
                {
                    cout<<"Computer is the winner\n\n";
                    (com_win)++;
                    Continue();
                    return;
                }
            }
            else if(k==0)
            {
                clear();
                print_match(arr);
                if(ch1=='O')
                {
                    cout<<p->name<<" is the winner\n\n";
                    (p->win)++;
                    Continue();
                    return;
                }
                else if(ch2=='O')
                {
                    cout<<"Computer is the winner\n\n";
                    (com_win)++; 
                    Continue();
                    return;
                }
            }
        }
        clear();
        if(c%2!=0)
        print_match(arr);
        c++;
    } // end of while loop
    if(c==9)
    cout<<"Match draw"<<endl;
} // end of play function with computer

// play is the function for inputing the user value between two player
void play(player *p1,player *p2)
{
    num_print=0;
    char ch1,ch2;
    char *ch=new char[1];
    cout<<p1->name<<", Enter your choice O or X: ";
    a:
    cin>>ch;
    try
    {
        if((ch[0]=='X'||ch[0]=='O'||ch[0]=='x'||ch[0]=='o') && ch[1]=='\0')
        {
            ch1=ch[0];
            if(ch1=='x'||ch1=='o')
            ch1=(int)ch1-32;
            if(ch1=='X')
            {
                cout<<p2->name<<" choice is O"<<endl;
                ch2='O';
            }
            else
            {
                cout<<p2->name<<" choice is X"<<endl;
                ch2='X';
            }
        }
        else
        throw ch;
    }
    catch(char *exp)
    {
        cout<<exp<<" is not valid choice"<<endl;
        Continue();
        cout<<p1->name<<", Enter your choice O or X: ";
        goto a;
    }
    
    Continue();
    int *pos=new int[9];
    char *arr=new char[3*3];
    int position,c=0,k,check;
    loading_the_game();
    cout<<"Enter position according to this \n";
    print_match(arr);
    Continue();
    cout<<"Now, Let's start the Game \n";
    print_match(arr);

    while(c<9)
    {
        if(c%2==0)
        {
            cout<<p1->name<<", Enter position: \n";
            b:
            cin>>ch;
            try
            {
                if(ch[0]>48 && ch[0]<=57 && ch[1]=='\0')
                {
                    position=((int)ch[0]-48);
                    cout<<endl;
                    position--;
                    if(c!=0)
                    check=check_position(position,pos,c);
                    if(check==1)
                    {
                        cout<<"Value is present at the entered position.\n";
                        Continue();
                        print_match(arr);
                        cout<<p1->name<<", Enter another position: \n";
                        goto b;
                    }
                    *(arr+position)=ch1;
                    *(pos+c)=position;
                }      
                else
                throw ch; 
            }
            catch(char *ex)
            {
                cout<<ex<<" is not a valid position\n";
                Continue();
                print_match(arr);
                cout<<p1->name<<", Enter valid position: \n";
                goto b;
            }
        }
        else
        {
            cout<<p2->name<<", Enter position: \n";
            d:
            cin>>ch;
            try
            {
                if(ch[0]>48 && ch[0]<=57 && ch[1]=='\0')
                {
                    position=((int)ch[0]-48);
                    cout<<endl;
                    position--;
                    if(c!=0)
                    check=check_position(position,pos,c);
                    if(check==1)
                    {
                        cout<<"Value is present at the entered position.\n";
                        Continue();
                        print_match(arr);
                        cout<<p2->name<<", Enter another position: \n";
                        goto d;
                    }
                    *(arr+position)=ch2;
                    *(pos+c)=position;
                }      
                else
                throw ch; 
            }
            catch(char *e)
            {
                cout<<e<<" is not a valid position\n";
                Continue();
                print_match(arr);
                cout<<p2->name<<", Enter valid position: \n";
                goto d;
            }
        }

        if(c>=4)
        {
            k=result(arr);
            if(k==1)
            {
                clear();
                print_match(arr);
                if(ch1=='X')
                {
                    cout<<p1->name<<" is the winner\n\n";
                    (p1->win)++;
                    Continue();
                    return;
                }
                else if(ch2=='X')
                {
                    cout<<p2->name<<" is the winner\n\n";
                    (p2->win)++;
                    Continue();
                    return;
                }
            }
            else if(k==0)
            {
                clear();
                print_match(arr);
                if(ch1=='O')
                {
                    cout<<p1->name<<" is the winner\n\n";
                    (p1->win)++;
                    Continue();
                    return;
                }
                else if(ch2=='O')
                {
                    cout<<p2->name<<" is the winner\n\n";
                    (p2->win)++; 
                    Continue();
                    return;
                }
            }
        }
        clear();
        print_match(arr);
        c++;
    } // end of while loop
    if(c==9)
    cout<<"Match draw"<<endl;
}  // end of play function with person to person

// print_score is the Function to print the score
void print_score(player *p1,player *p2)
{
    cout<<"Score\n";
    cout<<p1->name<<": "<<(p1->win)<<endl;
    cout<<p2->name<<": "<<(p2->win)<<endl;
} 
void print_score(player *p)
{
    cout<<"Score\n";
    cout<<p->name<<": "<<(p->win)<<endl;
    cout<<"Computer: "<<(com_win)<<endl;
} 

void person_to_person()
{
    clear();
    char *ch=new char[1];
    string name;
    int n,i,choice;
    d:
    cout<<"Enter name of the player1: ";
    fflush(stdin);
    getline(cin,name);
    player p1(name);
    cout<<"Enter name of the player2: ";
    fflush(stdin);
    getline(cin,name);
    player p2(name);
    clear();
    rs:
    p1.win=0;
    p2.win=0;
    ss:
    cout<<"Number of chances you want to play \n";
    cout<<"Enter value between 1 - 9: ";
    cin>>ch;
    try
    {
        if(ch[0]>48 && ch[0]<=57 && ch[1]=='\0')
        {
            n=((int)ch[0]-48);
        }
        else
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid or not in the range 1 - 9 \n";
        Continue();
        cout<<"Enter valid, ";
        goto ss;
    }

    clear();
    for(i=1;i<=n;i++)
    {
        if(i==1&&n!=1)
        cout<<"\t\t\t 1st match \n";
        else if(i==2)
        cout<<"\t\t\t 2nd match \n";
        else if(i==3)
        cout<<"\t\t\t 3rd match \n";
        else if(i>3)
        cout<<"\t\t\t"<<i<<"th match \n";

        w:
        cout<<"Who will play first? \n1 -> "<<p1.name<<"\t";
        cout<<"2 -> "<<p2.name<<endl;
        cin>>ch;
        clear();
        try
        {
            if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
            {
                choice=((int)ch[0]-48);
                if(choice==1)
                play(&p1,&p2);
                else if(choice==2)
                play(&p2,&p1);
                else
                cout<<"";
            }
            else
            throw ch;
        }
        catch(char *c)
        {
            cout<<c<<" is not valid choice"<<endl;
            Continue();
            cout<<"Please, Enter a valid choice"<<endl;
            goto w;
        }   
        if(n!=1)
        {
            print_score(&p1,&p2);  // printing score of the match
            Continue();
        }
    } // end of for loop

    cout<<"Final Result\n";
    print_score(&p1,&p2);  // printing final score of the match
    if(p1.win>p2.win)
    cout<<"Congratulation, "<<p1.name<<" is the winner of this match\n"<<endl;
    else if(p1.win<p2.win)
    cout<<"Congratulation, "<<p2.name<<" is the winner of this match\n"<<endl;
    else if(p1.win==p2.win)
    cout<<"Match draw\n"<<endl;
    Continue();
    
    x:
    cout<<("Want to play more? \n1-> Yes \t 2 -> No \n");
    cin>>ch;
    clear();
    try
    {
        if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
        {
            choice=((int)ch[0]-48);
            if(choice==1)
            {
                y:
                cout<<"1 -> With same player \t 2 -> With different player \n";
                cin>>ch;
                clear();
                try
                {
                    if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
                    {
                        choice=((int)ch[0]-48);
                        if(choice==1)
                        {
                            z:
                            cout<<"1 -> Continue with previous score \t 2 -> Reset score \n";
                            cin>>ch;
                            clear();
                            try
                            {
                                if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
                                {
                                    choice=((int)ch[0]-48);
                                    if(choice==1)
                                    goto ss;
                                    else
                                    goto rs;
                                }
                            }
                            catch(char *c)
                            {
                                cout<<c<<" is not valid choice"<<endl;
                                Continue();
                                cout<<"Please, Enter a valid choice"<<endl;
                                goto z;
                            }   
                        }
                        else
                        goto d;
                    }
                    else
                    throw ch;
                }
                catch(char *c)
                {
                    cout<<c<<" is not valid choice"<<endl;
                    Continue();
                    cout<<"Please, Enter a valid choice"<<endl;
                    goto y;
                }   
            }
            else
            return;
        }
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid choice"<<endl;
        Continue();
        cout<<"Please, Enter a valid choice"<<endl;
        goto x;
    }   
} // end of person_to_person function

void computer()
{
    string name;
    char *ch=new char[1];
    int n,i,choice;
    clear();
    cout<<"Enter your name: ";
    fflush(stdin);
    getline(cin,name);
    clear();
    player p(name);
    rs:
    com_win=0;
    p.win=0;
    ss:
    cout<<"Number of chances you want to play \n";
    cout<<"Enter value between 1 - 9: ";
    cin>>ch;
    try
    {
        if(ch[0]>48 && ch[0]<=57 && ch[1]=='\0')
        {
            n=((int)ch[0]-48);
        }
        else
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid or not in the range 1 - 9 \n";
        Continue();
        cout<<"Enter valid, ";
        goto ss;
    }
    
    clear();
    for(i=1;i<=n;i++)
    {
        if(i==1&&n!=1)
        cout<<"\t\t\t 1st match \n";
        else if(i==2)
        cout<<"\t\t\t 2nd match \n";
        else if(i==3)
        cout<<"\t\t\t 3rd match \n";
        else if(i>3)
        cout<<"\t\t\t"<<i<<"th match \n";

        play(&p);
        if(n!=1)
        {
            print_score(&p);  // printing score of the match
            Continue();
        }
    } // end of for loop

    cout<<"Final Result\n";
    print_score(&p);  // printing final score of the match
    if(p.win>com_win)
    cout<<"Congratulation, "<<p.name<<" is the winner of this match\n"<<endl;
    else if(p.win<com_win)
    cout<<"Computer is the winner of this match\nBetter Luck next time \n"<<endl;
    else if(p.win==com_win)
    cout<<"Match draw\n"<<endl;
    Continue();

    y:
    cout<<("Want to play more? \n1-> Yes \t 2 -> No \n");
    cin>>ch;
    clear();
    try
    {
        if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
        {
            choice=((int)ch[0]-48);
            if(choice==1)
            {
                z:
                cout<<"1 -> Continue with previous score \t 2 -> Reset score \n";
                cin>>ch;
                clear();
                try
                {
                    if(ch[0]>48 && ch[0]<=50 && ch[1]=='\0')
                    {
                        choice=((int)ch[0]-48);
                        if(choice==1)
                        goto ss;
                        else
                        goto rs;
                    }
                    else
                    throw ch;
                }
                catch(char *c)
                {
                    cout<<c<<" is not valid choice"<<endl;
                    Continue();
                    cout<<"Please, Enter a valid choice"<<endl;
                    goto z;
                }   
            }
            else
            return;
        }
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid choice"<<endl;
        Continue();
        cout<<"Please, Enter a valid choice"<<endl;
        goto y;
    }   
} // end of computer function

int main()
{
    char *ch=new char[1];
    long long int choice;
    cout<<"\t\t\t Welcome to Tic Tac Toe game\n";
    k:
    cout<<"***************************************************************************\n";
    l:
    cout<<"1 -> With Computer \t 2 -> With Person \t 3 -> Exit\n";
    cin>>ch;
    try
    {
        if(ch[0]>48 && ch[0]<=51 && ch[1]=='\0')
        {
            choice=((int)ch[0]-48);
            if(choice==1)
            {
                computer();
                goto k;
            }
            else if(choice==2)
            {
                person_to_person();
                goto k;
            }
            else if(choice==3)
            {
                cout<<"\t\t\t Turning OFF Tic Tac Toe Game\n";
                cout<<"****************************************************************************"<<endl;
                system("pause");
                return 0;
            }
        }
        else
        throw ch;
    }
    catch(char *c)
    {
        cout<<c<<" is not valid choice"<<endl;
        Continue();
        cout<<"Please, Enter a valid choice"<<endl;
        goto l;
    }
} // end of main function