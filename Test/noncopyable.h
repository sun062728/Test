#pragma once

class Noncopyable
{
protected:
	Noncopyable() = default;
	~Noncopyable() = default;
private:
	Noncopyable(Noncopyable const &) = delete;
	Noncopyable & operator=(Noncopyable const &) = delete;
};