#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

class Bye
{
	public:
		~Bye(){
			cout << "hello world" << endl;
		}
		Bye(int bye): bye(bye){
		}
	private:
		int bye;
};

class Hello
{
	public:
		enum Days{Friday, Saturday, Sunday};
		void getDay(Days days)
		{
			cout << days << endl;
		}
		
		// Hello()
		// {
		// bye = Bye(9);
		// }
		Hello(): bye(0)
		{}
		
	private:
		 Bye bye;
};

int main(void){
	// helloWorld();
	Hello hello;
	hello.getDay(Hello::Friday);
	hello.getDay(Hello::Saturday);
	hello.getDay(Hello::Sunday);
}

