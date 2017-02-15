#pragma once

#ifndef PIECE_SERIALIZER_HPP
#define PIECE_SERIALIZER_HPP

#include "piece.hpp"

#include <functional>

class piece_serializer {
public:
	using serializertype = std::function<piece*(const unsigned char* data, size_t size)>;
	
	template<typename T>
	static void register_piece(std::string name, serializertype serializer) {
		
	}
	
private:
	
	static std::unordered_map<std::string, serializertype> 
};

#endif // PIECE_SERIALIZER_HPP
