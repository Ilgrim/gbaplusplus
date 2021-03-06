#ifndef GBAXX_MAT3X2_HPP
#define GBAXX_MAT3X2_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/vec2.hpp>
#include <gba/vec3.hpp>

namespace gba {

template <typename MType, typename VType = MType>
struct mat3x2 {
	using size_type = uint32;
	using matrix_type = MType;
	using vector_type = VType;
	using type = mat3x2<MType, VType>;

	vec2<MType>	ab;
	vec2<MType>	cd;
	vec2<VType>	xy;

	constexpr mat3x2() noexcept : ab( { 1, 0 } ), cd( { 0, 1 } ), xy() {}

	template <typename M, typename V>
	constexpr mat3x2( const mat3x2<M, V>& other ) noexcept : ab( other.ab ), cd( other.cd ), xy( other.xy ) {}

	template <typename S>
	constexpr mat3x2( S scalar ) noexcept : ab( { scalar, 0 } ), cd( { 0, scalar } ), xy( { 0, 0 } ) {}

	template <typename A, typename B, typename C, typename D, typename X, typename Y>
	constexpr mat3x2( A a, B b, C c, D d, X x, Y y ) noexcept : 
		ab( { a, b } ),
		cd( { c, d } ),
		xy( { x, y } ) {}

	template <typename V0, typename V1, typename V2>
	constexpr mat3x2( const vec2<V0>& v0, const vec2<V1>& v1, const vec2<V2>& v2 ) noexcept : 
		ab( v0 ),
		cd( v1 ),
		xy( v2 ) {}

	template <typename OMType, typename OVType>
	constexpr auto& operator =( const mat3x2<OMType, OVType>& other ) noexcept {
		ab = other.ab;
		cd = other.cd;
		xy = other.xy;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( OType scalar ) noexcept {
		ab += scalar;
		cd += scalar;
		xy += scalar;
		return *this;
	}

	template <typename OMType, typename OVType>
	constexpr auto& operator +=( const mat3x2<OMType, OVType>& other ) noexcept {
		ab += other.ab;
		cd += other.cd;
		xy += other.xy;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( OType scalar ) noexcept {
		ab -= scalar;
		cd -= scalar;
		xy -= scalar;
		return *this;
	}

	template <typename OMType, typename OVType>
	constexpr auto& operator -=( const mat3x2<OMType, OVType>& other ) noexcept {
		ab -= other.ab;
		cd -= other.cd;
		xy -= other.xy;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( OType scalar ) noexcept {
		ab *= scalar;
		cd *= scalar;
		xy *= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( OType scalar ) noexcept {
		ab /= scalar;
		cd /= scalar;
		xy /= scalar;
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++ab;
		++cd;
		++xy;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--ab;
		--cd;
		--xy;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++ab;
		++cd;
		++xy;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--ab;
		--cd;
		--xy;
		return r;
	}
};

template <typename MType, typename VType>
constexpr const auto& operator +( const mat3x2<MType, VType>& m ) noexcept {
	return m;
}

template <typename MType, typename VType>
constexpr auto operator -( const mat3x2<MType, VType>& m ) noexcept {
	return mat3x2<MType, VType>( -m.ab, -m.cd, -m.xy );
}

template <typename MType, typename VType, typename S>
constexpr auto operator +( const mat3x2<MType, VType>& m, S s ) noexcept {
	return mat3x2<MType, VType>( m.ab + s, m.cd + s, m.xy + s );
}

template <typename AM, typename AV, typename BM, typename BV>
constexpr auto operator +( const mat3x2<AM, AV>& a, const mat3x2<BM, BV>& b ) noexcept {
	return mat3x2<AM, AV>( a.ab + b.ab, a.cd + b.cd, a.xy + b.xy );
}

template <typename MType, typename VType, typename S>
constexpr auto operator -( const mat3x2<MType, VType>& m, S s ) noexcept {
	return mat3x2<MType, VType>( m.ab - s, m.cd - s, m.xy - s );
}

template <typename AM, typename AV, typename BM, typename BV>
constexpr auto operator -( const mat3x2<AM, AV>& a, const mat3x2<BM, BV>& b ) noexcept {
	return mat3x2<AM, AV>( a.ab - b.ab, a.cd - b.cd, a.xy - b.xy );
}

template <typename MType, typename VType, typename S>
constexpr auto operator *( const mat3x2<MType, VType>& m, S s ) noexcept {
	return mat3x2<MType, VType>( m.ab * s, m.cd * s, m.xy * s );
}

template <typename S, typename MType, typename VType>
constexpr auto operator *( S s, const mat3x2<MType, VType>& m ) noexcept {
	return mat3x2<MType, VType>( m.ab * s, m.cd * s, m.xy * s );
}

template <typename MType, typename VType>
constexpr auto operator *( const mat3x2<MType, VType>& m, const vec3<VType>& v ) noexcept {
	return vec2<VType>(
		m.ab.x * v.x + m.cd.x * v.y + m.xy.x * v.z,
		m.ab.y * v.x + m.cd.y * v.y + m.xy.y * v.z);
}

template <typename MType, typename VType>
constexpr auto operator *( const vec2<VType>& v, const mat3x2<MType, VType>& m ) noexcept {
	return vec3<VType>(
		v.x * m.ab.x + v.y * m.ab.y,
		v.x * m.cd.x + v.y * m.cd.y,
		v.x * m.xy.x + v.y * m.xy.y);
}

template <typename AM, typename AV, typename BM, typename BV>
constexpr auto operator *( const mat3x2<AM, AV>& m1, const mat3x2<BM, BV>& m2 ) noexcept {
	return mat3x2<AM, AV>(
		m1.ab.x * m2.ab.x + m1.cd.x * m2.ab.y /*+ m1.xy.x * m2.ab.z*/,
		m1.ab.y * m2.ab.x + m1.cd.y * m2.ab.y /*+ m1.xy.y * m2.ab.z*/,
		m1.ab.x * m2.cd.x + m1.cd.x * m2.cd.y /*+ m1.xy.x * m2.cd.z*/,
		m1.ab.y * m2.cd.x + m1.cd.y * m2.cd.y /*+ m1.xy.y * m2.cd.z*/,
		m1.ab.x * m2.xy.x + m1.cd.x * m2.xy.y + m1.xy.x /** m2.xy.z*/,
		m1.ab.y * m2.xy.x + m1.cd.y * m2.xy.y + m1.xy.y /** m2.xy.z*/);
}

template <typename MType, typename VType, typename S>
constexpr auto operator /( const mat3x2<MType, VType>& m, S s ) noexcept {
	return mat3x2<MType, VType>( m.ab / s, m.cd / s, m.xy / s );
}

template <typename S, typename MType, typename VType>
constexpr auto operator /( S s, const mat3x2<MType, VType>& m ) noexcept {
	return mat3x2<MType, VType>( s / m.ab, s / m.cd, s / m.xy );
}

template <typename AM, typename AV, typename BM, typename BV>
constexpr auto operator ==( const mat3x2<AM, AV>& m1, const mat3x2<BM, BV>& m2 ) noexcept {
	return m1.ab == m2.ab && m1.cd == m2.cd && m1.xy == m2.xy;
}

template <typename AM, typename AV, typename BM, typename BV>
constexpr auto operator !=( const mat3x2<AM, AV>& m1, const mat3x2<BM, BV>& m2 ) noexcept {
	return !( m1 == m2 );
}

} // gba

#endif // define GBAXX_MAT3X2_HPP
