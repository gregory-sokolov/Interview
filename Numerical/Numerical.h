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
	/// Calculates closest integer number to the actual square root (using binary search)
	static unsigned Sqrt(unsigned n)
	{
		unsigned min = n > 2 ? 2 : 0, max = n > 5 ? n/2 : n/2 + 1, med = (min + max)/2;
		while (med > min && med < max)
		{
			unsigned square = med*med;
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
		if (n < 0) return NAN;
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return NAN;

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
		if (n < 0) return NAN;
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return NAN;

		double prev = 0.0, mid = n;
		while (std::abs(mid - prev) > p)
		{
			prev = mid;
			mid = (mid + n/mid)/2.0;
		}

		return mid;
	}

	/// Returns k-closest point to the given point.
	/// Uses max-heap algorithm with STL priority_queue.
	/// Time: O(n*log(k)), space: O(k)
	static void GetClosestPoints(unsigned k, std::pair<double, double> origin, const std::vector<std::pair<double, double>>& points,
		std::vector<std::pair<double, double>>& results)
	{
		auto compare = [origin](std::pair<double, double> p1, std::pair<double, double> p2)
		{ 
			// No need to calculate full hypotenuse to economize on sqrt operation
			auto d1 = (p1.first - origin.first)*(p1.first - origin.first) +
				(p1.second - origin.second)*(p1.second - origin.second);
			auto d2 = (p2.first - origin.first)*(p2.first - origin.first) +
				(p2.second - origin.second)*(p2.second - origin.second);
			return d1 < d2;
		};
		std::priority_queue<std::pair<double, double>, std::vector<std::pair<double, double>>, decltype(compare)>
			pq(compare);

		for (auto&& pi : points)
		{
			if (pq.size() < k)
			{
				pq.push(pi);
			}
			else
			{
				if (compare(pi, pq.top()))
				{
					pq.push(pi);
					pq.pop();
				}
			}
		}

		while (!pq.empty())
		{
			results.push_back(pq.top());
			pq.pop();
		}
		std::reverse(results.begin(), results.end());
	}
};
