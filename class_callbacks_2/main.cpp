#include<vector>
#include"template.h"
#include<iostream>
#include<climits>
#include<string>

using namespace std;

class Language
{
	public:
		Language(std::string language): language(language){}
		
		virtual void callback(int& a) = 0;
		
		std::string getLanguage(){
			return language;
		}
	private:
		std::string language;
	// protected:
	// 	std::vector<int> a;
};

class Spanish: public Language
{
	public:
		Spanish(): Language("Spanish") {}
		void callback(int& a){
			// for (unsigned int i = 0; i < a.size(); i++){
			// 	cout << a[i] + 1 << " ";
			// }
			// cout << std::endl;
			std::cout << "I don't know the Spanish one" << std::endl;
		}
};

class English: public Language
{
	public:
		English(): Language("English") {}
		void callback(int& a){
			// for (unsigned int i = 0; i < a.size(); i++){
			// 	cout << a[i]<< " ";
			// }
			// cout << std::endl;
			a+=1;
			std::cout << "hello world" << std::endl;
		}
};

class Hello
{
	private:
		int a;
	public:
		Hello(){
			a=5;
		}
		void hello(){
			English english;
			Spanish spanish;
			vector<Language*> languages;
			languages.push_back(&english);
			languages.push_back(&spanish);

			for (unsigned int i = 0; i < languages.size(); i++){
				std::cout << "running" << languages[i]->getLanguage();
				languages[i]->callback(a);
			}
			std::cout << a << std::endl;
		}
};

int main(void){

	// std::vector<int> a(5, 1);
	// Hello hello(a);
	Hello hello;
	hello.hello();
} 
