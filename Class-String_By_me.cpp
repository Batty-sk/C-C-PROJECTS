#include<iostream>
#include<conio.h>	
using namespace std;			

class String{		
	//Properties-
	private:
		char *str=nullptr;
	public:
		int size=NULL;
		int pre_size=NULL;
		int len=0;
				//Methods-
		
		//defining the constructors
		String()
		{
			str=new char;
			size=0;
		}
		String(char *userstring)
		{
			this->copy_string(userstring,*this);
		}
		
		// Function to copy the user-given string to string object.
		void copy_string(char *userstring,String &obj,int flag=0,bool use_check_len=true)
		{
			int i;
			int k;
			if (use_check_len)
			
			{
				int len=this->Check_len<char>(userstring,"char");
				
				if (size<len){
					this->Allot_memory(len,*this);
					}
				else{
					size=len;
					}
			}
				
			if (flag)
			{
				k=obj.pre_size-1;
			}
			else{
				k=0;
			}
			for(i=0,k;userstring[i];i++,k++)
				{
					obj.str[k]=userstring[i];
				}
			obj.str[k]='\0';

		}
		
		//Function to check the length of the string.
		template <class dt>
		int Check_len(dt *userstring,char *data_type)
		{
			int i=0;
			if (data_type == "char")
			{
				for(i=0;userstring[i];i++);
			}
			else if(data_type == "int")
			{
				
				while(*userstring>0)
					{
						*userstring/=10;
						i+=1;
					}
			}
			return i+1;
		}
		
		//Function to Allot/Changing the size of  the memeory if the len of a string is larger than the previous length of a string obj.
		void Allot_memory(int len_of_string,String &obj,int flag=1)
			{				//10
				if (flag)
				{
				 delete_str();
				 str=new char[len_of_string];
				 size=len_of_string;
				}
				else{
				delete []obj.str;
				obj.str=new char[len_of_string];//110;
				obj.size=len_of_string;//10 
				}
			}
			//used by operator + with integer argument.
		void Convert_To_str(int no,char str[],int k)
		{
			if(no>0)
				{
					Convert_To_str(no/10,str,k-1);
					str[k]=no%10+48;
				}
			return;
		}
		
		void delete_str()
		{
			delete []str;
		}
		
		// overloading the '='  operator.
		void operator = (String obj)
			{
				copy_string(obj.str,*this);
			}
			
		//overloading the '+' operator for string value.
		String  operator + (char *userstring)
		{
			// concadinate.
			String obj;
			obj.pre_size=size;//7
			Allot_memory(size+Check_len<char>(userstring,"char"),obj,0);  // abcd  dcewa
			copy_string(str,obj,0,false);
			copy_string(userstring,obj,1,false);
			return obj;
		}
	
		//overloading the '+' operator for int value.
		String operator + (int no)
		{
			String obj;
			obj.pre_size=size;
			int temp_no=no;
			int len=Check_len<int>(&no,"int");
			Allot_memory(size+len,obj,0);
			copy_string(str,obj,0,false);
			char Str[len];
			Convert_To_str(temp_no,Str,len-2);
			Str[len-1]='\0';
			copy_string(Str,obj,1,false);
			return obj;
			
		}
		
		//overloading the '-' operator to removes the dublicates from a string.
		String operator - (char *userstring)
		{
			int i,j,count=0,total_size=size+Check_len<char>(userstring,"char");
			char Unique_string[total_size];

			for(i=0;userstring[i];i++)
				{
					for(j=0;str[j];j++)
					{					
						if(str[j]==userstring[i])
							{						
								str[j]=-1;
								break;	
							}			
									
					}

					if (!str[j])
							Unique_string[count++]=userstring[i];
				}

			// putting all the non-dublicates to the unique string.
			
			for(j=0;str[j];j++)
				{
					if (str[j]!=-1)
							Unique_string[count++]=str[j];
			
				}
			Unique_string[count]='\0';
			String obj;
			obj.size=count;
			Allot_memory(count,obj,0);
			copy_string(Unique_string,obj,0,false);
			return obj;
			
		}
		
		//overloading the '==' operator to compare two strings.
		bool operator == (char *userstring)
		{
			int i;
			int len=Check_len<char>(userstring,"char");
			if (len==size)
			{
			for(i=0;userstring[i];i++)
				{
					if (userstring[i]!=str[i])
					{
						return false;
					}
				}
				return true;
			}

			return false;
		}				  	
		// Defining the friend function to overload the '<<' and '>>' operator 
		friend void operator << (ostream &,String &);
		friend void operator >> (istream &, String &);
		~String()
		{
			delete []str;
		}
		
};
void operator << (ostream &cout,String &obj)//we can't make an object of cout and cin that's why we have to make a refrence variable of it.
{
	cout<<obj.str;// because it's freind function of string class that means it can access all the methods and variables.
}
void operator >> (istream &, String &obj)
{
	obj.Allot_memory(100,obj,1);
	cin.getline(obj.str,obj.size);
}

int main()
{
	
	// How to use-
	String s="Hello";//assignment of string
	
	cout<<s;//printing the string.
	
	String s2,s3;//creating a object of String.
	s=s+"world hee";//concadination of strings.
	s2=s+12;//concadination of a string and a number.
	cout<<s2;
	bool result=s=="Helloworld hee";//checking if the string is equals to the given string.
	cout<<result<<endl;//Returns the bool value.
	s2=s-"w";//removing the dublicates from string.
	cout<<s2;
	cout<<s;
	cout<<endl<<"Enter A string"<<endl;
	cin>>s;
	cout<<s;

}
