#include"template.h"
#include<queue>
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;


class Hello
{
	public:
	virtual ~Hello()
	{
		cout << "destructor hello" << endl;
	}
};

class Bye: public Hello
{
	public:
	// ~Bye()
	// {
	// 	cout << "destructor Bye" << endl;
	// }
};

int main(void){
	Hello hello = Hello();
	Hello* bye = new Bye();
	delete bye;
	// Bye bye();
	queue<Hello*> indeed;
	for (unsigned int i = 0; i < 5; i++)
	{
		indeed.push(new Bye());
	}
	for (unsigned int i = 0; i < 5; i++)
	{
		Hello* yolo = indeed.front();
		indeed.pop();
		delete yolo;
	}
}

