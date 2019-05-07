#include "HashSet.h"
#include <cstdlib>
#include <iostream>
using namespace std;

HashSet::HashSet()
{
	nitems = 0;
	nslots = 12;
	intfn = new SquareRootHash(1,nslots);
	strfn = new JenkinsHash();
	//strfn2 = new PearsonHash();
	slots = new string*[nslots];
	for(int k = 0; k < nslots; k++)
	{
		slots[k] = NULL;
	}
}

HashSet::~HashSet()
{
	for(int k = 0; k < nslots; k++)
	{
		if(slots[k] != NULL)
		{
			delete slots[k];
		}
	}
	delete[] slots;
	delete intfn;
	delete strfn;
	//delete strfn2;
}

void HashSet::rehash()
{
	delete intfn;
	int temp = nslots;
	nslots = nslots*2;
	intfn = new DivisionHash(1,nslots);
	string** T = slots;
	slots = new string*[nslots];
	for(int k = 0; k < nslots; k++)
	{
		slots[k] = NULL;
	}
	for(int i = 0; i < temp; i++)
	{
		if(T[i]!= NULL)
		{
			/*string old = *slots[i];
			uint64_t hash_a = strfn->hash(old);
			uint64_t hash_b = intfn->hash(hash_a);
			uint64_t hashIndex = hash_b%n;
			if(lo[hashIndex]==NULL)
			{
				lo[hashIndex]=new string(old);
			}
			else
			{
				uint64_t hash_i = hashIndex;
				while(lo[hash_i]!=NULL)
				{
					hash_i++;
					hash_i = hash_i%n;

				}
				lo[hash_i]=new string(old);
			}*/
			insert(*T[i]);

		}
	}
	for(int i = 0; i < temp;i++)
	{
		if(T[i]!=NULL)
		{
			delete T[i];
		}
	}
	/*
	string** del = slots;
	for(int j = 0; j < nslots;j++)
	{
		delete del[j];
	}
	nslots = n;
	*/
	delete[] T;
	//slots = lo;
	//cout<<nslots;

}

void HashSet::insert(const std::string& value)
{	
	if(lookup(value)){
        return;
    }
	//cout<<nslots<<" "<<nitems<<" ";
	if((nitems / double(nslots)) > 0.4)
	{
		//cout<<"rehash";
		rehash();
	}
	//cout<<"once ";
	//string* a = new string[];
	uint64_t hash_a = strfn->hash(value);
	uint64_t hash_b = intfn->hash(hash_a);
	uint64_t hashIndex = hash_b%nslots;
	nitems+=1;
	/*while(a[hashIndex]!=NULL&&a[hashIndex]!=value)
	{
		hashIndex++;
		hashIndex%nslots;
	}*/
	//int hash_i = hashIndex;
	if(slots[hashIndex]==NULL)
	{
		//nitems++;
		slots[hashIndex]=new string(value);
		return;
	}
	while(slots[hashIndex]!=NULL)
	{
		hashIndex = (hashIndex+1)%nslots;
		//hashIndex = hashIndex%nslots;
	}
	slots[hashIndex] = new string(value);
		//a[hashIndex]=value;
	


}

bool HashSet::lookup(const std::string& value) const
{
	uint64_t hash_a = strfn->hash(value);
	uint64_t hash_b = intfn->hash(hash_a);
	uint64_t hashIndex = hash_b%nslots;

	/*if(slots[hashIndex]==NULL)
	{
		return false;
	}
	if(*slots[hashIndex]==value)
	{
		return true;
	}
	int hash_i = hashIndex;
	while(slots[hash_i]!=LL)
	{
		hash_i++;
		hash_i = hash_i%nslots;
		if(*slots[hash_i]==value)
		{
			return true;
		}
	}*/
	while(slots[hashIndex] != NULL)
	{
        if(*slots[hashIndex] == value){
            return true;
        }
        hashIndex = (hashIndex + 1) % nslots;
    }
	return false;
}
