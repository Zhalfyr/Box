#include "stdafx.h"

Dimension::Dimension(std::deque<int> p_TreeStructure, int p_Sublevel, Box* p_Box, Dimension* p_Parent, std::deque<int> p_IntDatas)
{
	m_Sublevel = p_Sublevel;
	m_Box = p_Box;
	m_Parent = p_Parent;
	m_IntDatas = p_IntDatas;
	m_TreeStructure = p_TreeStructure;
	if (p_Sublevel < p_TreeStructure.size())
		m_Children = CreateDimension(p_TreeStructure[m_Sublevel]);
	else if (p_Sublevel == p_TreeStructure.size())
		m_Children = CreateDimension(1);
	else
		m_Children = null;
}

std::deque<Dimension*> Dimension::CreateDimension(int p_Size)
{
	std::deque<Dimension*> l_Children;
	std::deque<std::deque<int>> l_SplittedIntDatas;
	if (m_IntDatas.size() % p_Size)
		return l_Children;

	for (int l_Itr = 0; l_Itr < m_IntDatas.size(); ++l_Itr)
	{
		if (l_Itr % (m_IntDatas.size() / p_Size) == 0)
			l_SplittedIntDatas.push_back(null);
		l_SplittedIntDatas[l_Itr / (m_IntDatas.size() / p_Size)].push_back(m_IntDatas[l_Itr]);
	}

	for (int l_Itr = 0; l_Itr < p_Size; ++l_Itr)
	{
		if (m_Sublevel <= (int)m_TreeStructure.size())
			l_Children.push_back(new Dimension(m_TreeStructure, m_Sublevel + 1, m_Box, this, l_SplittedIntDatas[l_Itr]));
	}
	return l_Children;
}

std::deque<int> Dimension::GetValueAt(std::deque<int> p_Coordinates) const
{
	if ((m_Sublevel + p_Coordinates.size()) != m_TreeStructure.size())
		return null;

	int l_LevelCoordinate = p_Coordinates[0];
	if (p_Coordinates.size() > 1)
	{
		p_Coordinates.pop_front();
		return m_Children[l_LevelCoordinate]->GetValueAt(p_Coordinates);
	}
	else
		return{ m_IntDatas[l_LevelCoordinate] };
}

std::pair<std::deque<int>, int*> Dimension::GetFieldAt(std::pair<std::deque<int>, int*> p_Coordinates)
{
	if ((m_Sublevel + p_Coordinates.first.size()) != m_TreeStructure.size())
		return null;

	int l_LevelCoordinate = p_Coordinates.first[0];
	if (p_Coordinates.first.size() > 1)
	{
		p_Coordinates.first.pop_front();
		return m_Children[l_LevelCoordinate]->GetFieldAt(p_Coordinates);
	}
	else
		return{ null, &m_IntDatas[l_LevelCoordinate] };
}

std::deque<Dimension*> Dimension::GetSiblings()
{
	Dimension* l_LastParent = m_Box->GetChild();
	if (this == l_LastParent)
		return { this };
	else
		return l_LastParent->GetAllChildrenAt(m_Sublevel);
}

std::deque<Dimension*> Dimension::GetAllChildrenAt(int p_Sublevel)
{
	if (m_Sublevel != p_Sublevel -1)
	{
		std::deque<std::deque<Dimension*>> l_ChildrenDeque;
		for (Dimension* l_Child : m_Children)
		{
			l_ChildrenDeque.push_back(l_Child->GetAllChildrenAt(p_Sublevel));
		}
		std::deque<Dimension*> l_ChildrenToReturn;
		for (std::deque<Dimension*> l_Children : l_ChildrenDeque)
		{
			for (Dimension* l_Child : l_Children)
			{
				l_ChildrenToReturn.push_back(l_Child);
			}
		}
		return l_ChildrenToReturn;
	}
	else
	{
		return m_Children;
	}
}

std::deque<Dimension*> Dimension::GetAllChildren()
{
	std::deque<std::deque<Dimension*>> l_ChildrenDeque;
	for (Dimension* l_Child : m_Children)
	{
		l_ChildrenDeque.push_back(l_Child->GetAllChildren());
	}
	std::deque<Dimension*> l_ChildrenToReturn;
	for (std::deque<Dimension*> l_Children : l_ChildrenDeque)
	{
		for (Dimension* l_Child : l_Children)
		{
			l_ChildrenToReturn.push_back(l_Child);
		}
	}
	l_ChildrenToReturn.push_back(this);
	return l_ChildrenToReturn;
}

void Dimension::AppendOnAxe(int p_Axe, std::deque<int> p_IntDatas, bool p_Front)
{
	if (p_Axe == m_Sublevel)
	{
		std::deque<Dimension*> l_Siblings = GetSiblings();
		if (l_Siblings.size() != 0)
		{
			for (Dimension* l_Sibling : l_Siblings)
			{
				if (p_Front)
					l_Sibling->m_Children.push_front(new Dimension(m_TreeStructure, l_Sibling->m_Sublevel + 1, m_Box, this, p_IntDatas));
				else
					l_Sibling->m_Children.push_back(new Dimension(m_TreeStructure, l_Sibling->m_Sublevel + 1, m_Box, this, p_IntDatas));
			}
		}
	}
	else
	{
		m_Children[0]->AppendOnAxe(p_Axe, p_IntDatas, p_Front);
	}
}