#include<algorithm>
#include<iostream>
#include<iomanip>
#include<vector>
#include<random>
#include<chrono>


void naiveSort(std::vector<int> list)
{
	for (int i = 0; i < list.size() - 1; ++i)
	{
		for (int j = i + 1; j < list.size(); ++j)
		{
			if (list[i] > list[j])
			{
				int temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}


void compareSortsForNElements(int N)
{
	//creating a vector of random unsorted integers
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distribution(0, N);

	std::vector<int> nums;
	for (int i = 0; i < N; i++)
	{
		nums.push_back(distribution(rng));
	}


	std::vector<int> copyOfNums = nums; //duplicate vector for Naive sort

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;


	//measuring performance of std::sort
	startTime = std::chrono::high_resolution_clock::now();
	std::sort(nums.begin(), nums.end());
	stopTime = std::chrono::high_resolution_clock::now();
	long long timeInNanosecondsForGoodSort = (stopTime - startTime).count();

	//measuring performance of naive sort
	startTime = std::chrono::high_resolution_clock::now();
	naiveSort(copyOfNums);
	stopTime = std::chrono::high_resolution_clock::now();
	long long timeInNanosecondsForBadSort = (stopTime - startTime).count();


	std::cout << "std::sort took " << std::scientific << std::setprecision(4) << (float)timeInNanosecondsForGoodSort << " to sort a vector of N = " << N << " elements.\n";
	std::cout << "Naive sort took " << std::scientific << std::setprecision(4) << (float)timeInNanosecondsForBadSort << " to sort a vector of N = " << N << " elements.\n";
}



int main()
{

	for (int i : {100, 1'000, 10'000, 100'000})
	{
		std::string line(50, '-');
		std::cout << line << std::endl;
		std::cout << "comparing with N = " << i << " elements...\n";
		compareSortsForNElements(i);
	}

	return 0;
}