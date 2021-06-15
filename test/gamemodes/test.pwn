#include <a_samp>

#include "../../samp-vectors.inc"


main()
{

}

public OnGameModeInit()
{
	new Vector:test = Vector_Create();

	new time = GetTickCount();
	for(new x = 1; x < 500; x++)
		Vector_Add(test, x);

	Vector_Insert(test, 600, 6213);

	foreachVector(test, i) {
		printf("%d", i);
	}
	return 1;	
}