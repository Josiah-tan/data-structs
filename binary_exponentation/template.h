#ifndef TEMPLATE_H
#define TEMPLATE_H

#include<vector>
#include<iostream>

void helloWorld(void);

template<class T>
bool same(std::vector<T> question, std::vector<T> answer){
	int question_size = question.size(), answer_size = answer.size();
	bool same = question_size == answer_size;
	for (int i = 0; i < std::min(question_size, answer_size); i++)
	{
		same &= question[i] == answer[i];
	}
	if (!same){
		std::cout << "Q: ";
		for (int i = 0; i < question_size; i++)
		{
			std::cout << question[i] << ' ';
		}
		std::cout << "\nA: ";
		for (int i = 0; i < answer_size; i++)
		{
			std::cout << answer[i] << ' ';
		}
		std::cout << std::endl;
	}
	return same;
}



#endif
