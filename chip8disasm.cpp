#include <iostream>
#include <cstdint>
#include <cstring>
#include <fstream>
#include "chip8disasm.hpp"

Chip8Disasm::Chip8Disasm()
{
    memset(romFile, 0x0, MAX_MEMORY);
}

bool Chip8Disasm::loadRom(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);

    const bool RomOpened = file.is_open();

    if(RomOpened)
    {
        romSize = file.tellg();

        if(romSize > MAX_MEMORY) return 0;

        char* buffer = new char[romSize];

        file.seekg(0, std::ios::beg);
        file.read(buffer, romSize);

        for (long index = 0; index < romSize; ++index)
        {
            romFile[index] = buffer[index];
        }

        delete[] buffer;
    }

    file.close();
    return RomOpened;
}

void Chip8Disasm::disasm()
{
    std::cout << std::hex;

    for (int index = 0; index < romSize; index += 2)
    {
        opcode = (romFile[index] << 8u) | romFile[index + 1];
        offset = 0x00;

        while (offset < MAX_OPCODES)
        {
            if ((opcodeMask[offset] & opcode) == opcodeId[offset])
            {
                break;
            }

            ++offset;
        }

        switch (offset)
        {
            case 0:     OP_0NNN();      break;
            case 1:     OP_00E0();      break;
            case 2:     OP_00EE();      break;
            case 3:     OP_1NNN();      break;
            case 4:     OP_2NNN();      break;
            case 5:     OP_3XKK();      break;
            case 6:     OP_4XKK();      break;
            case 7:     OP_5XY0();      break;
            case 8:     OP_6XKK();      break;
            case 9:     OP_7XKK();      break;
            case 10:    OP_8XY0();      break;
            case 11:    OP_8XY1();      break;
            case 12:    OP_8XY2();      break;
            case 13:    OP_8XY3();      break;
            case 14:    OP_8XY4();      break;
            case 15:    OP_8XY5();      break;
            case 16:    OP_8XY6();      break;
            case 17:    OP_8XY7();      break;
            case 18:    OP_8XYE();      break;
            case 19:    OP_9XY0();      break;
            case 20:    OP_ANNN();      break;
            case 21:    OP_BNNN();      break;
            case 22:    OP_CXKK();      break;
            case 23:    OP_DXYN();      break;
            case 24:    OP_EX9E();      break;
            case 25:    OP_EXA1();      break;
            case 26:    OP_FX07();      break;
            case 27:    OP_FX0A();      break;
            case 28:    OP_FX15();      break;
            case 29:    OP_FX18();      break;
            case 30:    OP_FX1E();      break;
            case 31:    OP_FX29();      break;
            case 32:    OP_FX33();      break;
            case 33:    OP_FX55();      break;
            case 34:    OP_FX65();      break;
            case 35:    OP_0NNN();      break;
            default:    OP_NULL();      break;
        }
    }
}

void Chip8Disasm::OP_NULL()
{
    std::cout << "; UNKN ERROR" << "\n";
}

void Chip8Disasm::OP_00E0()
{
    std::cout << "CLS" << "\n";
}

void Chip8Disasm::OP_00EE()
{
    std::cout << "RET" << "\n";
}

void Chip8Disasm::OP_0NNN()
{
    std::cout << "SYS 0x0" << OP_ADDR << "\n";
}

void Chip8Disasm::OP_1NNN()
{
    std::cout << "JP 0x0" << OP_ADDR << "\n";
}

void Chip8Disasm::OP_2NNN()
{
    std::cout << "CALL 0x0" << OP_ADDR << "\n";
}

void Chip8Disasm::OP_3XKK()
{
    std::cout << "SE V" << OP_X << ", " << OP_BYTE << "\n";
}

void Chip8Disasm::OP_4XKK()
{
    std::cout << "SNE V" << OP_X << ", " << OP_BYTE << "\n";
}

void Chip8Disasm::OP_5XY0()
{
    std::cout << "SE V" << OP_X << ", V" << OP_Y << "\n";
}

void Chip8Disasm::OP_6XKK()
{
    std::cout << "LD V" << OP_X << ", 0x00" << (OP_BYTE) << "\n";
}

void Chip8Disasm::OP_7XKK()
{
    std::cout << "ADD V" << OP_X << ", 0x00" << (OP_BYTE) << "\n";
}

void Chip8Disasm::OP_8XY0()
{
    std::cout << "LD V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY1()
{
    std::cout << "OR V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY2()
{
    std::cout << "AND V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY3()
{
    std::cout << "XOR V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY4()
{
    std::cout << "ADD V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY5()
{
    std::cout << "SUB V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY6()
{
    std::cout << "SHR V" << OP_X << "{, V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XY7()
{
    std::cout << "SUBN V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_8XYE()
{
    std::cout << "SHL V" << OP_X << "{, V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_9XY0()
{
    std::cout << "SNE V" << OP_X << ", V"<<OP_Y << "\n";
}

void Chip8Disasm::OP_ANNN()
{
    std::cout << "LD I" << OP_X << ", 0x0" << (OP_ADDR) << "\n";
}

void Chip8Disasm::OP_BNNN()
{
    std::cout << "JP V0" << ", 0x0" << (OP_ADDR) << "\n";
}

void Chip8Disasm::OP_CXKK()
{
    std::cout << "RND V" << OP_X << ", 0x00" << (OP_BYTE) << "\n";
}

void Chip8Disasm::OP_DXYN()
{
    std::cout << "DRW V" << OP_X << ", V" << OP_Y <<", 0x000"<< OP_NIBBLE << "\n";
}

void Chip8Disasm::OP_EX9E()
{
    std::cout << "SKP V" << OP_X << "\n";
}

void Chip8Disasm::OP_EXA1()
{
    std::cout << "SKNP V" << OP_X << "\n";
}

void Chip8Disasm::OP_FX07()
{
    std::cout << "LD V" << OP_X << ", DT" << "\n";
}

void Chip8Disasm::OP_FX0A()
{
    std::cout << "LD V" << OP_X << ", K" << "\n";
}

void Chip8Disasm::OP_FX15()
{
    std::cout << "LD DT, V" << OP_X << "\n";

}

void Chip8Disasm::OP_FX18()
{
    std::cout << "LD ST, V" << OP_X << "\n";
}

void Chip8Disasm::OP_FX1E()
{
    std::cout << "ADD I, V" << OP_X << "\n";
}

void Chip8Disasm::OP_FX29()
{
    std::cout << "LD F, V" << OP_X << "\n";

}

void Chip8Disasm::OP_FX33()
{
    std::cout << "LD B, V" << OP_X << "\n";
}

void Chip8Disasm::OP_FX55()
{
    std::cout << "LD [I], V" << OP_X << "\n";
}

void Chip8Disasm::OP_FX65() 
{
    std::cout << "LD V" << OP_X << ", [I]" << "\n";
}