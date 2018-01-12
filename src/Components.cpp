#include "Components.h"

void component0_::connect(connection_* c)
{
	in.push_back(c);
}

void component0_::connect(component0_* c)
{
	in.push_back(c->connection());
}

connection_* component0_::connection()
{
	return &out;
}

void component0_::print_in()
{
	std::cout << "IN: ";

	for (int i = 0; i < in.size(); i++)
	{
		if (in[i]->owner == NULL)
			continue;

		std::cout << in[i]->owner->id << "(" << in[i]->owner->name << ")";

		if (i < in.size() - 1)
			std::cout << " ";
	}
}

power_::power_()
{
	out.owner = this;
}

void power_::update()
{
	on = true;
	out.on = on;
}

void power_::print()
{
	std::cout << "ID: " << id;
	std::cout << " | CMP: Pwr Src | NAME: " << name << " | GRND: " << grounded << " | ON: " << out.on;
}

light_::light_()
{
	out.owner = this;
}

void light_::update()
{
	on = false;

	for (int i = 0; i < in.size(); i++)
	{
		if (in[i]->on)
		{
			on = true;
			break;
		}
	}

	out.on = on;
}

void light_::print()
{
	std::cout << "ID: " << id;
	std::cout << " | CMP: Light | NAME: " << name << " | GRND: " << grounded << " | ON: " << out.on;
}

switch_::switch_()
{
	out.owner = this;
}

void switch_::update()
{
	on = false;

	if (!closed)
	{
		out.on = on;
		return;
	}
		

	for (int i = 0; i < in.size(); i++)
	{
		if (in[i]->on)
		{
			on = true;
			break;
		}
	}

	out.on = on;
}

void switch_::print()
{
	std::cout << "ID: " << id;
	std::cout << " | CMP: Switch | NAME: " << name << " | GRND: " << grounded << " | Closed: " << closed;
}

wire_::wire_()
{
	out.owner = this;
}

void wire_::update()
{
	on = false;

	for (int i = 0; i < in.size(); i++)
	{
		if (in[i]->on)
		{
			on = true;
			break;
		}
	}

	out.on = on;
}

void wire_::print()
{
	std::cout << "ID: " << id;
	std::cout << " | CMP: Wire | NAME: " << name << " | GRND: " << grounded << " | ON: " << out.on;
}

relay_::relay_()
{
	out0.owner = this;
	out1.owner = this;
	out2.owner = this;
}

void relay_::update()
{
	out0.on = false;
	out1.on = false;
	out2.on = false;

	bool on[2];

	for (int i = 0; i < 2; i++)
		on[i] = false;

	for (int i = 0; i < in0.size(); i++)
	{
		if (in0[i]->on)
		{
			on[0] = true;
			break;
		}
	}

	for (int i = 0; i < in1.size(); i++)
	{
		if (in1[i]->on)
		{
			on[1] = true;
			break;
		}
	}

	if (on[0])
		out0.on = true;
	else
		out0.on = false;

	if (on[1])
	{
		if (on[0])
			out1.on = true;
		else
			out2.on = true;
	}
	else
	{
		out1.on = false;
		out2.on = false;
	}
}

void relay_::connect(connection_* c, int pin)
{
	if (pin == 1)
		in1.push_back(c);
	else
		in0.push_back(c);
}

void relay_::connect(component0_* c, int pin)
{
	if (pin == 1)
		in1.push_back(c->connection());
	else
		in0.push_back(c->connection());
}

connection_* relay_::connection(int pin)
{
	if (pin == 0)
		return &out0;
	else if (pin == 2)
		return &out2;
	else
		return &out1;
}

void relay_::print()
{
	std::cout << "ID: " << id;
	std::cout << " | CMP: Relay | NAME: " << name << " | GRND: " << grounded << " | ON(0): " << out0.on;
	std::cout << " | ON(1): " << out1.on;
	std::cout << " | ON(2): " << out2.on;
}

void relay_::print_in()
{
	std::cout << "IN0: ";

	for (int i = 0; i < in0.size(); i++)
	{
		if (in0[i]->owner == NULL)
			continue;

		std::cout << in0[i]->owner->id << "(" << in0[i]->owner->name << ")";

		if (i < in0.size() - 1)
			std::cout << " : ";
	}

	std::cout << " | IN1: ";

	for (int i = 0; i < in1.size(); i++)
	{
		if (in1[i]->owner == NULL)
			continue;

		std::cout << in1[i]->owner->id << "(" << in1[i]->owner->name << ")";

		if (i < in1.size() - 1)
			std::cout << " : ";
	}
}