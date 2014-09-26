#include "Notes.h"


Notes::Notes()
{
	OpenDB();
	mSelectedNote = mNotes.begin();
}



