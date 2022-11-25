#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "utils.h"

int main()
{
    std::vector<uint8_t> raw_image = { 0 };
    if (!utils::ReadFileToMemory("input.exe", &raw_image)) {
        printf("[-] Error with open input.exe\n");
        system("pause");
        return 0;
    }

    BYTE* data = raw_image.data();
    PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)data;
    PIMAGE_NT_HEADERS nt_header = (PIMAGE_NT_HEADERS)((DWORD64)data + dos_header->e_lfanew);
    PIMAGE_FILE_HEADER file_header = (PIMAGE_FILE_HEADER)((DWORD64)data + dos_header->e_lfanew + sizeof(nt_header->Signature));
    PIMAGE_SECTION_HEADER section_header = (PIMAGE_SECTION_HEADER)((DWORD64)data + dos_header->e_lfanew + sizeof(nt_header->Signature) + sizeof(nt_header->FileHeader) + sizeof(nt_header->OptionalHeader));
    DWORD64 numberofsections = file_header->NumberOfSections;

    printf("[!] Section Header: Number of Sections %x\n", file_header->NumberOfSections);
    

    PIMAGE_SECTION_HEADER import_section = {};

    for (int i = 1; i <= numberofsections; i++, section_header++) {

        if (*section_header->Name)
        {
            char* v13 = (char*)section_header->Name;
            do
                *v13++ = utils::_int(1, 9) + 0x30;
            while (*v13);
        }
        printf("[%i] New Section Name %s\n", i,section_header->Name);
    }

    std::ofstream file("output.exe", std::ios_base::out | std::ios_base::binary);
    file.write((char*)raw_image.data(), raw_image.size());
    file.close();

    system("pause");
}