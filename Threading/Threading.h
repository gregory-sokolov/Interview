#pragma once

#include <utility>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

///
/// Multithreading Problems
///

class Threading
{
public:
	///
	/// Buddy chat question
	///
	class BuddyChat
	{
	private:
		std::mutex _mx;
		std::condition_variable _cv;

	public:
		class Buddy
		{
			std::string _name;
			std::string _message;

		public:
			Buddy(const std::string& name) : _name(name) {}

			void say(const std::string& message)
			{
				_message = message;
				std::cout << _name << ": " << message << std::endl;
			}

			bool said_something() const { return !_message.empty(); }

			std::string listen()
			{
				std::string message = _message;
				_message.clear();
				return message;
			}
		};

		void Talk(Buddy& me, Buddy& other, const std::initializer_list<std::string>& speech)
		{
			for (const auto& phrase : speech)
			{
				// Replacing sleep with cond_var
				//while (!other.said_something())
				//{
				//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
				//}
				std::unique_lock<std::mutex> ulk(_mx);
				_cv.wait(ulk, [&] { return other.said_something(); });
				other.listen();

				me.say(phrase);
				ulk.unlock();
				_cv.notify_one();
			}
		}
	};
	
};

