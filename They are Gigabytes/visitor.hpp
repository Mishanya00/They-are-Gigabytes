#pragma once

#include "map.hpp"


class Visitor
{
public: 
	Visitor() {}
	virtual void visit() = 0;
};

class Painter : public Visitor
{
public:
	void visit();
};