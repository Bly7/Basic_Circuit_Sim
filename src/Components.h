#pragma once

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <iostream>
#include <vector>
#include <string>

// Component - Component Base Class
// 
// This is a basic component class that all
// components will inherit from.
class component_
{
public:
	// Virtual functions
	//	This allows each component to figure out what to
	//	do with each one. Though they should follow some
	//	sort of methodology.

	// Update Function
	//	This should update all variables within the
	//	component.
	virtual void update() = 0;

	// Print Function
	//	This should print all information about a given
	//	components internal makeup except input and
	//	output.
	virtual void print() = 0;

	// Print_In Function
	//	This should print all connections going into the
	//	component.
	virtual void print_in() = 0;

	// Name String
	//	This is a name given to the component. It does not
	//	really matter what it is in relation to the
	//	program, but it is useful for human interpretation.
	std::string name;

	// ID UInt
	//	This is an id number given to the component. This
	//	is not used program wise, as of right now, but it
	//	can be useful for human interpretation.
	unsigned int id;

	// Grounded Boolean
	//	This is a variable that will be modified to show if
	//	a component is connected to the ground. It is useful
	//	when determining what should be caclulated and what
	//	should not.
	bool grounded = false;
};

// Connection Structure
//
// This is the basic connection structure. It acts as an
// output pin on within an electrical component. It can be
// on or off. It also keeps track of who it's owner is.
struct connection_
{
	// On Boolean
	//	This is a value that keeps track of whether the
	//	component is outputing power or not. It will be
	//	modified by it's owner.
	bool on = false;

	// Owner Component Pointer
	//	This keeps track of the component that owns this
	//	connection.
	component_* owner = NULL;
};

// Component0 - Component Derived Class
//				One in One out Component Base Class
//
// This is the base class for all basic compontents that
// have only one input and one output. These are power
// source, light, switch, wire, etc.
class component0_ : public component_
{
public:
	// Connect Connection Function
	//	This connects the connection pointer to the
	//	in vector of this component.
	void connect(connection_* c);

	// Connect Component0 Function
	//	This connects the component0 pointer to the
	//	in vector of this component. It gets the out
	//	connection of this component.
	void connect(component0_* c);

	// Connection function
	//	This returns a pointer to the out connection
	//	of this component.
	connection_* connection();

	// Print_In function
	//	This prints the input connections to this
	//	component
	void print_in();

	// Out Connection
	//	This is the output connection of this
	//	component
	connection_ out;

	// In Connection
	//	This is the input connections of this
	//	component
	std::vector<connection_*> in;

	// On Boolean
	//	This keeps track of if power is being
	//	transfered through the component
	bool on = false;
};

// Power Class - Component0 Derived Class
//
// This is the power source. Its output is always
// on. The input acts as a ground. Everything that is
// connected to the ground will be calculated.
class power_ : public component0_
{
public:
	// Power Default Constructor
	//	This sets up all needed variables.
	power_();

	// Update Function
	//	This doesn't do much. It just makes sure on is
	//	set to true and set out to on.
	void update();

	// Print Function
	//	This prints all of the needed variables into the
	//	console.
	void print();
};

// Light Class : Component0 Derived Class
//
// This represents a light. If power is coming in, the
// light will turn on, and the power will be transfered to
// the output connection.
class light_ : public component0_
{
public:
	// Light Default Constructor
	//	This sets up all needed variables.
	light_();

	// Update Function
	//	This checks if power is coming in. If so it turns on
	//	the light. Then it transfers the power to the out
	//	connection.
	void update();

	// Print Function
	//	This prints all of the needed variables into the
	//	console.
	void print();
};

// Switch Class : Component0 Derived Class
//
// This represents a one in one out switch. It can either
// be closed or open. If closed it will transfer any power
// through to it's output.
class switch_ : public component0_
{
public:
	// Switch Default Constructor
	//	This sets up all needed variables.
	switch_();

	// Update Function
	//	This checks to see if the switch is closed. If it
	//	is closed it will transfer the state of the input
	//	to the output. If it is not it will output that it
	//	is off.
	void update();

	// Print Function
	//	This prints all of the needed variables into the
	//	console.
	void print();

	// Closed Boolean
	//	This keeps track of whether or not the switch is
	//	closed
	bool closed = false;
};

// Wire Class : Component0 Class Derived
//
// This is a basic component that just transfers energy
// from its input to its output.
class wire_ : public component0_
{
public:
	// Wire Default Constructor
	//	This sets up all needed variables.
	wire_();

	// Update Function
	//	If there is any power coming into the input it
	//	will transfer it to the output.
	void update();

	// Print Function
	//	This prints all of the needed variables into the
	//	console.
	void print();
};

// Relay Class : Component Class Derived
//
// This is a more complex component. It has two inputs
// and three outputs. These are described below.
//
// in0 is the main input node
// in1 is the switch power input node
// out0 is the output for the main input node
// out1 is the output for the activated switch
// out2 is the output for the inactivated switch
//
// in0 -> out0
// in1 -> out1 || out2
//
// If in0 is on then out1 will get in1's power.
// If in0 is off then out2 will get in1's power.
class relay_ : public component_
{
public:
	// Relay Default Constructor
	//	This sets up all needed variables.
	relay_();

	// Update Function
	//	Updates all needed variables
	//	If in0 is on then out1 will get in1's power.
	//	If in0 is off then out2 will get in1's power.
	void update();

	// Connect Connection Function
	//	Connect a connection to an input pin
	//	Defaults to 0 since that is the main input
	//	pin for a relay.
	void connect(connection_* c, int pin = 0);

	// Connect Connection Function
	//	Connect a component0s output connection to
	//	an input pin
	//	Defaults to 0 since that is the main input
	//	pin for a relay.
	void connect(component0_* c, int pin = 0);

	// Connection Function
	//	This returns an output connection from the
	//	relay.
	//	Defaults to 1 since this is the main output
	//	pin for a relay.
	connection_* connection(int pin = 1);

	// Print Function
	//	This prints all of the needed variables into the
	//	console.
	void print();

	// Print_In Function
	//	This should print all connections going into the
	//	component.
	void print_in();

	// In0 Connection Pointer Vector
	//	The main input node.
	std::vector<connection_*> in0;

	// In1 Connection Pointer Vector
	//	The switch power input node.
	std::vector<connection_*> in1;

	// Out0 Connection
	//	The output for the main input node.
	connection_ out0;

	// Out1 Connection
	//	The output for the activated switch.
	connection_ out1;
	
	// Out2 Connection
	//	The output for the inactivated switch
	connection_ out2;
};


#endif //COMPONENTS_H_