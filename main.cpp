



//	Cryptography Subject Works "The RSA Encryption Example".
//	2018/11/05-11/07


#include <bits/stdc++.h>

using namespace std;

#define MAX 99

long long PrimeSet[2];

char ori_mes[MAX] ; // origin message. 
int o_num_mes[MAX] = {0};// origin numbers transfered from message.
long e_num_mes[MAX];// encrypted number transferd from o_num_number.
int d_num_mes[MAX];// decrypted number.
char dec_mes[MAX]; // decrypted message.

int recieved_mes[MAX];

int meslen = 0;

long long phi, n;
int e = 17;
int d;

int rec_key1;
int rec_key2;

char m_option;


int GetMod(int a,int b,int c)
{
	int ans=1;
	a=a%c;
	while(b!=0)
	{
		if(b&1) ans=(ans*a)%c;
		b>>=1;
		a=(a*a)%c;
	}
	return ans;
}

bool IsPrime(const long long prime)
{
	int sq = sqrt(prime);
	if (prime%2 == 0 || prime%3 == 0 || prime%5 ==0 || prime%7 == 0 || prime%11 ==0) return false;
	for (int _ = 2; _ < sq; _++ )
	{
		if(prime%_ == 0) return false;
	}
	return true;
}

void GetPrime(long long PrimeSet[])
{
	do{
		for(int _ = 0; _ < 2; _++)
		{
			long long prime;
			do{
				srand((int)time(0));
				prime = 1;
				for(int __ = 0; __ < rand()%9 + 1; __++)
				{
					prime += rand();
				}
				prime = (abs(prime + (_+1) * rand()))/600;
				//cout << prime << endl;//return prime;
			}while(IsPrime(prime) == false);
			
			PrimeSet[_] = prime;
			cout << PrimeSet[_] << "  ";
			if (_ == 0)
			{
				cout << "and  ";
			}
		}
		}while(!(PrimeSet[0]+PrimeSet[1])%17);
}



int GetPriD(int e, long long phi)
{
	for (int m = 1; m < 999999; m++)
	{
		for (int n = 1; n < 999999; n++)
		{
			if((n*e == (m*phi)+1))
			{
				return n;
			}
		}
	}
	return 0;
}

void TransMesToNum(char ori_mes[], int o_num_mes[], int &meslen) // tramsfer origin message into numbers;
{
	string s_ori_mes;
	
	cout << "Please Enter Messages You Want To Be Encrypted: ";
	fflush(stdin);
	getline(cin, s_ori_mes);
	strcpy(ori_mes, s_ori_mes.c_str());
	meslen = strlen(ori_mes);
	for(unsigned int _ = 0; _ < strlen(ori_mes); _++)
	{
		o_num_mes[_] = ori_mes[_];
	}
	
}

void KeyGenerator(long long PrimeSet[],long long &phi, int &e, int &d, long long &n)
{
	n = PrimeSet[0]*PrimeSet[1];
	phi = (PrimeSet[0]-1)*(PrimeSet[1]-1);
	d = GetPriD(17, phi);
	while(d < 0){d += phi;};
}

void MeueSelect(char &m_option)
{
	cout << endl << endl << "Enter m or M To Go Back Meue.(Enter Others To Exit): ";
	cin >> m_option;
}

int main()
{

//GetPrime(PrimeSet);
//long long n = PrimeSet[0]*PrimeSet[1];
//long long phi = (PrimeSet[0]-1)*(PrimeSet[1]-1);
//
//int d = GetPriD(17, phi);
//while(d < 0)
//{
//	d += phi;
//}
//
//cout << "KU{e, n}="<< "{ 17, " << n << " }. KR{d, n}=" << "{ " << d << ", "  << n << " }." << endl;
//cout << "phi=" << phi << endl;
//
//int c = GetMod(99, 17, n);
//cout << "c:" << c << endl;
//int m = GetMod(c, d, n);
//cout << "m:" << m << endl;
	cout << "***The RSA Encryption Example Works***   ";
	int option = 0;
	while(1)
	{
		do{
			cout << endl << endl << "Please Select: " << endl ;
			cout << "                1. Encryption(Generating New Keys And Encrypt Messages.)"<< endl
				 << "                2. Decryption(Using Keys You Had To Decryption Messages. )"<< endl
				 << "                3. Encryption(Encrypt Messages Via Existing Keys.)" << endl
				 << "                4. Exit"<< endl;
				 cin >> option;
				 if(option == 4){exit(0);};
			}while(option != 1 && option != 2 && option != 3);
		
		
		if(option == 1)
		{
			cout << endl << endl << "The Program Is Generating Parameters. Please Waiting..." << endl;
			
			cout << endl << "The Prime Number For Encryption Is :";
			GetPrime(PrimeSet);

			KeyGenerator(PrimeSet, phi, e, d, n);
			cout << endl << endl << "The Public Key Is: { " << d << ", " << n << " }		";
			cout << "The Private Key Is: { " << e << ", " << n << " }" << endl << endl; 
			
			TransMesToNum(ori_mes, o_num_mes, meslen); long temp;
			cout << endl  << "                         "
			<<"( Send This Message Out And Use PUBLIC Key To Decrypt.)" << endl << endl <<"The Encrypted Messages Is: ";
			for(int __ = 0; __ < meslen; __++)
			{
				temp = GetMod(o_num_mes[__], e, n);
				e_num_mes[__] = temp;
				cout << e_num_mes[__] << " ";
				//cout <<"origin" << o_num_mes[__];
				
			};
			
			MeueSelect(m_option);
			if(!(m_option == 'm' || m_option == 'M'))
				return 0;
				//exit(0);
		}
		
		
		
		if(option == 2)
		{
			cout << endl << endl << "Please Enter Messages You Want To Be Decrypted: ";
		
			int mes_counter = 0;
			char cha;
			
			cin >> recieved_mes[mes_counter++];
			
			while((cha=getchar())!='\n')
			{
				cin>>recieved_mes[mes_counter++];
			}
			
			cout<< endl << endl << "Please Enter Your FIRST Key: ";
			cin >> rec_key1;
			cout << endl << "Please Enter Your SECOND Key: ";
			cin >> rec_key2; cout << endl << endl;
			cout << "The Decrypted Messages Is:"; char tempc;
			for(int __ = 0; __ < mes_counter; __++)
			{
				long temp = GetMod(recieved_mes[__], rec_key1, rec_key2);
				dec_mes[__] = temp;
				tempc = temp;
				cout << tempc ;
			}
			
			MeueSelect(m_option);
			if(!(m_option == 'm' || m_option == 'M'))
				return 0;
				//exit(0);
		}
		
		if(option == 3)
		{
			TransMesToNum(ori_mes, o_num_mes, meslen); long temp;
			fflush(stdin);
			cout<< endl << endl << "Please Enter Your FIRST Key: ";
			cin >> rec_key1;
			cout << endl << "Please Enter Your SECOND Key: ";
			cin >> rec_key2; cout << endl << endl;
			
			cout << endl  << "                         "
			<<"( Send This Message Out And Use PUBLIC Key To Decrypt.)" << endl << endl <<"The Encrypted Messages Is: ";
			for(int __ = 0; __ < meslen; __++)
			{
				temp = GetMod(o_num_mes[__], rec_key1, rec_key2);
				e_num_mes[__] = temp;
				cout << e_num_mes[__] << " ";
				//cout <<"origin" << o_num_mes[__];
				
			};
			
			MeueSelect(m_option);
			if(!(m_option == 'm' || m_option == 'M'))
				return 0;
				//exit(0);
		}
	}
	
	

	
}

