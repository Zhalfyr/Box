#include "stdafx.h"


class Table
{
	public:
		typedef std::string			Field;
		typedef std::deque<Field>	Row;
		typedef std::deque<Row>		Content;
		typedef std::pair<Row, Row> TableStruct;

		Table() {};
		Table(Content p_Content, TableStruct p_Struct);

		~Table() {};

		Content GetContent() const { return m_Content; };
		TableStruct GetStructure() const { return m_Struct; };
		bool GetStructure(bool p_bool) const { return p_bool ? !(m_Struct.first.empty() && m_Struct.second.empty()) : (m_Struct.first.empty() && m_Struct.second.empty()); };
		int GetRows() const { return m_Rows; };
		int GetColumns() const { return m_Columns; };
		Field GetField(int p_X, int p_Y) const { return m_Struct.first.size() ? m_Struct.second.size() ? m_Content[p_X + 1][p_Y + 1] : m_Content[p_X + 1][p_Y] : m_Content[p_X][p_Y]; };
		void SetContent(Content p_Content);
		void SetStructure(TableStruct p_Struct);
		void UpdateRowsAndColumns();

		void AlignFields();
		void RemoveSpaces();
		void Shift();
		void Display() const;
		

	private:
		Content m_Content = null;
		TableStruct m_Struct = null;
		int m_Rows = 0;
		int m_Columns = 0;
};