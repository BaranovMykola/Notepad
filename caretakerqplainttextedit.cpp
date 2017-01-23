#include "caretakerqplainttextedit.h"

#include <iterator>

CaretakerQPlaintTextEdit::CaretakerQPlaintTextEdit()
{

}

void CaretakerQPlaintTextEdit::add(MementoQPlainTextEdit *newState)
{
    changes.push_back(newState);
    current = std::prev(changes.end());
}

MementoQPlainTextEdit *CaretakerQPlaintTextEdit::get()
{
    return *current;
}

void CaretakerQPlaintTextEdit::prev()
{
    --current;
}

bool CaretakerQPlaintTextEdit::end() const
{
    return std::next(current) == changes.end();
}

bool CaretakerQPlaintTextEdit::begin() const
{
    return current == changes.begin();
}

void CaretakerQPlaintTextEdit::next()
{
    ++current;
}
