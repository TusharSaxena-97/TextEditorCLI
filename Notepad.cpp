#include<bits/stdc++.h>

using namespace std;

class User{

private:

    string UserID;

public:
    User(string id)
    {
       UserID = id;
    }
    string getUserID(){return UserID;}
};

class File{
private:
    string extension=".txt";
    string FileName;
    unordered_set<User*> Users;
    User* owner;

public:
    ~File()
    {
        FileName+=extension;
        char* char_array = new char[FileName.length() + 1];

        strcpy(char_array, FileName.c_str());

        if (!remove(char_array))
        cout<<"Deleted successfully file = "<<FileName<<endl;
        else
        cout<<"Unable to delete the file"<<endl;
    }

    File(string filename)
    {
      FileName = filename;
      filename += extension;
      fstream file;
      file.open(filename,ios::out);
      if(!file){
        cout<<"Error in file creation!"<<endl;
       }else{
        cout<<"File Creation successfull."<<endl;
      }
      file.close();
    }

    string getFileName()
    {
     return FileName;
    }
    unordered_set<User*> getUsers()
    {
      return Users;
    }
    void setUsers(User* user)
    {
        Users.insert(user);
    }

    User* getOwner()
    {
        return owner;
    }

    void setOwner(User* user)
    {
       owner = user;
    }

    void DisplayUsers()
    {
      for(auto it:Users)
        cout<< it->getUserID() <<"  ";
      cout<<endl;
    }

    void WriteFile(){
        EditFile();
    }

    void EditFile(){

          //  cout<<"Check Point 2"<<endl;
          string filename = FileName + extension;
          ofstream outfile;
          outfile.open(filename, ios_base::app);
          string str;
          cout<<"Enter The Text You want to enter into the File ===> "<<endl;
          cin.clear();cin.sync();
          getline(cin,str);
          outfile <<str;
          outfile.close();
    }

    void ReadFile()
    {
        string filename = FileName + extension;

        string myText;

        // Read from the text file
        ifstream MyReadFile(filename);

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, myText)) {
          // Output the text from the file
          cout << myText;
        }
        // Close the file
        MyReadFile.close();
    }
};


class Notepad{

private:
     User* current_user;
     string NotepadId;
     unordered_map<string,User*> NotepadUsers;
     unordered_map<string,File*> ListOfFiles;
     User* admin;

     User* is_exsist(string uid)
     {
        auto it = NotepadUsers.find(uid);
        if(it == NotepadUsers.end())
            return NULL;

        return it->second;
     }


     File* is_exsist_file(string fname)
     {
        auto it = ListOfFiles.find(fname);

        if(it == ListOfFiles.end()) return NULL;

        return it->second;
     }

public:
    string InputUserName()
    {
        string user1;
        int n = 1;
            while(n)
            {
                cout<<"Enter The User ID"<<endl;
                cin>>user1;

                if(!is_exsist(user1)) {
                    cout<<"This User Does not exist  please enter a new valid User ID"<<endl;
                       continue;
                }
                else n=0;
            }

        return user1;
    }

    string InputFileName()
    {
        string fname;
        int n = 1;
            while(n)
            {
                cout<<"Enter The User ID"<<endl;
                cin>>fname;

                if(!is_exsist_file(fname)) {
                    cout<<"This File D  please enter a new valid User ID"<<endl;
                       continue;
                }
                else n=0;
            }

        return fname;
    }

    Notepad()
    {

     User* user = new User("admin");
     this->admin = user;
     cout<<"Welcome to Notepad You are here as Admin"<<endl;

     // Added admin to noptepad users;
     NotepadUsers["admin"] = user;
     current_user = user;
    }

    void SwitchUser()
    {
      cout<<"Enter The UserID you wan to switch to "<<endl;

      string uid;
      int n = 1;
        while(n)
        {
            cout<<"Enter The User ID  \t Enter 'exit' to return "<<endl;
            cin>>uid;
            if(uid=="exit") return;

            if(!is_exsist(uid)){
                cout<<"This User Does not exist please enter a new valid User ID"<<endl;
                   continue;
            }
            else n=0;
        }

    current_user = NotepadUsers[uid];
    cout<<"The Current user now is "<<current_user->getUserID();

    }

    void DiplayUsers()
    {
      for(auto it:NotepadUsers)
        cout<<it.second->getUserID()<<"  ";

        cout<<endl;
    }

    void DisplayFiles()
    {
        int n;
        for(auto it:ListOfFiles)
            cout<<it.second->getFileName()<<"  ";
        cout<<endl;
        cin>>n;
    }

    void CreateUser(){

        int n = 1;
        while(n)
        {
            cout<<"Enter The User ID  \t  Enter 'exit' to return to the main menu"<<endl;
            string uid;
            cin>>uid;
            if(uid=="exit") return;

            if(is_exsist(uid)) {
                    cout<<"UserID already in Use Please choose a new USER ID"<<endl;
                    continue;
            }

            else
            {
             User* newuser = new  User(uid);
             NotepadUsers.insert(make_pair(uid,newuser));
             cout<<"User Created Successfully with UserID = "<<uid<<endl;
             n=0;
            }
        }

       // DiplayUsers();
    }

    void CreateFile(){

        int n=1;
        while(n)
        {
         string fname;
         cout<<"Enter The Name of the file  \t\t Enter 'exit' to return back to main menu"<<endl;
         cin>>fname;
         if(fname=="exit") return;

         if(is_exsist_file(fname))
         {
            cout<<"File Already Exists  Choose new name for the file"<<endl;
            continue;
         }
         else{
            File *newfile = new File(fname);
            ListOfFiles[fname] = newfile;
            cout<<"New File created successfully with the name = "<<fname<<endl;

            newfile->setOwner(current_user);
            newfile->setUsers(current_user);

            newfile->WriteFile();
            n=0;
         }
        }
       // DisplayFiles();
    }

    void EditFile(){

        int n = 1;
        string fname;
        while(n)
        {
            cout<<"Enter The FileName  \t Enter 'exit' to return to main menu"<<endl;
            cin>>fname;
            if(fname == "exit") return;

            if(!is_exsist_file(fname)) {
                cout<<"This file Does not exist please enter a new valid FileName"<<endl;
                   continue;
            }

            else if(ListOfFiles[fname]->getUsers().find(current_user) != ListOfFiles[fname]->getUsers().end())
            {
                   // cout<<"Reached Check Point 1"<<endl;
                    ListOfFiles[fname]->EditFile();
                    return;
            }
            else {
                cout<<"You do not have access to the file"<<endl;
                n=0;
            }
        }
    }

    void DeleteFile(){

        int n=1;
        while(n)
        {
         string fname;
         cout<<"Enter The Name of the file  \t enter 'exit' to return to main menu"<<endl;
         cin>>fname;
         if(fname=="exit") return;

         if(!is_exsist_file(fname))
         {
            cout<<"File Does Not Exist Please enter Again File Name"<<endl;
            continue;
         }
         else if(ListOfFiles[fname]->getOwner() == current_user){

            ListOfFiles[fname]->~File();
            ListOfFiles.erase(fname);
            cout<<"Successfully Deleted File => "<<fname<<endl;
            n=0;
         }
         else {
            cout<<"You  are Not the owner of the File Try Again"<<endl;
                return;
            }

        }
    }

    void GrantAccess(){

        string user2;

        int n = 1;
        while(n)
        {
            cout<<"Enter The User ID of the user you want to Grant Access to"<<endl;
            cin>>user2;
            if(user2=="exit") return;

            if(!is_exsist(user2)) {
                cout<<"This User Does not exist  please enter a new valid User ID   \t enter 'exit' to return to main Menu"<<endl;
                   continue;
            }
            else n=0;
        }

        n=1;
        while(n)
        {
             string fname;
             cout<<"Enter The Name of the file want to grant access to "<<endl;
             cin>>fname;

             if(!is_exsist_file(fname))
             {
                cout<<"File does not exist"<<endl;
                continue;
             }
             else if(ListOfFiles[fname]->getOwner() == current_user){
                     ListOfFiles[fname]->setUsers(NotepadUsers[user2]);

                    ListOfFiles[fname]->DisplayUsers();
                    return;
             }
             else {
                cout<<"You Are Not the owner of the File. Hence You can not Grant Access "<<endl;
                n=0;
             }
        }
    }

    void ReadFile()
    {
        int n = 1;
        string fname;
        while(n)
        {
            cout<<"Enter The FileName   \t Enter 'exit' to return to the main menu "<<endl;
            cin>>fname;
            if(fname=="exit") return;

            if(!is_exsist_file(fname)) {
                cout<<"This file Does not exist please enter a new valid FileName"<<endl;
                   continue;
            }

            else if(ListOfFiles[fname]->getUsers().find(current_user) != ListOfFiles[fname]->getUsers().end())
            {
                   // cout<<"Reached Check Point 1"<<endl;
                    ListOfFiles[fname]->ReadFile();
                    return;
            }
            else {
                cout<<"You do not have access to the file"<<endl;
                n=0;
            }
        }



    }
};


int main()
{
    int n=1;

    Notepad notepad;
    while(n)
    {
        cout<<"\n\n\t\tMENU"<<endl;
        cout<<"\t1 - To Create a new user "<<endl;
        cout<<"\t2 - To Create a new File "<<endl;
        cout<<"\t3 - To Edit a existing File"<<endl;
        cout<<"\t4 - To Delete an existing File"<<endl;
        cout<<"\t5 - To Grant Access to Other Users"<<endl;
        cout<<"\t6 - To Read an Already Existing File"<<endl;
        cout<<"\t7 - To Switch to a new user "<<endl;
        cout<<"\t8 - To Display All the existing files"<<endl;
        cout<<"\t9 - To EXIT Notepad Application"<<endl;

        cin>>n;

        if(n==1)
            notepad.CreateUser();
        else if(n==2)
            notepad.CreateFile();
        else if(n==3)
            notepad.EditFile();
        else if(n==4)
            notepad.DeleteFile();
        else if(n==5)
            notepad.GrantAccess();
        else if(n==6)
            notepad.ReadFile();
        else if(n==7)
            notepad.SwitchUser();
        else if(n==8)
            notepad.DisplayFiles();
        else if(n==9)
            return 0;
        else
            cout<<"Invalid Choice Please Choose Again";
    }
    return 0;
}
