

class APC
{
public:
	static void s_run();

private:
	static void NTAPI _s_apc(ULONG_PTR Parameter);
};