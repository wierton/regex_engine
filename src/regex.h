#ifndef REGEX_H
#define REGEX_H

/* concat, alter, closure */

struct Epsilon {
	template<class Next>
	static constexpr bool match(const char *s, Next next) {
		return next(s);
	}
};

template<char v>
struct Atom {
	template<class Next>
	static constexpr bool match(const char *s, Next next) {
		return *s == v && next(s + 1);
	}
};

template<class T, class U>
struct Concat {
	template<class Next>
	static constexpr bool match(const char *s, Next next) {
		auto relay = [&next] (const char *s) -> bool {
			return U::match(s, next);
		};
		return T::match(s, relay);
	}
};

template<class T, class U>
struct Alter {
	template<class Next>
	static constexpr bool match(const char *s, Next next) {
		return T::match(s, next) || U::match(s, next);
	}
};

template<class T>
struct Closure {
	template<class Next>
	static constexpr bool match(const char *s, Next next) {
		auto relay = [&next] (const char *s) -> bool {
			return Closure<T>::match(s, next);
		};
		return T::match(s, relay) || next(s);
	}
};


template<class T>
struct Match {
	static constexpr bool apply(const char *s) {
		auto eof = [](const char *s) -> bool {
			return *s == '\0';
		};
		return T::match(s, eof);
	}
};


#endif
