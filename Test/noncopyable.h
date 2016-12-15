#pragma once

class Noncopyable
{
protected:
	Noncopyable() = default;
	~Noncopyable() = default;
	Noncopyable(Noncopyable const &) = delete;
	Noncopyable & operator=(Noncopyable const &) = delete;
};