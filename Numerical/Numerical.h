#pragma once

#include <queue>
#include <cmath>
#include <bitset>
#include <algorithm>

///
/// EPI. Chapter 6. Numerical Problems
///
class Numerical
{
public:
	/// EPI 5.6. Convert integer to string
	/// Converts a signed integer to a string.
	/// Code pages store digit characters in a row, so conversion can be done simply by adding digit to '0'.
	static std::string IntToString(const int value)
	{
		std::string result;
		if (value == 0)
		{
			result = "0";
		}
		else
		{
			unsigned int source = value < 0 ? -value : value;
			for (unsigned rmd = source; rmd > 0; rmd /= 10)
			{
				result.push_back('0' + rmd % 10);
			}

			if (value < 0)
			{
				result.push_back('-');
			}
			std::reverse(result.begin(), result.end());
		}

		return result;
	}

	/// EPI 5.6. Convert string to integer
	/// Converts a string to a signed integer.
	/// Uses "delayed sum" trick, where converted digit turns to its actual weight on the next iteration. 
	static int StringToInt(const std::string& value)
	{
		auto result = 0;
		auto negative = value[0] == '-' ? true : false;
		for (unsigned short i = negative ? 1 : 0; i < value.size(); ++i)
		{
			auto digit = value[i] - '0';
			if (digit >= 0 && digit < 10)
			{
				result = result * 10 + digit;
			}
			else
			{
				throw new std::exception("Invalid number format");
			}
		}

		result = negative ? -result : result;
		return result;
	}

	/// EPI 5.7. Base conversion
	/// Converts a number given as string in base1 to the number as string in base2.
	/// Base range is [2; 16], negative numbers are also handled.
	/// Returns an empty string in case of invalid input.
	/// Firstly, converts input base1-value to the decimal system, then to the required system with base2.
	/// This is because all the calculations are performed only with decimal numbers.
	static std::string ConvertBase(const std::string& value, const int base1, const int base2)
	{
		std::string result;
		if (value.empty() || (base1 < 2 || base1 > 16) || (base2 < 2 || base2 > 16))
		{
			return result;
		}
		else if (value == "0")
		{
			return value;
		}

		auto neg = value[0] == '-';
		auto decimal = 0, weight = 1;
		for (int i = value.size() - 1; i >= (neg ? 1 : 0); --i)
		{
			auto digit = value[i] - '0';
			if (digit < 0 || digit > base1 - 1)
			{
				digit = value[i] - 'A' + 10;
				if (digit < 0 || digit > base1 - 1)
				{
					return result;
				}
			}

			decimal += digit*weight;
			weight *= base1;
		}

		for (auto source = decimal; source > 0; source /= base2)
		{
			auto digit = source % base2;
			auto character = digit > 9 ? 'A' + digit - 10 : '0' + digit;
			result.push_back(character);
		}
		
		if (neg && decimal != 0)
		{
			result.push_back('-');
		}
		std::reverse(result.begin(), result.end());

		return result;
	}

	/// EPI 5.8. Spreadsheet column encoding
	/// Converts Excel column ID to the corresponding number.
	/// Column numbering sustem is actually a positional system with base 26.
	static int ExcelColumnId(std::string name)
	{
		const int base = 26;
		int result = 0, weight = 1;
		for (int i = name.size() - 1; i >= 0; --i)
		{
			auto digit = name[i] - 'A' + 1;
			if (digit > 0 && digit < base + 1)
			{
				result += digit*weight;
				weight *= base;
			}
			else
			{
				return -1;
			}
		}

		return result == 0 ? -1 : result;
	}

	/// EPI 5.9. Elias gamma coding
	/// Encodes input array of unsigned integers with Elias code.
	/// Elias coding scheme: convert a value to the binary, count number of bits N, append (N - 1) leading zeros.
	static std::vector<std::string> EliasEncode(const std::vector<unsigned>& input)
	{
		std::vector<std::string> results;
		for (auto it = input.cbegin(); it != input.cend(); ++it)
		{
			if (*it > 0)
			{
				// std::bitset appends all leading zeros
				auto code = std::bitset<32>(*it).to_string();
				code = code.substr(code.find_first_of('1'));
				if (code.size() > 1)
				{
					std::string prefix(code.size() - 1, '0');
					code = prefix + code;
				}
				results.push_back(code);
			}
		}

		return results;
	}
	/// Decodes Elias-coded string
	static std::vector<unsigned> EliasDecode(const std::string& input)
	{
		std::vector<unsigned> results;
		unsigned i = 0, n = 0;
		while (i < input.size())
		{
			if (input[i] == '1')
			{
				auto value = input.substr(i, n + 1);
				results.push_back(std::bitset<32>(value).to_ulong());
				i += n + 1;
				n = 0;
			}
			else
			{
				++i;
				++n;
			}
		}

		return results;
	}

	/// EPI 5.11. Generating primes
	/// Generates n prime numbers.
	/// Optimizations of obvious brute-force algorithm:
	/// - skip even numbers
	/// - look for divisors only in exisiting primes
	/// - stop when prime divisor is greater than square root of the number (max of min divisors)
	/// Sieve of Eratosthenes and its successor, Sieve of Atkin, are used as much faster algorithms for big numbers.
	static std::vector<unsigned> GeneratePrimes(unsigned n)
	{
		std::vector<unsigned> primes;
		for (unsigned i = 3; i <= n; i += 2)
		{
			auto divisable = false;
			unsigned sqrt = (unsigned)std::ceil(std::sqrt(i));
			for (auto it = primes.cbegin(); it != primes.cend(); ++it)
			{
				if (i % *it == 0)
				{
					divisable = true;
					break;
				}
				if (*it > sqrt)
				{
					break;
				}
			}

			if (!divisable)
			{
				primes.push_back(i);
			}
		}

		primes.insert(primes.begin(), { 1, 2 });
		return primes;
	}

	/// EPI 5.10. Greatest common divisor (GCD)
	/// Terms: summand/summand/sum; minuend/sutrahend/difference; multiplier/product; divident/divisor/quotient.
	/// Recursive version with remainders
	static unsigned GcdR(int a, int b)
	{
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;
		return b > 0 ? GcdR(b, a % b) : a;
	}
	/// Iterative version with remainders
	static unsigned GcdRmd(int a, int b)
	{
		if (a == 0 || b == 0)
		{
			return 1;
		}
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;

		int t = 0;
		while (b > 0)
		{
			t = b;
			b = a % b;
			a = t;
		}

		return a;
	}
	/// Iterative version with subtraction (Euclid's algorithm)
	static unsigned GcdSub(int a, int b)
	{
		if (a == 0 || b == 0)
		{
			return 1;
		}
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;

		while (a != b)
		{
			if (a > b)
			{
				a -= b;
			}
			else
			{
				b -= a;
			}
		}

		return a;
	}


	/// EPI 11.9. Computing square roots
	/// Calculates closest integer number to the actual square root (using binary search).
	/// Time: O(log(n))
	static unsigned Sqrt(unsigned n)
	{
		unsigned min = n > 2 ? 2 : 0, max = n > 5 ? n/2 : n/2 + 1, med = (min + max)/2;
		while (med > min && med < max)
		{
			unsigned long long square = ((unsigned long long)med)*((unsigned long long)med);
			if (square > n)
			{
				max = med;
				med = (min + max)/2;
			}
			else if (square < n)
			{
				min = med;
				med = (min + max)/2;
			}
			else
			{
				return med;
			}
		}

		return max*max - n <= n - min*min ? max : min;
	}
	/// Calculates square root of a number using simple binary search.
	/// Time: O(log(n))
	static double Sqrt(double n, double p)
	{
		if (n < 0) return std::numeric_limits<double>::quiet_NaN();
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return std::numeric_limits<double>::quiet_NaN();

		double low = n > 1 ? 1 : 0, high = n < 1 ? 1 : n;
		while (high - low > p)
		{
			double mid = (low + high)/2.0;
			double square = mid*mid;
			if (square > n)
			{
				high = mid;
			}
			else if (square < n)
			{
				low = mid;
			}
			else
			{
				return mid;
			}
		}

		return (high + low)/2.0;
	}
	/// Calculates square root of a number using Newton-Raphson method derived from binary search.
	/// Based on such optimization as updating both bounds together (adding low = n/mid, high = n/mid),
	/// and replacing low/high with mid/prev, since low/high will be the same. 
	/// Time: O (log(p)*F(p)), where F(p) is the cost of division with p-precision.
	/// It takes 8-9 iterations for 15-digit precision (quadratical convergence of the N-R method).
	static double SqrtNewton(double n, double p)
	{
		if (n < 0) return std::numeric_limits<double>::quiet_NaN();
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return std::numeric_limits<double>::quiet_NaN();

		double prev = 0.0, mid = n;
		while (std::abs(mid - prev) > p)
		{
			prev = mid;
			mid = (mid + n/mid)/2.0;
		}

		return mid;
	}

	/// EPI 6.9. Big integer multiplication
	/// School way of long multiplication.
	/// Careful string-integer conversions, reversions and sign handling.
	static std::string MultiplyIntegers(std::string s1, std::string s2)
	{
		if (s1.empty() || s2.empty())
		{
			return std::string();
		}
		if (s1 == "0" || s2 == "0")
		{
			return std::string("0");
		}

		std::string sign = s1[0] == '-' && s2[0] != '-' || s1[0] != '-' && s2[0] == '-' ? "-" : "";
		s1 = s1[0] == '-' ? s1.substr(1, s1.size() - 1) : s1;
		s2 = s2[0] == '-' ? s2.substr(1, s2.size() - 1) : s2;
		
		std::reverse(s1.begin(), s1.end());
		std::reverse(s2.begin(), s2.end());
		std::vector<std::string> muls(s2.size(), std::string(s1.size() + s2.size(), '0'));
		for (unsigned i = 0; i < s2.size(); ++i)
		{
			unsigned d2 = s2[i] - '0';
			unsigned dec = 0;
			for (unsigned j = 0; j < s1.size(); ++j)
			{
				unsigned d1 = s1[j] - '0';
				unsigned mul = d2*d1 + dec;
				unsigned rem = mul%10;
				muls[i][i + j] = rem + '0';
				dec = mul/10;
			}
			if (dec > 0)
			{
				muls[i][s1.size() + i] = dec + '0';
			}
		}

		unsigned dec = 0;
		std::string result(muls[0].size(), '0');
		for (unsigned i = 0; i < muls[0].size(); ++i)
		{
			unsigned ri = dec;
			for (unsigned j = 0; j < muls.size(); ++j)
			{
				ri += muls[j][i] - '0';
			}
			result[i] = (ri % 10) + '0';
			dec = ri / 10;
		}
		std::reverse(result.begin(), result.end());
		result = result[0] == '0' ? result.substr(1, result.size() - 1) : result;
		result = sign + result;

		return result;
	}

	/// Leetcode 238. Product of Array Except Self
	/// Operates with input and output arrays.
	/// Basic case - no zeroes in the array. 
	/// We run two pointers, backward and forward, calculating products in both directions in one pass.
	/// On the second pass we calculate the result: result[i] = forward[i - 1] * backward[i + 1].
	/// Indeed, the product except self is the product of the previous item in forward-processed array and 
	/// the next item in backward-processed one. Carefully handle start and end index in the formula.
	/// Special case - presence of zeroes.
	/// We count zeroes on initial preprocessing pass. The only interesting case is when there's one zero in the array,
	/// then the zero-item is replaced with the except-self product and other items are zeroes. 
	/// When zeroes > 1, all the items become zero because of at least one of them participates in multiplication.
	/// Time: O(n), space: O(n) (or O(1) if output array is not considered as extra space).
	static std::vector<int> ProductExceptSelf(std::vector<int>& input)
	{
		if (input.empty() || input.size() == 1) { return input; }

		unsigned zeroes = 0;
		for (unsigned i = 0; i < input.size(); ++i)
		{
			zeroes += input[i] == 0 ? 1 : 0;
		}
		
		std::vector<int> output;
		if (zeroes == 0)
		{
			output = std::vector<int>(input);
			for (unsigned i = 1; i < input.size(); ++i)
			{
				input[i] = input[i] * input[i - 1];
				output[input.size() - i - 1] = output[input.size() - i - 1] * output[input.size() - i];
			}
			for (unsigned i = 0; i < input.size(); ++i)
			{
				output[i] = (i > 0 ? input[i - 1] : 1) * (i < input.size() - 1 ? output[i + 1] : 1);
			}
		}
		else
		{
			int zeroProd = zeroes == 1 ? 1 : 0;
			unsigned zeroIndex = 0;
			for (unsigned i = 0; i < input.size(); ++i)
			{
				if (input[i] != 0)
				{
					zeroProd *= input[i];
				}
				else
				{
					zeroIndex = i;
				}
				input[i] = 0;
			}
			input[zeroIndex] = zeroProd;
			output = input;
		}

		return output;
	}
};

