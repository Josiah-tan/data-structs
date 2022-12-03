#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

class Hello
{
	private:
		unsigned int a;
	public:
		Hello(unsigned int a) : a(a){}
		void print(){
			cout << a << endl;
		}
		static Hello make(unsigned int a){
			return  Hello(a);
		}
		void change(){
			a++;
		}

};

void hello(const Hello* hello)
{
	hello->change();
}
int main(void){
	// helloWorld();
	// helloWorld(a="10");
	// Hello hello = Hello(5);
	Hello buy = Hello(5);
	buy.print();
	hello(&buy);
}

