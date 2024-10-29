#pragma once


class Visitor
{
public: 
	Visitor() {}
};

class Painter : public Visitor
{
public:
	void visit();
};