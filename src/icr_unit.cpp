
// The MIT License (MIT)
//
// Copyright (c) 2016 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string>
#include <sstream>

#include "carb_unit.h"
#include "insulin_unit.h"
#include "icr_unit.h"

namespace ns {
	icr_t::icr_t( carb_t carb ) noexcept:
			value{ std::move( carb ) } { }

	icr_t::~icr_t( ) { }

	std::string icr_t::to_string( ) const {
		std::stringstream ss;
		ss << value << "/U";
		return ss.str( );
	}

	icr_t & icr_t::scale( real_t factor ) noexcept {
		value.scale( factor );
		return *this;
	}

	icr_t icr_t::scale( real_t factor ) const noexcept {
		icr_t result{ *this };
		result.scale( factor );
		return result;
	}

	void swap( icr_t & lhs, icr_t & rhs ) noexcept {
		using std::swap;
		swap( lhs.value, rhs.value );
	}

	std::ostream & operator<<( std::ostream & os, icr_t const & icr ) {
		os << icr.to_string( );
		return os;
	}

	insulin_t operator/( carb_t const & lhs, icr_t const & rhs ) noexcept {
		auto tmp = lhs.value/rhs.value.value;
		insulin_t result;
		result.value = tmp;
		return result;
	}

	carb_t operator*( icr_t const & lhs, insulin_t const & rhs ) noexcept {
		auto tmp = lhs.value.value * rhs.value;
		carb_t result;
		result.value = tmp;
		return result;
	}

	carb_t operator*( insulin_t const & lhs, icr_t const & rhs ) noexcept {
		auto tmp = rhs.value.value * lhs.value;
		carb_t result;
		result.value = tmp;
		return result;
	}

	bool operator==( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value == rhs.value;
	}

	bool operator!=( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value != rhs.value;
	}

	bool operator<( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value < rhs.value;
	}

	bool operator>( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value > rhs.value;
	}

	bool operator<=( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value <= rhs.value;
	}

	bool operator>=( icr_t const & lhs, icr_t const & rhs ) noexcept {
		return lhs.value >= rhs.value;
	}
}    // namespace ns
