int main()
{
	int a = 0;

	while (a < 5) {
		a++;
		printf("%d\n", a);
	}

    do {
		a--;
		printf("%d\n", a);
	} while (a > 0);

	return 0;
}