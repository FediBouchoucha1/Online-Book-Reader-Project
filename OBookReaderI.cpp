#include<bits/stdc++.h>
using namespace std;

class book{
private:
    int ISBN;
    string title;
    string authorName;
    int NPages;
    vector<string>content;
public:
    book(){}
    book(int ISBN, string title,string at,int np, vector<string>&c){
        setISBN(ISBN);
        settitle(title);
        setauthorName(at);
        setNpages(np);
        setContent(c);
    }

    void setISBN(int x)
    {
        this->ISBN=x;
    }
    const int& getISBN()const{
        return this->ISBN;
    }

    void settitle(string n)
    {
        this->title=n;
    }

    const string& getTitle()const
    {
        return this->title;
    }

    void setauthorName(string n)
    {
        this->authorName=n;
    }

    const string& getAname()const
    {
        return this->authorName;
    }

    void setNpages(int n)
    {
        this->NPages=n;
    }
    const int& getNpages()const{

        return this->NPages;
    }
    void setContent(vector<string> &v)
    {
        this->content=v;
    }

    const vector<string> getContent()
    {
        return this->content;
    }
};
class bookHistory{
private:
    book currentBook;
    int pageNumber;
    string date;
public:
    bookHistory(){}

    bookHistory(book booktoadd){
        currentBook=booktoadd;
        pageNumber=1;
        time_t now = time(0);
        date = ctime(&now);
    }

    void ReadCurrentPage()
    {
        vector<string> v=this->currentBook.getContent();
        cout<<"Current Page: "<<this->pageNumber<<"/"<<v.size()<<endl;
        cout<<v[pageNumber-1]<<endl;
    }


    void nextPage()
    {
        time_t now = time(0);
        this->date = ctime(&now);
        if(pageNumber==currentBook.getNpages())
        {
            this->ReadCurrentPage();
            return;
        }
        this->pageNumber+=1;
        this->ReadCurrentPage();
    }
    void PreviousPage()
    {
        time_t now = time(0);
        this->date = ctime(&now);
        if(pageNumber==1)
            return;
        this->pageNumber-=1;
        this->ReadCurrentPage();
    }
    void menu()
    {
        while(true)
        {
            int choice;
            cout<<"Menu:"<<endl;
            cout<<"\t1: Next Page"<<endl;
            cout<<"\t2: Previous Page"<<endl;
            cout<<"\t3: Stop Reading"<<endl;
            cout<<"Enter number in range 1 - 3 "<<endl;
            cin>>choice;
            if(choice==1)
            {
                this->nextPage();
            }else if(choice==2)
            {
                this->PreviousPage();
            }else if(choice==3)
            {
                break;
            }
        }
    }

    void print()
    {
        cout<<this->currentBook.getTitle()<<" "<<pageNumber<<"/"<<currentBook.getNpages()<<" - "<<this->date<<endl;
    }

};



class user{
private:
    string name;
    string UserName;
    string password;
    string email;
    bool isAdmin{false};
    vector<bookHistory*> historyBooks;
public:
    user(string name,string username,string passwrod,string email){
        setname(name);
        setUname(username);
        setpass(passwrod);
        setemail(email);
    }
    void setname(string name)
    {
        this->name=name;
    }
    const string& Getname()const
    {
        return this->name;
    }
    void setUname(string name)
    {
        this->UserName=name;
    }
    const string& GetUname()const
    {
        return this->UserName;
    }
    void setpass(string pass)
    {
        this->password=pass;
    }
    const string& Getpass()
    {
        return this->password;
    }
    void setemail(string email)
    {
        this->email=email;
    }
    const string& Getemail()const
    {
        return this->email;
    }
    void setAdmin()
    {
        this->isAdmin=true;
    }
    const bool& Getadmin()const
    {
        return this->isAdmin;
    }

    bookHistory* addTobookHistory(book* booktoadd)
    {
        bookHistory *newbook=new bookHistory(*booktoadd);
        historyBooks.push_back(newbook);
        return newbook;
    }
    void ListReadingHis()
    {   
        for(int i=0; i<(int)historyBooks.size();++i)
        {
            cout<<i+1;
            historyBooks[i]->print();
        }
        cout<<endl;
        int choice;
        cout<<"Which session to open?:"<<endl;
        cout<<"Enter number in range 1 - "<< this->historyBooks.size()<<endl;
        cin>>choice;
        for(int i=0; i<(int)historyBooks.size();++i)
        {
            if(i+1==choice)
            {
                this->historyBooks[i]->ReadCurrentPage();
                this->historyBooks[i]->menu();
                break;
            }
        }

    }

};

class UserManager{
private:
    user* currentUser;
    map<string,user*> Total_Users;
    
public:
    UserManager()
    {
        user *p=new user("admin","admin","123","admin@");
        p->setAdmin();
        Total_Users["admin"]=p;
    }
    void Login(){
        while(true)
        {
            string n;
            cout<<"Enter user name (no spaces)"<<endl;
            cin>>n;
            if (!Total_Users.count(n)){
                cout<<"user doesnt exist!Please re-enter !!"<<endl;
                continue;
            }
            user * us=Total_Users[n];
            while(true)
            {
                cout<<"Enter password"<<endl;
                cin>>n;
                if(n==us->Getpass())
                {
                    this->currentUser=us;
                    return;
                }else{
                    cout<<"user name or password are wrong !!"<<endl;
                }
            }
            
        }
    }

    void SignUp()
    {
        while(true)
        {
            string userN;
            cout<<"Enter user name(No spaces)"<<endl;
            cin>>userN;
            if(Total_Users.count(userN))
            {
                cout<<"this user name exists!!!"<<endl;
                continue;
            }
            string p;
            string name;
            string email;
            cout<<"Enter passswrod"<<endl;
            cin>>p;
            cout<<"Enter name (no spaces)"<<endl;
            cin>>name;
            cout<<"Enter email (no spaces)"<<endl;
            cin>>email;
            this->currentUser=new user(name,userN,p,email);
            Total_Users[userN]=currentUser;
            break;
        }
        

    }
    void accessSystem()
    {
        int choice;
        cout<<"Menu\n"<<endl;
        cout<<"\t1: Login"<<endl;
        cout<<"\t2: Sign Up"<<endl;
        cout<<"Enter number in range 1 - 2"<<endl;
        cin>>choice;
        if(choice==1)
        {
            Login();
        }else{
            SignUp();
        }
    }

    user* getCurrentUser()const
    {
        return this->currentUser;
    }

    void ViewProfile()
    {
        cout<<"Name: "<<currentUser->Getname()<<endl;
        cout<<"Email: "<<currentUser->Getemail()<<endl;
        cout<<"User name: "<<currentUser->GetUname()<<endl;
    }

    bookHistory* addBookTouser(book* bookToadd)
    {
        return this->currentUser->addTobookHistory(bookToadd);
    }

    void ListReadingHis()
    {
        this->currentUser->ListReadingHis();
    }

};

class BookManager{
private:
    map<int,book*> Total_books;
public:
    BookManager(){
    }
    void addbook()
    {
        int ISBN;
        cout<<"Enter ISBN"<<endl;
        cin>>ISBN;
        string title;
        cout<<"Enter Title"<<endl;
        cin>>title;
        string at;
        cout<<"Author Name"<<endl;
        cin>>at;
        int np;
        cout<<"Enter how many pages"<<endl;
        cin>>np;
        vector<string> v;
        for(int i=1 ; i<=np;++i)
        {
            string s;
            cout<<"Enter page # "<<i<<endl;
            cin>>s;
            v.push_back(s);
        }
        book * newBook=new book(ISBN,title,at,np,v);
        this->Total_books[ISBN]=newBook;
    }

    void ListAllbooks()
    {
        int i{0};
        if(Total_books.size()<=0)
        {
            cout<<"There are no books in the library at the moment"<<endl;
            return;
        }
        for(auto const&x :Total_books)
        {
            cout<<++i<<" "<<x.second->getTitle()<<endl;
        }
    }
    book* chooseBook()
    {
        int choice;
        cout<<"Which book to read ?:"<<endl;
        cout<<"Enter number in range 1 - "<<Total_books.size()<<endl;
        cin>>choice;
        book *chosenbook;
        int i=0;
        for(auto const&x : Total_books)
        {
            if(i==choice-1)
            {
                chosenbook=x.second;
                break;
            }else{
                ++i;
            }
        }
        return chosenbook;
    }

};

class UserView{
private:
    UserManager &users;
    BookManager &books;
public:
    UserView(UserManager &users  ,BookManager &books):users(users),books(books)
    {
    }
    void view()
    {
        while(true)
        {
            int choice;
            cout<<"Menu:"<<endl;
            cout<<"\t1: View Profile"<<endl;
            cout<<"\t2: List & Select from My Reading History"<<endl;
            cout<<"\t3: List & Select from Available Books"<<endl;
            cout<<"\t4: Logout "<<endl; 
            cout<<"Enter number in range 1 - 4 "<<endl;
            cin>>choice;
            if(choice==1)
            {
             users.ViewProfile();
            }else if(choice==2)
            {
                this->users.ListReadingHis();
            }else if(choice==3)
            {
               this->books.ListAllbooks();
               cout<<endl;
               book* chosedBook=books.chooseBook();
               bookHistory* bookofuser=users.addBookTouser(chosedBook);
               bookofuser->ReadCurrentPage();
               bookofuser->menu();               
               
            }else if(choice==4)
            {
               break;
            }
            cout<<endl;
        }
       

    }
};

class AdminView{
private:
    UserManager &users;
    BookManager &books;
public:
    AdminView(UserManager &users  ,BookManager &books):users(users),books(books)
    {
    }
    void addBook()
    {
        books.addbook();
    }
    void view()
    {
      while(true)
      {
        int choice;
        cout<<"Menu:"<<endl;
        cout<<"\t1: View Profile"<<endl;
        cout<<"\t2: Add Book"<<endl;
        cout<<"\t3:Logout"<<endl;
        cin>>choice;
        if(choice==1)
        {
            users.ViewProfile();
        }else if(choice==2)
        {
            addBook();
        }else if(choice==3){
            break;
        }
        cout<<endl;
      }
    }
};

class OnlineBookReader{
private:
    UserManager *users;
    BookManager *books;
public:
    OnlineBookReader()
    {
        users=new UserManager();
        books=new BookManager();
    }

    void run()
    {
        while(true)
        {
            users->accessSystem();
            user* currentUser=users->getCurrentUser();
            if(currentUser->Getadmin())
            {
                cout<<"Hello "<<currentUser->Getname()<<" | Admin View ";
                AdminView admin(*users,*books);
                admin.view();
            }else{
                cout<<"Hello "<<currentUser->Getname()<<" | User View ";
                UserView user(*users,*books);
                user.view();
            }
        }
    }
};

int main()
{
    OnlineBookReader test;
    test.run();
    return 0;
}
