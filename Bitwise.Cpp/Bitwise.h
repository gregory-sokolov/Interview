#pragma once

#include <limits>
#include <vector>
#include <algorithm>

/// 
/// EPI. Chapter 5. Bit Manipulation Problems
///
class Bitwise
{
public:
	/// EPI 5.1. Bit count
	/// Simple method to calculate bit count of a number.
	/// Handles of positive and negative 64-bit numbers.
	/// Time: O(n).
	static unsigned short GetBitCountSmp(long long value)
	{
		unsigned short result = 0;
		unsigned short capacity = 8 * (sizeof(long long) / sizeof(char));
		for (unsigned short i = 0; i < capacity; ++i)
		{
			result += (unsigned short)(value & 1LL);
			value >>= 1;
		}

		return result;
	}

	/// EPI 5.1. Bit count
	/// Optimized method to calculate bit count of a number (by Brian Kernighan).
	/// Checks and then clears the lowest set bit until the whole number is zero.
	/// Works faster on inputs with low set bit count.
	/// Time: O(s), s - number of bits set to 1.
	static unsigned short GetBitCountOpt(long long value)
	{
		unsigned short result = 0;
		while (value)
		{
			++result;
			value &= value - 1;
		}

		return result;
	}

	/// EPI 5.1. Bit count
	/// Optimized method using pre-generated lookup table with bit counts.
	/// Takes some time to generate initial table once, most efficient on big data inputs.
	/// Extracting n-th word of the value is constant, as well as accessing an item by index in the lookup vector.
	/// Time: O(w) -> O(1), w - number of 16-bit words in the value.
	static unsigned short GetBitCountTbl(long long value, const std::vector<unsigned short>& table)
	{
		unsigned short result = 0;
		long long shortMax = std::numeric_limits<unsigned short>::max();
		for (unsigned short wi = 0; wi < sizeof(long long)/sizeof(unsigned short); ++wi)
		{
			auto word = (unsigned short)((value >> wi * 16) & shortMax);
			result += table[word];
		}

		return result;
	}
	/// Helper function to generate bit count table for a 16-bit word
	static void GenerateWordTable(std::vector<unsigned short>& table)
	{
		for (unsigned short i = 0; i < std::numeric_limits<unsigned short>::max(); ++i)
		{
			table.push_back(GetBitCountOpt(i));
		}
		table.push_back(GetBitCountOpt(std::numeric_limits<unsigned short>::max()));
	}

	/// EPI 5.2. Swap bits
	/// Swaps bits i and j in 64-bit value.
	/// If specified bits really needed to be swapped, just invert them.
	/// To invert a bit, XOR the value with 1-bitmask.
	/// Time: O(1), if shift(n) operation is performed in one clock. 
	static long long SwapBits(long long value, unsigned short i, unsigned short j)
	{
		auto result = value;
		auto capacity = 8*(sizeof(long long)/sizeof(char));
		if (i < capacity - 1 && j < capacity - 1 && i != j)
		{
			if (((value >> i) & 1LL) != ((value >> j) & 1LL))
			{
				result = value ^ (1LL << i | 1LL << j);
			}
		}

		return result;
	}

	/// EPI 5.3. Reverse bits
	/// Reverses bit order in 16-bit value.
	/// Could be easily replaced with 64-bit or made a template.
	/// Could be optimized with pre-generated lookup table like in GetBitCountTbl().
	/// Uses the same technique as in SwapBits(), swapping bits from both sides of the value.
	/// Time: O(n/2). 
	static unsigned short ReverseBits(unsigned short value)
	{
		auto result = value;
		unsigned short capacity = 8 * (sizeof(unsigned short) / sizeof(char));
		for (unsigned short i = 0, j = capacity - 1; i < j; ++i, --j)
		{
			unsigned short vi = (value >> i) & 1;
			unsigned short vj = (value >> j) & 1;
			if (vi != vj)
			{
				result ^= (1 << i | 1 << j);
			}
		}

		return result;
	}

	/// EPI 5.5. The power set
	/// Generates the power set of an input set.
	/// Input set size is limited to the ullong capacity (64 bits).
	/// In C++11, the returned vector will be handled by either RVO or its move constructor.
	/// Time: O(2^n), since that is the total number of subsets to generate.
	static std::vector<std::vector<std::string>> GenereatePowerSet(const std::vector<std::string>& input)
	{
		std::vector<std::vector<std::string>> results;
		std::vector<std::string> empty{ "-0-" };
		results.push_back(empty);

		auto power = 1 << input.size();
		for (unsigned long long n = 1; n < power; ++n)
		{
			auto indexes = GetSetBitIndexes(n);
			std::vector<std::string> subset;
			for (auto idx : indexes)
			{
				subset.push_back(input[idx]);
				
			}
			results.push_back(subset);
		}

		return results;
	}
	/// Helper function to get indexes of set bits of a number
	static std::vector<unsigned short> GetSetBitIndexes(unsigned long long value)
	{
		std::vector<unsigned short> results;
		auto shifted = value;
		for (unsigned short i = 0; shifted > 0; ++i)
		{
			if ((shifted & 1LL) > 0)
			{
				results.push_back(i);
			}
			shifted >>= 1;
		}

		return results;
	}
};