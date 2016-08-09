#include "stdafx.h"

int main()
{
	int l_Dimensions = 3;

	std::deque<int> l_TreeStructure =
	{ 2, 3, 4 };

	std::deque<int> l_IntDatas =
	{
		12, 5, 45, 78, 53, 45,
		47, 56, 75 ,37 ,2, 47,
		45, 73, 19, 7, 78 ,82,
		4, 47, 53, 59, 67, 81
	};

	Box* l_Box = new Box(l_Dimensions, l_TreeStructure, l_IntDatas);
	if (!l_Box->IsEmpty())
	{
		std::cout << l_Box->GetValueAt({ 0, 0, 0 });
		std::cout << "\n";
		std::cout << l_Box->GetValueAt({ 1, 2, 3 });
		std::cout << "\n";
		std::cout << *l_Box->SetValueAt({ 1, 2, 3 }, 200);
		std::cout << "\n";
		std::cout << l_Box->GetValueAt({ 1, 1, 1 });
		std::cout << "\n";
		std::deque<Dimension*> l_Bab = l_Box->GetAllChildren();
		l_Bab = l_Box->SortBySublevel(l_Bab);
		l_Box->AppendOnAxe(0, null);
		l_Box->AppendOnAxe(1, null);
		l_Box->AppendOnAxe(2, null);
		l_Box->AppendOnAxe(3, null);
		
	}

	int a;
	std::cin >> a;
	return 0;
}

