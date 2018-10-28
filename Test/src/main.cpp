namespace dmn
{
	__declspec(dllimport) void foo();
}

int main()
{
	dmn::foo();
	return 0;
}
