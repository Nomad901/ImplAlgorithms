#include <iostream>
#include <vector>
#include <concepts>

// mostly was taken from this talk:
// https://youtu.be/4IUCBx5fIv0?si=EUUdvwu3yaG4F7bR 

template<typename src_type>
concept isAccesible = requires(const src_type& pType)
{
	pType[0];
};

class tridiagonal
{
public:
	tridiagonal() = default;

	template<typename src_type>
		requires isAccesible<src_type>
	tridiagonal& operator=(const src_type& pType)
	{
		const size_t I = mStorage.size();
		for (size_t i = 0; i < I; ++i)
		{
			mStorage[i] = pType[i]; 
		}
		return *this;
	}
	
private:
	std::vector<double> mStorage;
};

template<typename operand>
auto subscript(const operand& pStorage, const size_t& pIndex)
{
	if constexpr (requires { pStorage[pIndex]; })
		return pStorage[pIndex];
	return pStorage;
}

template<typename callable, typename... operands>
class expr
{
public:
	expr(callable pFunc, const operands&&... pArgs)
		: mFunc(pFunc), mArgs(pArgs)
	{ }

	auto operator[](const size_t pIndex) const
	{
		const auto call_at_index = [this, pIndex](const operands&... pArgs)
			{
				return mFunc(subscript(pArgs, pIndex)...);
			};
		return std::apply(call_at_index, mArgs);
	}

private:
	callable mFunc;
	std::tuple<const operands&&...> mArgs;
};


template<typename LHS, typename RHS>
concept isBinaryOp = requires(const LHS & pLeft, const RHS & pRight)
{
	pLeft + pRight;
};

template<typename LHS, typename RHS>
	requires isBinaryOp<LHS, RHS>
auto operator*(const LHS& pLeft, const RHS& pRight)
{
	return expr
	{
		[](const auto& l, const auto& r) { return l * r; },
		pLeft, pRight
	};
}

int main()
{
	tridiagonal first, second;
	first  = std::vector<double>({ 1,2,3,4,5 });
	second = std::vector<double>({ 6,7,8,9,10 });

	auto lazy_mult = first * second;

	std::cout << lazy_mult[1] << std::endl;  // Prints mat[1] * vec[1]

	tridiagonal result;
	result = first * second;  // Evaluates all elements

}
