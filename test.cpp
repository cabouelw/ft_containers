#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include "containers/Vector.hpp"
#include "containers/Stack.hpp"
#include "containers/Reverse_iterator.hpp"
#include "containers/Pair.hpp"
#include "containers/avl_tree.hpp"
#include "containers/Map.hpp"
#include <map>


int main()
{

	std::map<int, int> test;
	// std::map<int, int> test1;
	test[1] = 1337;
	test[2] = 1338;
	test[3] = 1339;
	test[4] = 1340;
	test[5] = 1341;

	// std::map<int, int>::iterator it = test.find(1);
		std::cout << test.count(54) << "\n";
	// std::map<int, int>::iterator it1 = test.end();
	// while (it != it1)
	// {
	// 	std::cout << (*it).first << "|" << (*it).second << "\n";
	// 	it++;
	// }

	// test.insert()

	// ft::avltree<ft::pair<int, int>, std::less<int>, std::allocator<int> > test;
	// ft::avltree<int, std::less<int>, std::allocator<int> > test;
	// test1.print();
	
	// test.insert(1);
	// test.insert(2);
	// test.insert(3);
	// test.insert(4);
	// test.insert(5);
	// test.remove(5);
	// test.print();
	/*
{
	std::vector<int> vector(10, 2);
	std::vector<int> vector1;

	vector1.swap(vector);
	if (vector.empty() && !vector.empty())
		std::cout << "Good\n";
	else
		std::cout << "emty function: " << ((!vector.empty()) ? "vector1" : "vector") << " is Not working\n";
	vector.reserve(3);
	vector.push_back(3);
	vector.push_back(3);
	vector.push_back(3);
	vector1.resize(9);
	std::cout << "vector1:";
	for (std::vector<int>::iterator i = vector1.begin(); i != vector1.end(); i++)
		std::cout << "|" << *i;
	std::cout << "|\n" << "max_size=" << vector1.max_size() << "|capacty=" << vector1.capacity() << "|size=" << vector1.size() << "\n";
	std::cout << "vector:";
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "|" << vector[i];
	std::cout << "|\n" << "max_size=" << vector.max_size() << "|capacty=" << vector.capacity() << "|size=" << vector.size() << "\n";

	vector1.assign(vector.begin(), vector.begin() + 2);
	vector1.assign(3, 5);

	vector1.pop_back();
	vector.insert(vector.begin(), 0);
	vector.insert(vector.begin() + 1, 1, 1);
	vector.insert(vector.end() - 2, vector1.begin(), vector1.begin() + 2);
	std::cout << "vector1:";
	for (std::vector<int>::iterator i = vector1.begin(); i != vector1.end(); i++)
		std::cout << "|" << *i;
	std::cout << "|\n" << "max_size=" << vector1.max_size() << "|capacty=" << vector1.capacity() << "|size=" << vector1.size() << "\n";
	std::cout << "vector:";
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "|" << vector[i];
	std::cout << "|\n" << "max_size=" << vector.max_size() << "|capacty=" << vector.capacity() << "|size=" << vector.size() << "\n";
	vector1.clear();
}
	// std::cout << '\n' << "size=" << myvector.size() << "|cap=" << myvector.capacity() << "\n\n";
	std::cout << "\n\n\n";

	ft::vector<int> vector((size_t)10, 2);
	ft::vector<int> vector1;

	vector1.swap(vector);
	if (vector.empty() && !vector.empty())
		std::cout << "Good\n";
	else
		std::cout << "emty function: " << ((!vector.empty()) ? "vector1" : "vector") << " is Not working\n";
	vector.reserve(3);
	vector.push_back(3);
	vector.push_back(3);
	vector.push_back(3);
	vector1.resize(9);
	std::cout << "vector1:";
	for (ft::vector<int>::iterator i = vector1.begin(); i != vector1.end(); i++)
		std::cout << "|" << *i;
	std::cout << "|\n" << "max_size=" << vector1.max_size() << "|capacty=" << vector1.capacity() << "|size=" << vector1.size() << "\n";
	std::cout << "vector:";
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "|" << vector[i];
	std::cout << "|\n" << "max_size=" << vector.max_size() << "|capacty=" << vector.capacity() << "|size=" << vector.size() << "\n";

	vector1.assign(vector.begin(), vector.begin() + 2);
	vector1.assign((size_t)3, 5);

	vector1.pop_back();
	vector.insert(vector.begin(), 0);
	vector.insert(vector.begin() + 1, (size_t)1, 1);
	vector.insert(vector.end() - 2, vector1.begin(), vector1.begin() + 2);
	std::cout << "vector1:";
	for (ft::vector<int>::iterator i = vector1.begin(); i != vector1.end(); i++)
		std::cout << "|" << *i;
	std::cout << "|\n" << "max_size=" << vector1.max_size() << "|capacty=" << vector1.capacity() << "|size=" << vector1.size() << "\n";
	std::cout << "vector:";
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "|" << vector[i];
	std::cout << "|\n" << "max_size=" << vector.max_size() << "|capacty=" << vector.capacity() << "|size=" << vector.size() << "\n";
	vector1.clear();
	
	{
		std::vector<int> tmp;
		tmp.insert(tmp.begin(), 3, 42);
		tmp.insert(tmp.begin() + 1, (size_t)1, 1);
		tmp.insert(tmp.end() - 2, tmp.begin(), tmp.begin() + 2);
		for (size_t i = 0; i < tmp.size(); i++)
			std::cout << "|" << tmp[i];
		std::cout << "\n" << "max_size=" << tmp.max_size() << "|capacty=" << tmp.capacity() << "|size=" << tmp.size() << "\n";;
	}
	ft::vector<int> tmp;
	tmp.insert(tmp.begin(), (size_t)3, 42);
	tmp.insert(tmp.begin() + 1, (size_t)1, 1);
	tmp.insert(tmp.end() - 2, tmp.begin(), tmp.begin() + 2);
	for (size_t i = 0; i < tmp.size(); i++)
		std::cout << "|" << tmp[i];
	std::cout << "\n" << "max_size=" << tmp.max_size() << "|capacty=" << tmp.capacity() << "|size=" << tmp.size() << "\n";;
	*/
	return 0;
}