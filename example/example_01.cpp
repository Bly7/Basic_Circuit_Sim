#include <iostream>
#include <vector>
#include <string>

Components.h

int main(int argc, char* argv[])
{
	power_ p;
	wire_ w[12];
	relay_ r;
	switch_ s[2];
	light_ l[2];

	// Connect

	w[0].connect(&p);

	w[1].connect(&w[0]);
	w[2].connect(&w[0]);

	s[0].connect(&w[1]);

	w[3].connect(&s[0]);

	s[1].connect(&w[2]);

	w[11].connect(&s[1]);

	r.connect(&w[3]);
	r.connect(&w[11], 1);

	w[4].connect(r.connection(2));
	w[5].connect(r.connection());
	w[6].connect(r.connection(0));

	l[0].connect(&w[5]);

	l[1].connect(&w[4]);

	w[7].connect(&l[0]);
	
	w[8].connect(&l[1]);

	w[9].connect(&w[7]);
	w[9].connect(&w[8]);

	w[10].connect(&w[6]);
	w[10].connect(&w[9]);

	p.connect(&w[10]);

	// Add names

	p.name = "p";
	r.name = "r";
	
	for (int i = 0; i < 2; i++)
		s[i].name = "s" + std::to_string(i);

	for (int i = 0; i < 12; i++)
		w[i].name = "w" + std::to_string(i);

	for (int i = 0; i < 2; i++)
		l[i].name = "l" + std::to_string(i);

	// Add compontents to array

	std::vector<component_*> components;

	components.push_back(&p);
	components.push_back(&r);

	for (int i = 0; i < 2; i++)
		components.push_back(&s[i]);

	for (int i = 0; i < 12; i++)
		components.push_back(&w[i]);

	for (int i = 0; i < 2; i++)
		components.push_back(&l[i]);

	// Generate IDs
	for (int i = 0; i < components.size(); i++)
		components[i]->id = i;

	// switch controls
	s[0].closed = true;
	s[1].closed = true;

	float frames = 20;

	for (int frame = 0; frame < frames; frame++)
	{
		std::cout << "frame: " << frame << std::endl;

		for (int i = 0; i < components.size(); i++)
		{
			components[i]->update();


			std::cout << "\t";
			components[i]->print();
			std::cout << std::endl;
			std::cout << "\t  ";
			components[i]->print_in();
			std::cout << std::endl;
		}
	}	
	
	return 0;
}