//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_INPUTSTREAM_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_INPUTSTREAM_H

#include <iosfwd>

namespace xlanger::lex
{
	template<typename _StreamType>
	struct InputStream {
		using StreamType = _StreamType;

		StreamType &operator()() const
		{ return stream; }

		StreamType &stream;
	};

	std::string readChunk(InputStream<std::istream> &stream)
	{
//		char buffer[256];
//
//		stream().getline(buffer, 256);
//
//		return buffer;
		std::string line;
		line.resize(256);

		stream().getline(line.data(), 256);

		return line;
	}
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_INPUTSTREAM_H
