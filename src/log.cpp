// Copyright 2020 Sirbu Dan
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sge/log.hpp>
#include <chrono>
#include <time.h>
#include <cassert>
#include <iostream>

namespace
{
	std::tm GetLocalTime()
	{
		std::tm t;

		auto now  = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		#ifdef SGE_UNIX
			localtime_r(&time, &t);
		#elif defined SGE_WIN32
			localtime_s(&t, &time);
		#else
			#error "No safe localtime alternative"
		#endif

		return t;
	}

	const char* GetMtText(sge::Log::MessageType mt)
	{
		switch (mt)
		{
		case sge::Log::MessageType::info:
			return "INF";
			break;
		case sge::Log::MessageType::warning:
			return "WRN";
			break;
		case sge::Log::MessageType::error:
			return "ERR";
			break;
		case sge::Log::MessageType::debug:
			return "DBG";
			break;
		default:
			return "UNK";
			break;
		}
	}
}

namespace sge
{
	Log Log::instance("log.txt");

	Log::Log()
		: mMt(MessageType::info), mWriteTime(false)
	{

	}

	Log::Log(const std::filesystem::path& file)
	{
		Open(file);
	}

	Log::~Log()
	{
		Close();
	}

	Log::Log(Log&& other) noexcept
		: mMt(other.mMt), mWriteTime(other.mWriteTime)
	{
		other.Close();

		mLog = std::move(other.mLog);
	}

	Log& Log::operator=(Log&& other) noexcept
	{
		mMt = other.mMt;
		mWriteTime = other.mWriteTime;

		other.Close();

		mLog = std::move(other.mLog);

		return *this;
	}

	bool Log::Open(const std::filesystem::path& file)
	{
		if (mLog.is_open())
			Close();

		mMt = MessageType::info;
		mLog.open(file, std::ios::out | std::ios::app);
		mWriteTime = true;

		std::tm t = GetLocalTime();
		mLog << "Log started at " << t.tm_mday << "/" << t.tm_mon + 1 << "/" <<
			t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":" <<
			t.tm_sec << std::endl;

		return mLog.is_open();
	}

	void Log::Close()
	{
		if (!mLog.is_open())
			return;

		if (!mWriteTime)
			mLog << std::endl;

		mWriteTime = true;
		mMt = MessageType::info;

		std::tm t = GetLocalTime();
		mLog << "Log ended at " << t.tm_mday << "/" << t.tm_mon + 1 << "/" <<
			t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":" <<
			t.tm_sec << std::endl;

		mLog.close();
	}

	Log& Log::operator<<(MessageType message)
	{
		mMt = message;

		return *this;
	}

	Log& Log::operator<<(bool b)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		if (b)
			mLog << "true";
		else
			mLog << "false";

		return *this;
	}

	Log& Log::operator<<(signed int i)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		mLog << i;

		return *this;
	}

	Log& Log::operator<<(unsigned int i)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		mLog << i;

		return *this;
	}

	Log& Log::operator<<(float f)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		mLog << f;

		return *this;
	}

	Log& Log::operator<<(double d)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		mLog << d;

		return *this;
	}

	Log& Log::operator<<(std::string_view s)
	{
		assert(mLog.is_open());

		if (mWriteTime)
		{
			std::tm t = GetLocalTime();
			mLog << "[" << GetMtText(mMt) << "][" << t.tm_mday << "/" <<
				t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour <<
				":" << t.tm_min << ":" << t.tm_sec << "] ";

			mWriteTime = false;
		}

		mLog << s;

		return *this;
	}

	Log& Log::operator<<(Operation op)
	{
		assert(mLog.is_open());

		if (op == Operation::endl)
		{
			mLog << std::endl;
			mWriteTime = true;
		}

		return *this;
	}
}