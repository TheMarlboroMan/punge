#pragma once
#include <string>
#include <istream>
#include <vector>

namespace tools {

/**
 * this class takes an input stream and outputs a string or vector with the 
 * same contents but with the max line width indicated. Words will be split in
 * the middle with no regard to its meaning or punctuation rules.
 */
class line_width_format {

	public:

/**
 * converts a stream to a vector of lines. Each line is a line of the original
 * stream split to the given max_width. If zero is given the whole line will be
 * given.
 * The stream read head must be set where the reading must start (e.g. at the
 * beginning). The stream head will be moved during this operation until eof
 * is reached, thus must be reset if reused.
 */
	std::vector<std::string>    stream_to_vector(std::istream&, std::size_t=0);
/**
 * converts a stream to a string following the rules of stream_to_vector.
 */
	std::string                 stream_to_string(std::istream&, std::size_t=0);
};
}

