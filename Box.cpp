#include "stdafx.h"

Box::Box(int p_Dimensions = 0, std::deque<int> p_TreeStructure = null, std::deque<int> p_IntDatas = null)
{
	std::deque<int> l_IntDatas = null;
	if (p_TreeStructure.size() == 0 || p_TreeStructure.size() != p_Dimensions)
	{
		for (int l_Itr = 0; l_Itr < p_Dimensions; ++l_Itr)
		{
			p_TreeStructure.push_back(1);
		}
	}
	else if (p_IntDatas.size() != 0)
	{
		int l_ExpectedDatas = 1;
		for (int l_Itr = 0; l_Itr < p_Dimensions; ++l_Itr)
			l_ExpectedDatas *= p_TreeStructure[l_Itr];

		if (p_IntDatas.size() == l_ExpectedDatas)
			l_IntDatas = p_IntDatas;
		
	}
	m_Child = new Dimension(p_TreeStructure, 0, this, nullptr, l_IntDatas);
}

int Box::GetValueAt(std::deque<int> p_Coordinates) const
{
	std::deque<int> l_Value = m_Child->GetValueAt(p_Coordinates);
	if (l_Value.size() != 0)
		return l_Value[0];

	return 0;
}

int* Box::GetFieldAt(std::deque<int> p_Coordinates)
{
	int* l_Field = m_Child->GetFieldAt({ p_Coordinates, 0 }).second;
	return l_Field;
}

int* Box::SetValueAt(std::deque<int> p_Coordinates, int p_Value)
{
	int* l_Field = GetFieldAt(p_Coordinates);
	if (l_Field != nullptr)
		*l_Field = p_Value;
	
	return l_Field;
}

bool Box::IsEmpty() const
{
	return m_Child == nullptr ? true : false;
}

void Box::AppendOnAxe(int p_Axe, std::deque<int> p_IntDatas, bool p_Front)
{
	if (!m_Child)
		return;

	std::deque<int> l_TreeStructure = m_Child->GetTreeStructure();
	if (p_Axe >= l_TreeStructure.size())
		return;

	int l_ExpectedIntDatas = 1;
	for (int l_Itr = 0; l_Itr < l_TreeStructure.size(); ++l_Itr)
	{
		if (l_Itr != p_Axe)
			l_ExpectedIntDatas *= l_TreeStructure[l_Itr];
	}

	if (p_IntDatas.size() == 0)
	{
		for (int l_Itr = 0; l_Itr < l_ExpectedIntDatas; ++l_Itr)
			p_IntDatas.push_back(0);
	}

	if (p_IntDatas.size() != l_ExpectedIntDatas)
		return;

	m_Child->AppendOnAxe(p_Axe, p_IntDatas, p_Front);
	UpdateTreeStructure();
}

void Box::UpdateTreeStructure()
{
	std::deque<Dimension*> l_AllChildren = GetAllChildren();
	
	std::map<int, int> l_SublevelSizes;
	for (Dimension* l_Child : l_AllChildren)
		++l_SublevelSizes[l_Child->GetSublevel()];

	std::deque<int> l_TreeStructure;
	for (int l_Itr = 0; l_SublevelSizes[l_Itr] != 0; ++l_Itr)
	{
		if (l_Itr == 1)
		{
			l_TreeStructure.push_back(l_SublevelSizes[l_Itr]);
		}
		else if (l_Itr > 1)
		{
			l_TreeStructure.push_back(l_SublevelSizes[l_Itr] / l_SublevelSizes[l_Itr - 1]);
		}
	}
	l_TreeStructure.pop_back();

	for (Dimension* l_Child : l_AllChildren)
		l_Child->SetTreeStructure(l_TreeStructure);
}

std::deque<Dimension*> Box::GetAllChildren()
{
	return GetChild()->GetAllChildren();
}

std::deque<Dimension*> Box::SortBySublevel(std::deque<Dimension*> l_Dimensions)
{
	if (l_Dimensions.size() != 0)
	{
		std::deque<Dimension*> l_SortedDimensions;
		int l_TreeSize = 0;
		for (Dimension* l_Dimension : l_Dimensions)
		{
			if (l_Dimension->GetSublevel() > l_TreeSize)
				l_TreeSize = l_Dimension->GetSublevel();
		}
		for (int l_Itr = 0; l_Itr < l_TreeSize; ++l_Itr)
		{
			for (Dimension* l_Dimension : l_Dimensions)
			{
				if (l_Dimension->GetSublevel() == l_Itr)
					l_SortedDimensions.push_back(l_Dimension);
			}
		}
		return l_SortedDimensions;
	}
}

void Box::UpdateIntDatas()
{

}