#include "BloomFilter.h"
#include <cstdlib>
#include <iostream>
using namespace std;

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn)
{
	this->k = k;
	this->m = m;
	int size = (m/64)+1; 
	bits = new uint64_t[size];
	//initialize the bits
	for(int i = 0; i < size; i++)
	{
		bits[i] = uint64_t(0);
	}

	//set the strfn
	if(strfn=="pearson")
	{
		this->strfn=new PearsonHash();
	}else if(strfn=="jenkins")
	{
		this->strfn=new JenkinsHash();
	}else
	{
		cerr<<"not valid";
		exit(1);
	}
	//set the intfn
	this->intfns = new IntegerHash*[k];
	if(intfn == "squareroot")
	{
		for(int i = 0; i < k; i++)
		this->intfns[i] = new SquareRootHash(i,m);
	}
	else if(intfn=="reciprocal")
	{
		for(int i = 0; i < k; i++)
		this->intfns[i] = new ReciprocalHash(i,m);
	}
	else if(intfn=="division")
	{
		for(int i = 0; i < k; i++)
		this->intfns[i] = new DivisionHash(i,m);
	}else
	{
		cerr<<"not valid";
		exit(1);
	}
}

BloomFilter::~BloomFilter()
{
	delete strfn;
	for(int i = 0; i < k; i++)
	{
		delete intfns[i];
	}
	delete[] bits;
	delete[] intfns;
}

void BloomFilter::insert(const std::string& value)
{
	uint64_t hash_a = strfn->hash(value);
	for(int j = 0; j < k; j++)
	{
		uint64_t hash_b = intfns[j]->hash(hash_a);
		uint64_t hashIndex = hash_b / 64;
		int ind = hash_b % 64;
		uint64_t o = 1;
		uint64_t fin = (o << ind);
		bits[hashIndex] |= fin;
	}
	
	//uint64_t hashIndex = hash_b/64;
}

bool BloomFilter::lookup(const std::string& value) const
{
	uint64_t hash_a = strfn->hash(value);
	for(int j = 0; j < k; j++)
	{
		uint64_t hash_b = intfns[j]->hash(hash_a);
		int hashIndex = hash_b / 64;
		int ind = hash_b % 64;
		uint64_t at = bits[hashIndex];
		at >>= ind;
		uint64_t o = 1;
		if((o & at)==0)
		{
			return false;
		}

	}
	return true;
}

