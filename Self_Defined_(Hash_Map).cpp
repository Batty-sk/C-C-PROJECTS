#include<iostream>
using namespace std;
class dictonary;
struct Element;

struct Element{
	
	char *key;
	int value;
	
	Element()
	{
		key=nullptr;
		value=0;
	}
	
	void operator = (Element *e)// baby is not present so i would hold the value in the temp variable.
	{
		key = e->key;
		value= e->value;
	}
	

	
}; 

class Dictonary{
	
	private:
		struct Element *e;
		int CurrentFill=0;
		int Size=0;
		char *holdstring=nullptr;
		int assignment=0;
		char **Keys;
	public:
		Dictonary()
		{ 								   	 
			e=new Element[++Size];//1 
			// 1		 	
		}		 	
	Dictonary &operator [](char *ptr) 
	{ 				    
		holdstring=ptr;
		return *this;	
	}							
						
	Dictonary &operator = (int x)
		{
			//if holdstring is already present as key so i would update the value of that key with the value inside x.
		//	Create_Pair(holdstring,x);
			if( holdstring !=nullptr)
				{
					if(!Check_Available(holdstring,x))
					{
						Create_Pair(holdstring,x);
					}
					holdstring=nullptr;

				}
			else{
				cout<<"Try This obj[key] = value"<<endl;
			}
				
				return *this; 		
		}

	
	int Create_Pair(char *ptr, int no)
	{						
		if(isOverflow())	
		{					
			Double_Size();	
		}
		
		e[CurrentFill].key=ptr;
		e[CurrentFill].value=no;
		CurrentFill++;
		return 1;
	}
	
	int Check_Available(char *ptr,int value)
	{	
		int i=0;
		for(i;i<CurrentFill;i++)
		{
			if(ptr == e[i].key )
				{
					e[i].value = value;
					return 1;
				}
		}
		return 0;
	}
	
	void Double_Size()
	{
		struct Element *temp=e;
		e=new Element[Size*2];
		CopyElements(temp);
		delete []temp;
		Size*=2;
	}
	void CopyElements(struct Element *temp)
	{
		int i=0;
		while(i<CurrentFill)
		{
			e[i]=&temp[i];
			i++;
		}
	}
	int isOverflow()
	{
		if(CurrentFill==Size)
		{
			return 1;
		}
		return 0;
	}
	
	int Delete_Pair(char *ptr)
	{	
		int i=0;
		int j;
		for(i;i<CurrentFill;i++)
			{
				if(e[i].key == ptr)
					{
						j=i;
						while(j<CurrentFill)
							{
								e[j]=&e[j+1];
								j++;
							}
						
						CurrentFill--;
						return 1;						
					}	
			}
			return 0;	
	}
	
	char ** keys()
	{
		Keys = new char *[CurrentFill];// creating an array of keys size = currentFill 
	    int i;
		for(i=0;i<CurrentFill;i++)
		{
			Keys[i]=e[i].key;
			cout<<Keys[i]<<endl;
		 } 
		return Keys;
	}
	
	~Dictonary() // Freeing up the memory used by the object data members
	{	
		
		delete []e;
		delete []Keys;
			
	}	
	
	friend ostream& operator << (ostream &, Dictonary &);// declaring 
	
};

ostream& operator <<(ostream &cout, Dictonary &obj)
{
	int i=0;
	if (obj.holdstring == nullptr)
	{
		for(i;i<obj.CurrentFill;i++)	
		{
			cout<<'"'<<obj.e[i].key<<'"'<<":"<<obj.e[i].value<<","<<" ";
		}
	}
	else{ 		
		for(i;i<obj.CurrentFill;i++)
			{
				
				
				if(obj.e[i].key == obj.holdstring)
					{
						obj.holdstring=nullptr;
						cout<<obj.e[i].value<<endl;
						return cout;
					}
				obj.holdstring=nullptr;
			}
			cout<<"key not found !"<<endl;
		}
	return cout;
}


int main()
{
	Dictonary d;
	// d = 21
	d["Batman2"]= 912;// this will insert the pair in the dictonary
	d.Create_Pair("Robin",943);
	d.Create_Pair("People",69);
	d.Create_Pair("Batman",923); // we could also use Create_Pair Function to create key value pair  
	cout<<d["Robin"]; // it would print the value associate with the key robin
	d["Robin"]=100; // this will update the value of the key Robin 
	d.Delete_Pair("Robin"); // it would delete the pair in which Robin is present.
	d.Delete_Pair("People");
	
	d.keys();//this would print the array of keys present in the d object.
	
	
	/**********************************************************************************************************************
	***********************************************************************************************************************
	***********************************************************************************************************************
	***********************************************************************************************************************
										 The Refrence is Taken From The Dictonary Class In Python.
	*/
	

}
