#include "Calculator.h"

int main()
{
	Calculator calcu;
	char c;
	std::cout<<"press Ctrl+C to quit, and R to continue:"<<std::endl;
	c = getchar();
	while(c != EOF)
	{
		std::cout<<"Please input your expression:"<<std::endl;
		calcu.run();
		calcu.clear();
		std::cout<<"press Ctrl+C to quit, and R to continue:"<<std::endl;
		std::cin.clear();
		c = getchar();
	}
	::system("pause");
	return 0;
}