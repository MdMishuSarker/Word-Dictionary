#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<windows.h>
#include<conio.h>

using namespace std;

struct WordDictionary
{
    char word[25], mean[50];
    struct WordDictionary *left, *right;
};

struct WordDictionary *insert(struct WordDictionary*, char, char);
struct WordDictionary *Word_Dictionary(struct WordDictionary*);
struct WordDictionary *Admin(struct WordDictionary*);
struct WordDictionary *User(struct WordDictionary*);
void showall(struct WordDictionary*, char);

struct WordDictionary *find_minimum(struct WordDictionary *root)
{

    if(root->left != NULL)
        return find_minimum(root->left);
    return root;

}

struct WordDictionary *insert(struct WordDictionary *temp, char W[], char M[])
{
    if(temp==NULL)
    {
        temp = (struct WordDictionary*)malloc(sizeof(struct WordDictionary));
        strcpy(temp->word, W);
        strcpy(temp->mean, M);
        temp->left = temp->right = NULL;
    }
    else if(strlen(W)>=strlen(temp->word))
    {
        temp->right = insert(temp->right, W, M);
    }
    else
    {
        temp->left = insert(temp->left, W, M);
    }
    return temp;
}

void showall(struct WordDictionary *temp, char W[])
{
    if(temp!=NULL)
    {
        showall(temp->left, W);
        if(W[0]==temp->word[0] && W[1]==temp->word[1])
            cout << "  '" << temp->word << "' ";
        showall(temp->right, W);
    }
}

void sort(struct WordDictionary *root, char h, char s)
{
    if(root!=NULL)
    {
        sort(root->left, h, s);
        if(root->word[0]== h || root->word[0]==s)
            cout <<  root->word << " = " << root->mean << endl;
        sort(root->right, h, s);
    }
}

struct WordDictionary *deleteNode(struct WordDictionary *root, char W[])
{
    if(root==NULL)
        return NULL;
    if (strlen(W)>strlen(root->word))
        root->right = deleteNode(root->right, W);
    else if(strlen(W)<strlen(root->word))
        root->left = deleteNode(root->left, W);
    else
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }
        else if(root->left==NULL || root->right==NULL)
        {
            struct WordDictionary *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            struct WordDictionary *temp = find_minimum(root->right);
            strcpy(root->word,temp->word);
            strcpy(root->mean,temp->mean);
            root->right = deleteNode(root->right, temp->word);
        }
    }
    return root;
}

int searching(struct WordDictionary *root, char W[])
{
    struct WordDictionary *temp = root;
    if(root!=NULL)
    {
        if(strcmp(root->word, W)==0)
        {
            cout <<  root->word << " = " << root->mean << endl;
            return 1;
        }
        else if(strlen(W)>=strlen(root->word))
            return searching(root->right, W);
        else if(strlen(W)<strlen(root->word))
            return searching(root->left,W);
        else
        {
            return 0;
        }
    }
}

struct WordDictionary *edit(struct WordDictionary *root, char W[])
{
    if(root!=NULL)
    {
        if(strcmp(root->word, W)==0)
        {
            char word[25], mean[50];
            cout << "We Found The Word \n Enter the New Word & Meaning" << endl;
            cout << "Word:";
            gets(word);
            cout << "Meaning:";
            gets(mean);
            strcpy(root->word, word);
            strcpy(root->mean, mean);
        }
        else if(strlen(W)>=strlen(root->word))
            root->right = edit(root->right, W);
        else if(strlen(W)<strlen(root->word))
            root->left = edit(root->left, W);
    }
    return root;
}

struct WordDictionary *Word_Dictionary(struct WordDictionary *root)
{
    char n, c[20];
    char pass[] = "mishu";
    cout << "1.Admin" << endl;
    cout << "2.User" << endl;
    cout << "0.Exit" << endl;
    cout << "Enter your option:";
    n = getch();
    cout << endl;
    switch(n)
    {
    case '1':
    {
        system("cls");
        cout << "Enter The Password:";
        gets(c);
        if(strcmp(pass, c)==0)
        {
            root = Admin(root);
        }
        else
        {
            cout << "Wrong Password. Try again." << endl;
            return Word_Dictionary(root);
        }
        break;
    }
    case '2':
    {
        system("cls");
        root = User(root);
        break;
    }
    case '0':
        system("cls");
        return root;
        break;

    default:
        system("cls");
        return Word_Dictionary(root);
        break;
    }
}

struct WordDictionary *Admin(struct WordDictionary *root)
{
    while(true)
    {
        char n;
        char word[25], mean[50], search[50];
        cout << "1.Insertion" << endl;
        cout << "2.Show All" << endl;
        cout << "3.Delete" << endl;
        cout << "4.Search" << endl;
        cout << "5.Edit" << endl;
        cout << "0.Back" << endl;

        cout << "Enter your option:";
        n = getch();
        cout << endl;
        switch(n)
        {
        case '1':
        {
            system("cls");
            cout << "Word:";
            gets(word);
            cout << "Meaning:";
            gets(mean);
            root = insert(root, word, mean);
            break;
        }
        case '2':
        {
            system("cls");
            char h = 'a', s = 'A';
            for(int i = 0; i<26; i++)
            {
                sort(root, h, s);
                h++;
                s++;
            }
            break;
        }
        case '3':
        {
            system("cls");
            cout << "Enter The Word:";
            gets(search);
            root = deleteNode(root, search);
            break;
        }
        case '4':
        {
            system("cls");
            cout << "Enter The Word:";
            gets(search);
            int k = searching(root, search);
            if(k==0)
            {
                cout << "Not Found" << endl;
                cout << "Did you mean :";
                showall(root, search);
            }
            cout << endl;
            break;
        }
        case '5':
        {
            system("cls");
            cout << "Enter The Word:";
            gets(search);
            root = edit(root, search);
            break;
        }
        case '0':
            system("cls");
            return Word_Dictionary(root);
            break;
        default:
            system("cls");
            return Admin(root);
            break;
        }
    }

}

struct WordDictionary *User(struct WordDictionary *root)
{
    while(true)
    {
        char n;
        char search[50];
        cout << "1.Show All" << endl;
        cout << "2.Search" << endl;
        cout << "0.Back" << endl;
        cout << "Enter your option:";
        n = getch();
        cout << endl;
        switch(n)
        {
        case '1':
        {
            system("cls");
            char h = 'a', s = 'A';
            for(int i = 0; i<26; i++)
            {
                sort(root, h, s);
                h++;
                s++;
            }
            break;
        }
        case '2':
        {
            system("cls");
            cout << "Enter The Word:";
            gets(search);
            int k = searching(root, search);
            if(k==0)
            {
                cout << "Not Found" << endl;
                cout << "Did you mean :";
                showall(root, search);
            }
            break;
        }
        case '0':
            system("cls");
            return Word_Dictionary(root);
            break;
        default:
            system("cls");
            return User(root);
            break;
        }
    }
}

int main()
{
    struct WordDictionary *root = NULL;
    root = Word_Dictionary(root);
}
