#pragma once

template <typename T>
T min(T x, T y)
{
	if (x < y) return x;
	return y;
}
template <typename T>
int max(T x, T y)
{
	if (x > y) return x;
	return y;
}