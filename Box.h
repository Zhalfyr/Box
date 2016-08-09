#include "stdafx.h"

class Dimension;

class Box
{
	public:
		Box(int p_Dimensions, std::deque<int> p_TreeStructure, std::deque<int> p_IntDatas);
		~Box();

		int GetValueAt(std::deque<int> p_Coordinates) const;
		int* GetFieldAt(std::deque<int> p_Coordinates);
		int* SetValueAt(std::deque<int> p_Coordinates, int p_Value);
		bool IsEmpty() const;
		Dimension* GetChild() { return m_Child; };
		void AppendOnAxe(int p_Axe, std::deque<int> p_IntDatas = null, bool p_Front = false);
		void UpdateTreeStructure();
		void UpdateIntDatas();
		std::deque<Dimension*> GetAllChildren();
		std::deque<Dimension*> SortBySublevel(std::deque<Dimension*> l_Dimensions);
	private:
		Dimension* m_Child;
};