#include "stdafx.h"


class Dimension
{
	public:
		Dimension(std::deque<int> p_TreeStructure, int p_Sublevel, Box* p_Box, Dimension* p_Parent, std::deque<int> p_IntDatas);
		~Dimension();

		std::deque<Dimension*> CreateDimension(int p_Size);
		std::deque<int> GetValueAt(std::deque<int> p_Coordinates) const;
		std::pair<std::deque<int>, int*> GetFieldAt(std::pair<std::deque<int>, int*> p_Coordinates);
		std::deque<int> const GetTreeStructure() const { return m_TreeStructure; };
		std::deque<Dimension*> GetSiblings();
		std::deque<Dimension*> GetAllChildrenAt(int p_Sublevel);
		std::deque<Dimension*> GetAllChildren();
		void SetTreeStructure(std::deque<int> p_TreeStructure) { m_TreeStructure = p_TreeStructure; };
		int GetSublevel() { return m_Sublevel; };
		void AppendOnAxe(int p_Axe, std::deque<int> p_IntDatas, bool p_Front);
	private:
		int m_Sublevel;
		Box* m_Box;
		Dimension* m_Parent;
		std::deque<Dimension*> m_Children;
		std::deque<int> m_IntDatas;
		std::deque<int> m_TreeStructure;
};