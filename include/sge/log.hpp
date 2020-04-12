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

#ifndef __SGE_LOG_HPP__
#define __SGE_LOG_HPP__

#include <sge/export.hpp>
#include <fstream>
#include <filesystem>
#include <string_view>

namespace sge
{
	class SGE_API Log
	{
	public:

		enum class SGE_API MessageType
		{
			info,
			warning,
			error,
			debug
		};

		enum class SGE_API Operation
		{
			endl
		};

	public:

		static Log instance;

	public:

		Log();

		Log(const std::filesystem::path& file);

		~Log();

		Log(const Log&) = delete;

		Log(Log&& other) noexcept;

		Log& operator=(const Log&) = delete;

		Log& operator=(Log&& other) noexcept;

		bool Open(const std::filesystem::path& file);

		void Close();

		Log& operator<<(MessageType message);

		Log& operator<<(bool b);

		Log& operator<<(signed int i);

		Log& operator<<(unsigned int i);

		Log& operator<<(float f);

		Log& operator<<(double d);

		Log& operator<<(std::string_view s);

		Log& operator<<(Operation op);

	private:

		MessageType mMt;

		std::ofstream mLog;

		bool mWriteTime;

	};
}

#endif // !__SGE_LOG_HPP__
