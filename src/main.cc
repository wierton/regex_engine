#include "regex.h"


void test_match() {
	static_assert(Match<Epsilon>::apply(""), "");
	static_assert(!Match<Epsilon>::apply("0"), "");

	static_assert(Match<Atom<'a'>>::apply("a"), "");
	static_assert(!Match<Atom<'a'>>::apply("b"), "");

	static_assert(Match<Concat<Atom<'a'>, Atom<'b'>>>::apply("ab"), "");
	static_assert(!Match<Concat<Atom<'a'>, Atom<'b'>>>::apply("abc"), "");
	static_assert(!Match<Concat<Atom<'a'>, Atom<'b'>>>::apply("bc"), "");

	static_assert(Match<Alter<Atom<'a'>, Atom<'b'>>>::apply("a"), "");
	static_assert(Match<Alter<Atom<'a'>, Atom<'b'>>>::apply("b"), "");
	static_assert(!Match<Alter<Atom<'a'>, Atom<'b'>>>::apply("c"), "");

	static_assert(Match<Closure<Atom<'a'>>>::apply(""), "");
	static_assert(Match<Closure<Atom<'a'>>>::apply("a"), "");
	static_assert(Match<Closure<Atom<'a'>>>::apply("aa"), "");
	static_assert(Match<Closure<Atom<'a'>>>::apply("aaa"), "");

	// (a|b|cd)* match abcdabcd
	
	static_assert(Match<
				Closure<
					Alter<
						Atom<'a'>,
						Alter<
							Atom<'b'>,
							Concat<
								Atom<'c'>,
								Atom<'d'>
							>
						>
					>
				>
			>::apply("abcdabcd"), "");
}

int main() {
	return 0;
}
