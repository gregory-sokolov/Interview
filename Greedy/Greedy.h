#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

///
/// Greedy Method Problems
///
class Greedy
{
public:
	/// EPI 15.22.1. Scheduling tutors
	/// This is a variation of classic interval scheduling problem, solved by greedy method.
	/// We build a pool of tutors "greedily", either reusing existing free tutors within their capacity time, 
	/// or adding a new tutor when no free/unexpired ones are available. Expired tutors are not removed from the pool
	/// as they are safely excluded from selection by the end of duty time. As a result, total pool size 
	/// after the processing is the least number of tutors required to serve the requests.
	/// Time: O(n log(n)) + O(n) = O(n log(n)), space: O(1)
	struct Tutor
	{
		double eor; // End of request
		double eod; // End of duty
	};
	static std::list<Tutor> ScheduleTutors(std::vector<std::pair<double, double>>& requests, const double capacity)
	{
		bool result = false;

		std::sort(requests.begin(), requests.end(),
			[](std::pair<double, double>& p1, std::pair<double, double>& p2) { return p1.second < p2.second; });

		std::list<Tutor> tutorPool = { { requests.cbegin()->second, requests.cbegin()->first + capacity } };
		for (auto ri = requests.cbegin() + 1; ri < requests.cend(); ++ri)
		{
			bool found = false;
			for (auto& tp : tutorPool)
			{
				if (ri->first >= tp.eor && ri->second <= tp.eod)
				{
					tp.eor = ri->second;
					found = true;
					break;
				}
			}

			if (!found)
			{
				tutorPool.push_back({ ri->second, ri->first + capacity });
			}
		}

		return tutorPool;
	}

	/// EPI 15.22.2. Coin change
	/// Solving change-making problem by greedy method.
	static std::vector<std::pair<unsigned, unsigned>> CoinChangeGreedy(std::vector<unsigned>& coinage, const unsigned amount)
	{
		std::vector<std::pair<unsigned, unsigned>> result = {};
		std::sort(coinage.begin(), coinage.end(), std::greater<unsigned>());
		for (unsigned i = 0, remainder = amount; i < coinage.size(); ++i)
		{
			unsigned count = 0;
			for (unsigned subsum = coinage[i]; subsum <= remainder; subsum += coinage[i], ++count) {}
			result.push_back(std::make_pair(coinage[i], count));
			remainder -= count * coinage[i];
		}

		return result;
	}

	/// EPI 15.26. Huffman Coding
	/// Returns Huffman codes for the provided alphabet with known character frequencies.
	/// Huffman codes are prefix codes: no code word is a prefix of another.
	/// We build the prefix code tree out of existing character frequencies:
	/// - place all the pairs freq-char into the min-heap by frequency
	/// - take two minimum frequencies repeatedly as heap tops
	/// - sum them up, sum up also the symbols into a new string
	/// - append code bit '0' to the all the characters from the first node (left edge), '1' - from the second one (right edge) 
	/// - add new node with the frequency and character sum to the heap
	/// - repeat until the heap root is reached
	/// Below is a modififed classical solution that removes top node once per iteration to avoid code duplication, 
	/// tracks minimums in a small double-item vector, appending the bit digit to the corresponding symbols in code cache,
	/// and then switching the bit for the next heap node. Resulting codes are accumulated per character in the map.
	/// Time: O(n log(n)), space: 3n (input, heap, codes) -> O(n)
	static std::map<char, std::string> HuffmanCoding(const std::vector<std::pair<char, double>>& char_freq)
	{
		std::map<char, std::string> results;

		auto compare = [](const std::pair<std::string, double>& p1, const std::pair<std::string, double>& p2)
		{
			return p1.second > p2.second;
		};
		std::priority_queue<std::pair<std::string, double>, std::vector<std::pair<std::string, double>>, decltype(compare)>
			min_heap(compare);
		for (const auto& cfi : char_freq)
		{
			min_heap.push(std::make_pair(std::string(1, cfi.first), cfi.second));
			results[cfi.first] = "";
		}

		bool bit = false;
		std::vector<std::pair<std::string, double>> mins;
		while (!min_heap.empty())
		{
			mins.push_back(min_heap.top());
			min_heap.pop();
			if (!min_heap.empty() || mins.size() > 1 || char_freq.size() == 1)
			{
				for (const auto& ch : mins.back().first)
				{
					results[ch] = std::to_string((int)bit) + results[ch];
				}
			}

			if (mins.size() > 1)
			{
				auto sum = std::make_pair(mins.front().first + mins.back().first, mins.front().second + mins.back().second);
				min_heap.push(sum);
				mins.clear();
			}

			bit = !bit;
		}

		return results;
	}
};

