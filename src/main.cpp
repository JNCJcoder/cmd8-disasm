#include <iostream>
#include "chip8disasm.cpp"

int main(int argc, char const *argv[])
{
	Chip8Disasm chip8;

	const bool fileExist = chip8.loadRom(argv[1]);

	if(fileExist)
	{
		chip8.disasm();
	}
	else
	{
		std::cout << "Usage: " << argv[0] << " <ROM_LOCATION>" << std::endl;
	}
	
	return 0;
}
