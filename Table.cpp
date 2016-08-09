#include "stdafx.h"


Table::Table(Content p_Content, TableStruct p_Struct = { null ,null })
{
	SetContent(p_Content);
	SetStructure(p_Struct);
	UpdateRowsAndColumns();
}

void Table::SetContent(Content p_Content)
{
	int l_Columns = 0;
	for (Row l_Row : p_Content)
		l_Columns = l_Row.size() > l_Columns ? l_Row.size() : l_Columns;
	
	m_Columns = l_Columns;

	for (Row& l_Row : p_Content)
	{
		int l_Diff = m_Columns - l_Row.size();
		for (int l_Itr =0; l_Itr < l_Diff; ++l_Itr)
			l_Row.push_back("");
	}

	m_Content = p_Content;
	UpdateRowsAndColumns();
}

void Table::SetStructure(TableStruct p_Struct)
{
	if (p_Struct.first.size() == m_Columns)
	{
		if (m_Struct.first.size())
			m_Content.pop_front();

		m_Struct.first = p_Struct.first;
		m_Content.push_front(m_Struct.first);
	}
	if (m_Struct.first.size() ? p_Struct.second.size() + 1 == m_Content.size() : p_Struct.second.size() == m_Content.size())
	{
		bool l_NeedRemove = false;
		if (m_Struct.second.size())
			l_NeedRemove = true;

		m_Struct.second = p_Struct.second;
		int l_Itr = 0;
		for (Row& l_row : m_Content)
		{
			if (l_NeedRemove)
				l_row.pop_front();
			if (!l_Itr)
				l_row.push_front("");
			else
				l_row.push_front(p_Struct.second[l_Itr - 1]);
			l_Itr++;
		}
	}
	if (GetStructure(true))
	{
		RemoveSpaces();
		AlignFields();
	}
	UpdateRowsAndColumns();
}

void Table::UpdateRowsAndColumns()
{
	m_Rows = m_Content.size();
	m_Columns = m_Content[0].size();
}

void Table::AlignFields()
{
	RemoveSpaces();
	int l_Columns = GetColumns();
	Content l_Content = GetContent();
	Content l_ResultContent = l_Content;

	for (int l_Itr = 0; l_Itr < l_Columns; ++l_Itr)
	{
		int l_FieldSize = 0;
		for (Row l_Row : l_ResultContent)
			l_FieldSize = l_Row[l_Itr].size() > l_FieldSize ? l_Row[l_Itr].size() : l_FieldSize;

		l_FieldSize += 3;

		for (Row& l_Row : l_ResultContent)
		{
			int l_WhitespaceNumber = l_FieldSize - l_Row[l_Itr].size();
			for (int l_ThirdItr = 0; l_ThirdItr < l_WhitespaceNumber; ++l_ThirdItr)
			{
				if (!l_Itr && GetStructure(true) && !(l_ThirdItr < 2))
					l_Row[l_Itr] = " " + l_Row[l_Itr];
				else
					l_Row[l_Itr] += " ";
			}
		}
	}
	SetContent(l_ResultContent);
}

void Table::RemoveSpaces()
{
	for (Row& l_Row : m_Content)
	{
		for (Field& l_Field : l_Row)
		{
			while (l_Field.size() && l_Field[l_Field.size() - 1] == (char)32)
				l_Field.pop_back();
		}
	}
}

void Table::Shift()
{
	Content l_NewContent; 
	for (int l_Itr = 0; l_Itr < m_Columns; ++l_Itr)
	{
		l_NewContent.push_back(null);
		for (Row l_Row : m_Content)
		{
			l_NewContent[l_Itr].push_back(l_Row[l_Itr]);
		}
	}
	m_Content = l_NewContent;
	if (GetStructure(true))
	{
		TableStruct l_NewStruct;
		l_NewStruct.first = m_Struct.second;
		l_NewStruct.second = m_Struct.first;
		m_Struct = l_NewStruct;
	}
	RemoveSpaces();
	UpdateRowsAndColumns();
}

void Table::Display() const
{
	int l_RowLenght = 0;
	for (Field l_Field : m_Content[0])
	{
		l_RowLenght += l_Field.size();
	}
	for (int l_Itr = 0; l_Itr < l_RowLenght; ++l_Itr)
	{
		std::cout << "=";
	}
	std::cout << "\n";
	for (Row l_Row : GetContent())
	{
		for (Field l_Field : l_Row)
		{
			std::cout << l_Field;
		}
		std::cout << "\n";
		for (int l_Itr = 0; l_Itr < l_RowLenght; ++l_Itr)
		{
			std::cout << "-";
		}
		std::cout << "\n";
	}
}