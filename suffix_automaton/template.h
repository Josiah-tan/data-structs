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



template<class T>
bool same(std::vector<std::vector<T>> question, std::vector<std::vector<T>> answer){
	int question_size = question.size(), answer_size = answer.size();
	bool is_same = question_size == answer_size;
	for (int i = 0; i < std::min(question_size, answer_size); i++)
	{
		is_same &= same(question[i], answer[i]);
		if (!is_same) std::cout << "←i " << i << std::endl;
	}
	return is_same;
}


template<class T>
void print(std::vector<T> array){
	for (const auto & character: array){
		std::cout << character << " ";
	}
	std::cout << std::endl;
}

template<class T>
void print(std::vector<std::vector<T>> matrix){
	for (const auto & array: matrix){
		for (const auto & character: array){
			std::cout << character << " ";
		}
		std::cout << std::endl;
	}
}

#endif
