#include "HashSet.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include "BloomFilter.h"
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int main()
{
	/*HashSet* h = new HashSet();
	for(int i =0; i < 100; i++)
	{
		h->insert(to_string(i));
		cout<<" "<<h->lookup(to_string(i))<<" ";
	}
	*/
	BloomFilter* b = new BloomFilter(3,100,"pearson","reciproval");
	for(int i =0; i < 100; i++)
	{
		b->insert(to_string(i));
		cout<<" "<<b->lookup(to_string(i))<<" ";
	}
	
	return 0;
}