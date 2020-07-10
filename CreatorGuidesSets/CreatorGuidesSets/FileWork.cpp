#include "FileWork.h"

int FileWork::getFileSizeOutput()
{
    struct stat file_stat;
    stat("output.txt", &file_stat);
    return file_stat.st_size;
}
int FileWork::getFileSizeOut()
{
	struct stat file_stat;
	stat("out.txt", &file_stat);
	return file_stat.st_size;
}

void FileWork::copyFile(std::string f1)
{
	const static int BUF_SIZE = 4096;
	using std::ios_base;

	std::ifstream in(f1, ios_base::in | ios_base::binary);
	std::ofstream out("output.txt", ios_base::out | ios_base::binary); // ����� ����������

	char buf[BUF_SIZE];
	do {
		in.read(&buf[0], BUF_SIZE);      // ������� �������� n ���� � �����,
		out.write(&buf[0], in.gcount()); // ����� �������� ���������� ������
	} while (in.gcount() > 0);        // � ����� ������.

	in.close();
	out.close();

}