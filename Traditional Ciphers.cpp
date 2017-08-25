// A C++ program to illustrate Traditional Cipher Techniques

#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

//Caesar Cipher Functions
string caesar_encrypt(string text, int s)
{
	string result = "";

	// traverse text
	for (int i=0;i<text.length();i++)
	{
		// apply transformation to each character
		// Encrypt Uppercase letters
		if (isupper(text[i]))
			result += char(int(text[i]+s-65)%26 +65);

	// Encrypt Lowercase letters
	else
		result += char(int(text[i]+s-97)%26 +97);
	}

	// Return the resulting string
	return result;
}
string caesar_decrypt(string text, int s)
{
	string result = "";

	// traverse text
	for (int i=0;i<text.length();i++)
	{
		// apply transformation to each character
		// Encrypt Uppercase letters
		if (isupper(text[i]))
			result += char(int(text[i]-s-65)%26 +65);

	// Encrypt Lowercase letters
	else
		result += char(int(text[i]-s-97)%26 +97);
	}
    // Return the resulting string
	return result;
}

//Playfair Cipher
void get_pos(char, int&, int&);
void same_row(int, vector<char>&, int, int);
void same_column(int, vector<char>&, int, int);
void diff_col_row(int, int, vector<char>&, int, int);
void encode(vector<char>, int);
void get_input(vector<char>&);
void convert_string(vector<char>&, vector<char>&);
const char encoder[5][5]={{'A','B','C','D','E'},
                      {'F','G','H','I','K'},
                      {'L','M','N','O','P'},
                      {'Q','R','S','T','U'},
                      {'V','W','X','Y','Z'}};

void get_pos(char p, int& r, int& c)
{
    if (p < 'J')
    {
        r = (p - 65) / 5;
        c = (p - 65) % 5;
    }
    else if (p > 'J')
    {
        r = (p - 66) / 5;
        c = (p - 66) % 5;
    }
    return;
}

void same_row(int r, vector<char>& code, int c1, int c2)
{
    code.push_back(encoder[r][(c1 + 1) % 5]);
    code.push_back(encoder[r][(c2 + 1) % 5]);
    return;
}

void same_column(int c, vector<char>& code, int r1, int r2)
{
    code.push_back(encoder[(r1 + 1) % 5][c]);
    code.push_back(encoder[(r2 + 1) % 5][c]);
    return;
}

void diff_col_row(int r1, int c1, vector<char>& code, int r2, int c2)
{
    code.push_back(encoder[r1][c2]);
    code.push_back(encoder[r2][c1]);
    return;
}

void encode(vector<char> msgx, int len)
{
    vector<char> code;
    int i = 0, j = 0;
    int r1, c1, r2, c2;
    while (i < len)
    {
        get_pos(msgx[i], r1, c1);
        i++;
        get_pos(msgx[i], r2, c2);
        if (r1 == r2)
        {
            same_row(r1, code, c1, c2);
        }
        else if (c1 == c2)
        {
            same_column(c1, code, r1, r2);
        }
        else
        {
            diff_col_row(r1, c1, code, r2, c2);
        }
        i++;
    }
    cout<<"\nCODE: ";
    for (j = 0;j < code.size();j++)
    {
        cout<<code[j];
    }
    return;
}

void get_input(vector<char>& a)
{
    char c;
    while (1)
    {
        cin>>c;

        if (c >= 97 && c <= 122)
        c-=32;
        if (c == '\n')
            break;
        else if (c==' ')
            continue;
        else if (c == 'J')
        a.push_back('I');
        a.push_back(c);
    }
    return;
}

void convert_string(vector<char>& msg, vector<char>& msgx)
{
    int i, j;
    i = 0;j = 0;
    while (i < msg.size())
    {
        msgx.push_back(msg[i]);
        i++;
        if (i == msg.size())
        {
            msgx.push_back('X');
            break;
        }
        if (msg[i] == msgx[j])
        {
            msgx.push_back('X');
            j++;
        }
        else if(msg[i] != msgx[j])
        {
            j++;
            msgx.push_back(msg[i]);
            i+=1;
        }
        j++;
    }
}

//Vigenere Cipher Functions
string vigenere_generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}
string vigenere_encrypt(string str, string key)
{
	string cipher_text;

	for (int i = 0; i < str.size(); i++)
	{
		// converting in range 0-25
		int x = (str[i] + key[i]) %26;

		// convert into alphabets(ASCII)
		x += 'A';

		cipher_text.push_back(x);
	}
	return cipher_text;
}
string vigenere_decrypt(string cipher_text, string key)
{
	string orig_text;

	for (int i = 0 ; i < cipher_text.size(); i++)
	{
		// converting in range 0-25
		int x = (cipher_text[i] - key[i] + 26) %26;

		// convert into alphabets(ASCII)
		x += 'A';
		orig_text.push_back(x);
	}
	return orig_text;
}

//Hill cipher functions
float encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];
void inverse();
string hill_encrypt() {
    int i, j, k;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 1; j++)
            for(k = 0; k < 3; k++)
                encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];

    string e;
    for(i = 0; i < 3; i++)
        e.push_back((char)(fmod(encrypt[i][0], 26) + 97));
    return(e);
}

string hill_decrypt() {
    int i, j, k;
    cout<<"zdgzfdg";
    inverse();

    for(i = 0; i < 3; i++)
        for(j = 0; j < 1; j++)
            for(k = 0; k < 3; k++)
                decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];

    string d;
    for(i = 0; i < 3; i++)
        d.push_back((char)(fmod(decrypt[i][0], 26) + 97));
    return(d);
}

void hill_getKeyMessage() {
    int i, j;
    char msg[3];

    cout<<"Enter 3x3 matrix for key (It should be inversible):\n";

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++) {
            cin>>a[i][j];
            c[i][j] = a[i][j];
        }

    cout<<"\nEnter a 3 letter plain text(small letters): ";
    cin>>msg;

    for(i = 0; i < 3; i++)
        mes[i][0] = msg[i] - 97;
}

void inverse() {
    int i, j, k;
    float p, q;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++) {
            if(i == j)
                b[i][j]=1;
            else
                b[i][j]=0;
        }

    for(k = 0; k < 3; k++) {
        for(i = 0; i < 3; i++) {
            p = c[i][k];
            q = c[k][k];

            for(j = 0; j < 3; j++) {
                if(i != k) {
                    c[i][j] = c[i][j]*q - p*c[k][j];
                    b[i][j] = b[i][j]*q - p*b[k][j];
                }
            }
        }
    }

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            b[i][j] = b[i][j] / c[i][i];

    cout<<"\n\nInverse Matrix is:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++)
            cout<<b[i][j]<<" ";

        cout<<"\n";
    }
}
// Menu driven program
int main()
{
    cout<<"S. DHANYA ABHIRAMI\n16BCE0965\nTraditional Ciphers\n";
	//p-plain text , e-encrypted text , d-decrypted text
	string p,e,d;
	char c,ch='y';
	while(ch=='y'||ch=='Y'){

	    cout<<"\nEnter cipher technique to use: ";
	    cout<<"\n1. Caesar Cipher\n2. Vigenere Cipher\n3. Hill Cipher\n";
	    cin>>c;
	    switch(c){
	        case '1':
	        {
	       cout<<"\nEnter plain text: ";
	        cin>>p;
	        int k;
	        cout<<"\nEnter key: ";
	        cin>>k;
	        e=caesar_encrypt(p,k);
	        d=caesar_decrypt(e,k);
	        break;}
	        case '2':
	        {cout<<"\nEnter plain text(all caps): ";
	        cin>>p;
	        string keyword,k;
	        cout<<"\nEnter keyword(length<=plain text length): ";
	        cin>>keyword;
	        k=vigenere_generateKey(p,keyword);
	        e=vigenere_encrypt(p,k);
	        d=vigenere_decrypt(e,k);
	        break;}
	        case '3':
	        {hill_getKeyMessage();
            e=hill_encrypt();
            d=hill_decrypt();
            break;}
	       }
	    cout<<"\nEncrypted Text: "<<e<<"\nDecrypted Text: "<<d;
	    cout<<"\nWant to continue? Y/N: ";
	    cin>>ch;
	}
	return 0;
}
